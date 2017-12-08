#!/usr/bin/env python
# _*_coding: utf-8 _*_

import argparse
import time
import datetime
import subprocess
import gitlab
import ConfigParser
import sys
import os


# gitlab v3

cp_script = ConfigParser.ConfigParser()

cp_script.read('script-config.opt')

maxrepos = cp_script.get('labor', 'MAXREPOS')
maxrepos = int(maxrepos, 10)  # hack so that the script would run. string to int coversion problem

prefixrepolist = cp_script.get('labor', 'PREFIXREPOLIST')
iterations = len(prefixrepolist.split(','))

gitlab_server_url = cp_script.get('gitlab', 'GITLAB_SERVER')
gitlab_server_token = cp_script.get('gitlab', 'GITLAB_SERVER_TOKEN')

user = cp_script.get('credentials', 'GITLAB_ADMIN')
password = cp_script.get('credentials', 'GITLAB_ADMIN_PASSWORD')

ldap_admin = cp_script.get('credentials', 'LDAP_ADMIN')
ldap_admin_password = cp_script.get('credentials', 'LDAP_ADMIN_PASSWORD')

currentdate = datetime.date


def ezslab_resync(args):
    ''' Add / Delete shift new users to new groups etc'''
    response = raw_input("Resync the authorization file with ldap and gitlab (Y/N)")
    authorizationfile = args.authfile
    print "Adding and deleting groups and studentsnames in LDAP as per entries in authorization-file.opt.";
    members_add_gitlab_and_ldap(authorizationfile, "incremental")

    # Add
    if response == "Y":
        ou_todelete = "ou=labor,ou=people,dc=hs-esslingen,dc=de"
        print "adding all members from ldif-prepare-ezs-ldap.ldif file under %s", ou_todelete
        command = "ldapadd -x -c -S logs/ldapadd-error.log -D %s -w %s -f ldif-prepare-ezs-ldap.ldif" % (
            ldap_admin, ldap_admin_password)
        print command

    try:
        subprocess.check_output(command.split(' '))
    except subprocess.CalledProcessError as e:
        print e.output
    response = 'N'


def ezslab_flush(args):
    ''' Initialize config directories'''

    authorizationfile = args.authfile
    print "Adding and deleting groups and studentsnames in LDAP as per entries in authorization-file.opt.";
    members_add_gitlab_and_ldap(authorizationfile, "fresh")

    print "This will delete all entries under ou=labor,ou=people,dc=hs-esslingen,dc=de (Y/N)"
    response = sys.stdin.read(1)
    if response == "Y":
        ou_todelete = "ou=labor,ou=people,dc=hs-esslingen,dc=de"
        print "deleting all members under %s" % ou_todelete
        command = "ldapdelete -r -v -x -c -D %s -w %s %s" % (ldap_admin, ldap_admin_password, ou_todelete)
        print command
        try:
            subprocess.check_output(command.split(' '))
        except subprocess.CalledProcessError as e:
            print e.output
            sys.exit(1)

        print "adding all members from ldif-prepare-ezs-ldap.ldif file under %s", ou_todelete
        command = "ldapadd -x -c -S logs/ldapadd-error.log -D %s -w %s -f ldif-prepare-ezs-ldap.ldif" % (
            ldap_admin, ldap_admin_password)
        print command
        try:
            subprocess.check_output(command.split(' '))
        except subprocess.CalledProcessError as e:
            print e.output
        response = 'N'


def main():
    '''Main entry'''

    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(title='subcommands', description='')

    authorizationfile = None

    # resync
    parser_resync = subparsers.add_parser('resync', help='resyncs auth file with gitlab and ldap')
    parser_resync.set_defaults(func=ezslab_resync)
    parser_resync.add_argument('-c', '--authfile', help='the authorizationfile', type=str, required=authorizationfile)

    # flush
    parser_flush = subparsers.add_parser('flush', help='flush ldap users')
    parser_flush.set_defaults(func=ezslab_flush)
    parser_flush.add_argument('-c', '--authfile', help='the authorizationfile', type=str, required=authorizationfile)

    if len(sys.argv) == 1:
        print parser.format_help()
        return

    args = parser.parse_args()
    args.func(args)


def members_add_gitlab_and_ldap(authorizationfile, mode):
    cp = ConfigParser.ConfigParser()
    authfile = os.getcwd() + '/' + authorizationfile
    print authfile

    if os.path.isfile(authfile):
        cp.read(authfile)
    else:
        print "no file is found at", os.path.realpath(authfile)
        sys.exit(1)

    listofgroups_1 = []
    listofgroups_2 = []
    listofgroups_3 = []
    listofgroups_4 = []
    listofgroups_5 = []
    listofgroups_6 = []
    listofgroups_7 = []
    listofgroups_8 = []
    listofgroups_9 = []
    listofgroups_10 = []

    listofprojects_1 = []
    listofprojects_2 = []
    listofprojects_3 = []
    listofprojects_4 = []
    listofprojects_5 = []
    listofprojects_6 = []
    listofprojects_7 = []
    listofprojects_8 = []
    listofprojects_9 = []
    listofprojects_10 = []

    listofgroups_prefix = prefixrepolist.split(',')
    listofprojects_prefix = prefixrepolist.split(',')
    listofgroups = [listofgroups_1, listofgroups_2, listofgroups_3, listofgroups_4, listofgroups_5, listofgroups_6,
                    listofgroups_7, listofgroups_8, listofgroups_9, listofgroups_10]
    listofprojects = [listofprojects_1, listofprojects_2, listofprojects_3, listofprojects_4, listofprojects_5,
                      listofprojects_6, listofprojects_7, listofprojects_8, listofprojects_9, listofprojects_10]

    for x in range(iterations):
        for y in range(1, maxrepos + 1):
            listofgroups[x].append(listofgroups_prefix[x] + 'group' + str(y))
            listofprojects[x].append(listofprojects_prefix[x] + 'repo' + str(y))

    ldiffile = open('./ldif-prepare-ezs-ldap.ldif', 'w')

    ldiffile.write("dn: ou=labor,ou=people,dc=hs-esslingen,dc=de\n")
    ldiffile.write("changetype: add\n")
    ldiffile.write("objectClass: organizationalUnit\n")
    ldiffile.write("objectClass: top\n")
    ldiffile.write("ou: labor\n")
    ldiffile.write('\n')

    gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)

    # fresh -> backup, list , delete, create, fill, add members
    # incremental -> add members

    if ( mode == "fresh" ):
        # -------------------------------------BACKUP
        answer = raw_input("Do you want a backup of the GIT repos (Y/N)")
        if answer == "Y":
            print "Backup GIT repos.. This can take a long time...."
        else:
            print "No Backup GIT repos"

        # -------------------------------------DELETE
        print "This will delete all the below listed student repos"
        projects = gl.projects.all(search='LaborAufgaben', sort='asc')
        number_of_projects = len(projects)
        for x in range(number_of_projects):
            print projects[x].name

        response = raw_input(
            "Proceed with delete (Y/N)")
        if response == "Y":
            for x in range(iterations):
                for y in range(maxrepos):
                    reponame = listofprojects[x][y]
                    print "deleting repo " + reponame
                    time.sleep(1)
                    # Get a project by ID
                    try:
                        project = gl.projects.get('LaborAufgaben/' + reponame)
                    except:
                        print "No repo %s found under LaborAufgaben, Skipping....." % (reponame)
                        continue
                    project.delete()

        time.sleep(1)

        # -------------------------------------CREATE and FILL
        user = "ezslab"
        password = "njn$43EL"
        curdir_save = os.getcwd()
        submodules_dir = curdir_save + '/' + '../submodules/template-repo'
        os.chdir(submodules_dir)
        print os.getcwd()
        subprocess.check_call(["git", "remote", "-v"])
        for x in range(iterations):
            for y in range(maxrepos):
                reponame = listofprojects[x][y]
                print "creating repo " + reponame
                project = gl.projects.create({'name': reponame, 'namespace_id': 10})
                time.sleep(1)
                template_repo_original = "https://vagrawal@gitlab.hs-esslingen.de/IT-Allgemein-LaborVerwaltung/template-repo.git"
                template_repo = "https://%s:%s@%s/LaborAufgaben/%s.git"% (user, password, gitlab_server_url, reponame)
                command = "git remote set-url origin " + template_repo
                print command
                subprocess.check_call(command.split(' '))
                subprocess.check_call("git push origin master".split(' '))
                print "Adding users"
                template_repo = "https://%s@%s/LaborAufgaben/%s.git" % (user, gitlab_server_url, reponame)
                command = "git remote set-url origin " + template_repo_original
                print command
                subprocess.check_call(command.split(' '))
                branch = project.branches.get('master')
                branch.protect()
                branch = project.branches.create({'branch_name': 'Work',
                                                  'ref': 'master'})

        os.chdir(curdir_save)

    # -------------------------------------ADD MEMBERS
    # both incremental and fresh
    for x in range(iterations):
        for y in range(maxrepos):
            groupname = listofgroups[x][y]
            reponame = listofprojects[x][y]
            try:
                groupmembers = cp.get('groups', groupname)
            except:
                print "No group entry for %s found in the authorization file, Skipping....." % (groupname)
                continue
            groupmembers = groupmembers.split(',')
            # print groupmembers

            # Delete existing team groups.
            # add the group and add group members
            ldiffile.write("dn: cn=" + groupname + ",ou=groups,dc=hs-esslingen,dc=de\n")
            ldiffile.write("changetype: delete\n")
            ldiffile.write('\n')
            # End of delete existing team groups.

            print "Creating group " + groupname + " and adding below members to the group for " + reponame
            # Create team groups.
            ldiffile.write("dn: cn=" + groupname + ",ou=groups,dc=hs-esslingen,dc=de\n")
            ldiffile.write("changetype: add\n")
            ldiffile.write("objectClass: groupOfNames\n")
            ldiffile.write("objectClass: top\n")
            ldiffile.write("description: group of lab students\n")
            ldiffile.write("cn: " + groupname + "\n")
            projectfound = gl.projects.get('LaborAufgaben/' + reponame)
            print "project found ", projectfound.id
            members = projectfound.members.list()
            if len(members) > 0:
                for number_of_members in range(len(members)):
                    members[number_of_members].delete()
            for i in range(len(groupmembers)):
                # Add members to team groups.
                membertoadd = groupmembers[i]
                membertoadd = membertoadd.strip(' ')
                if membertoadd != '':
                    ldiffile.write(
                        "member: cn= " + membertoadd + ",ou=labor,ou=people,dc=hs-esslingen,dc=de\n")
                    print membertoadd
                    memberfound = gl.users.list(username=membertoadd)
                    print "userfound", memberfound
                    if len(memberfound) > 0:
                        user = memberfound[0]
                        user_id = user.id
                    else:
                        print "Creating new member in GITLAB", membertoadd
                        user = gl.users.create({'email': membertoadd + '@hs-esslingen.de',
                                                'password': 'ezsiscool',
                                                'username': membertoadd,
                                                'name': membertoadd})
                        user_id = user.id
                    print user_id
                    member = projectfound.members.create(
                        {'user_id': user.id, 'access_level': gitlab.DEVELOPER_ACCESS})
                else:
                    ldiffile.write("member: cn=dummy,ou=labor,ou=people,dc=hs-esslingen,dc=de\n")
                    print "dummy"
                    # End of adding members to the team groups.
            ldiffile.write('\n')
            # End of create team groups.

            for i in range(len(groupmembers)):
                membertoadd = groupmembers[i]
                if membertoadd != '':
                    # Add team group members to LDAP
                    ldiffile.write(
                        "dn: cn=" + membertoadd + ",ou=labor,ou=people,dc=hs-esslingen,dc=de\n")
                    ldiffile.write("changetype: add\n")
                    ldiffile.write("givenName: Not configured\n")
                    ldiffile.write("sn: Not configured\n")
                    ldiffile.write("userPassword: ezsiscool\n")
                    ldiffile.write("mail: " + membertoadd + "@hs-esslingen.de\n")
                    ldiffile.write("objectClass: inetOrgPerson\n")
                    ldiffile.write("objectClass: organizationalPerson\n")
                    ldiffile.write("objectClass: person\n")
                    ldiffile.write("objectClass: top\n")
                    ldiffile.write("objectClass: pwmUser\n")
                    ldiffile.write("memberof: cn= " + groupname + ",ou=groups,dc=hs-esslingen,dc=de\n")
                    ldiffile.write("uid: " + membertoadd + "\n")
                    ldiffile.write("cn: " + membertoadd + "\n")
                    ldiffile.write('\n')
                    # End of add team group members to LDAP

if __name__ == '__main__':
    main()

# curl --header "PRIVATE-TOKEN: <my token>" -X POST "https://gitlab.com/api/v3/projects?name=foobartest8&namespace_id=10"
# curl --request POST --header "PRIVATE-TOKEN: $gitlab_server_TOKEN" https://gitlab.example.com/api/v3/projects/:id/members/:user_id?access_level=30
# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
# curl --request POST --header "PRIVATE-TOKEN: pHNJ8ksUCCssCDmtyZxh"
# https://wwwitrt.hs-esslingen.de:8443/api/v3/projects/:id/members/:user_id?access_level=30
# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
