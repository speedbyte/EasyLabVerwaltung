#!/usr/bin/env python
import argparse
import time
import datetime
import subprocess
import gitlab
import ConfigParser
import sys


cp = ConfigParser.ConfigParser()
cp_script = ConfigParser.ConfigParser()

cp_script.read('script-config.opt')

authorizationfile = sys.argv[1]

maxrepos = cp_script.get('labor', 'MAXREPOS')
maxrepos = int(maxrepos, 10)  # hack so that the script would run. string to int coversion problem

iterations = cp_script.get('labor', 'ITERATIONS')
iterations = int(iterations,10)  # $ITERATIONS . hack so that the script would run, string to int converstion problem

prefixrepolist = cp_script.get('labor', 'PREFIXREPOLIST')
gitlab_server_url = cp_script.get('labor', 'gitlab_server')
gitlab_server_token = cp_script.get('labor', 'gitlab_server_TOKEN')

cp.read(authorizationfile)

user = "ezslab"
password="njn\$43EL"
ldap_admin_password="marc276%!"
currentdate=datetime.date

git_option = 'n'
ldap_option = 'n'

def prepare_gitrepos_delete_repos():
    print "Do you want a backup of the GIT repos (Y/N)"
    answer = sys.stdin.readline()
    if answer == "Y":
        print "Backup GIT repos.. This can take a long time...."
        # git rename repos
    else
        print "Not Backup GIT repos.. This can take a long time...."
    count=1
    type='repo'
    
    for i in range(maxrepos*iterations):
        index=(i-1)/maxrepos
        prefixrepo=prefixrepolist[index]
        reponame=prefixrepo+type+str(count)
        if [ count > maxrepos ]:
            count=1
        else:
            count=count+1

        print "deleting repo "+ reponame
        url_join="curl --request DELETE --header "
        url_join+="PRIVATE-TOKEN:"+gitlab_server_TOKEN
        url_join+="https://"+gitlab_server+"/api/v3/projects/LaborAufgaben%2F"+reponame
        subprocess.check_call(url_join)
        time.sleep(1)
        url_join="curl --request GET --header "
        url_join+="PRIVATE-TOKEN:"+gitlab_server_TOKEN
        url_join+="https://"+gitlab_server+"/api/v3/projects/LaborAufgaben%2F"+reponame
        subprocess.check_call(url_join)
        time.sleep(1)
        #  curl --request POST --header "PRIVATE-TOKEN: $gitlab_server_TOKEN" https://gitlab.example.com/api/v3/projects/:id/members/:user_id?access_level=30

def prepare_gitrepos_create_repos():
    count=1
    type=repo
    cd ../submodules/template-repo
    print subprocess.check_call("git remote -v")
    for i in range(maxrepos*iterations):
        index=(i-1)/maxrepos
        prefixrepo=prefixrepolist[index]
        reponame=prefixrepo+type+str(count)
        if [ count > maxrepos ]:
            count=1
        else:
            count=count+1
        print "creating repo " + reponame
        url_join = "curl --header "
        url_join += "PRIVATE-TOKEN:" + gitlab_server_TOKEN
        url_join += "--data-urlencode name=" + reponame + "--data-urlencode namespace_id=10 https://$gitlab_server/api/v3/projects"
        subprocess.check_call(url_join)
        #curl --header "PRIVATE-TOKEN: <my token>" -X POST "https://gitlab.com/api/v3/projects?name=foobartest8&namespace_id=10"
        time.sleep(1)
        template_repo="https://"+user+":"+password+"@"+gitlab_server+"/LaborAufgaben/" + reponame + ".git"
        subprocess.check_call("git remote set-url origin",template_repo)
        subprocess.check_call("git push origin master")
        print "Adding users"
    #  curl --request POST --header "PRIVATE-TOKEN: $gitlab_server_TOKEN" https://gitlab.example.com/api/v3/projects/:id/members/:user_id?access_level=30
        subprocess.check_call("git remote set-url origin https://$user@$gitlab_server/LaborVerwaltung/template-repo.git")
        subprocess.check_call("cd ../../ezslab")



def trigger_ldap_gitlab_incremental():
    print "Adding and deleting groups and studentsnames in LDAP as per entries in authorization-file.opt.";
    ldap_python()


def ezslab_adduser(args):
    ''' Initialize config directories'''
    trigger_ldap_gitlab_incremental()
    ldapadd -x -c -S logs / ldapadd-error.log -D cn=admin, dc=hs-esslingen, dc=de -w marc276 % ! -f ldif-prepare-ezs-ldap.ldif

def ezslab_deluser(args):
    ''' Initialize config directories'''
    trigger_ldap_gitlab_incremental()
    ldapadd -x -c -S logs / ldapadd-error.log -D cn=admin, dc=hs-esslingen, dc=de -w marc276 % ! -f ldif-prepare-ezs-ldap.ldif

def ezslab_moduser(args):
    ''' Initialize config directories'''
    trigger_ldap_gitlab_incremental()
    ldapadd -x -c -S logs / ldapadd-error.log -D cn=admin, dc=hs-esslingen, dc=de -w marc276 % ! -f ldif-prepare-ezs-ldap.ldif

def ezslab_listusers(args):
    ''' Initialize config directories'''
    pass

def ezslab_flush(args):
    ''' Initialize config directories'''
    if git_option is "y" :
        prepare_gitrepos_delete_repos()
        time.sleep(10)
        prepare_gitrepos_create_repos()

    trigger_ldap_gitlab_incremental()

    if  ldap_option is "y" :
        grouptodelete="ou=labor,ou=people,dc=hs-esslingen,dc=de"
        print "deleting all members under $grouptodelete"
        ldapdelete -r -v -x -c -D cn=admin, dc=hs-esslingen, dc=de -w ldap_admin_password grouptodelete
        ldapadd -x -c -S logs/ldapadd-error.log -D cn=admin, dc=hs-esslingen, dc=de -w marc276 % ! -f ldif-prepare-ezs-ldap.ldif


def ezslab_sync(args):
    ''' Initialize config directories'''
    pass

def ezslab_git(args):
    ''' Initialize config directories'''
    git_option="y"

def ezslab_ldap(args):
    ''' Initialize config directories'''
    ldap_option="y"

def main():
    '''Main entry'''

    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(title='subcommands', description='')

    confdir_required = DEFAULT_CONF_DIR is None
    #while getopts ":l:jsgvf:h" opt; do
    conffile_required = 'authorizationfile.opt'


    # adduser
    parser_init = subparsers.add_parser('adduser', help='adds user to the ldap group')
    parser_init.set_defaults(func=ezslab_adduser)
    parser_init.add_argument('-u', '--user', help='the user id', type=str)
    parser_init.add_argument('-g', '--group', help='the group name', type=str)


    # adduser
    parser_init = subparsers.add_parser('deluser', help='delete the user from the ldap group')
    parser_init.set_defaults(func=ezslab_deluser)
    parser_init.add_argument('-u', '--user', help='the user id', type=str)
    parser_init.add_argument('-g', '--group', help='the group name', type=str)


    # modifyuser
    parser_init = subparsers.add_parser('moduser', help='add user to a new group')
    parser_init.set_defaults(func=ezslab_moduser)
    parser_init.add_argument('-u', '--user', help='the user id', type=str)
    parser_init.add_argument('-g', '--group', help='the new group name', type=str)

    # list-remote
    parser_download = subparsers.add_parser('listusers', help='list remote entries')
    parser_download.set_defaults(func=ezslab_listusers)
    parser_download.add_argument('-s', '--server', help='server on which to put the user', type=str)

    # git
    parser_download = subparsers.add_parser('git', help='do git')
    parser_download.set_defaults(func=ezslab_git)
    parser_download.add_argument('-g', '--gitlab', help='do git', type=str)

    # git
    parser_download = subparsers.add_parser('ldap', help='do ldap')
    parser_download.set_defaults(func=ezslab_ldap)
    parser_download.add_argument('-l', '--ldap', help='do ldap', type=str)

    # flush
    parser_download = subparsers.add_parser('flush', help='flush ldap users')
    parser_download.set_defaults(func=ezslab_flush)
    parser_download.add_argument('-s', '--server', help='server on which to flush all users', type=str)

    # sync
    parser_sync = subparsers.add_parser('sync', help='sync the authorization file, todo')
    parser_sync.set_defaults(func=ezslab_sync)
    parser_sync.add_argument('-c', '--conffile', help='the config file', type=str, required=conffile_required)
    parser_sync.add_argument('-s', '--server', help='URL for server', type=str)

    if len(sys.argv) == 1:
        print parser.format_help()
        return

    args = parser.parse_args()
    args.func(args)

def ldap_python():

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

    for y in range(iterations):
        for x in range(1, maxrepos + 1):
            listofgroups[y].append(listofgroups_prefix[y] + 'group' + str(x))
            listofprojects[y].append(listofprojects_prefix[y] + 'repo' + str(x))

    ldiffile = open('./ldif-prepare-ezs-ldap.ldif', 'w')
    ldifmodfile = open('./ldif-prepare-ezs-ldapm.ldif', 'w')

    currentOUunit = "labor"
    ldiffile.write("dn: ou=" + currentOUunit + ",ou=people,dc=hs-esslingen,dc=de\n")
    ldiffile.write("changetype: add\n")
    ldiffile.write("objectClass: organizationalUnit\n")
    ldiffile.write("objectClass: top\n")
    ldiffile.write("ou: " + currentOUunit + "\n")
    ldiffile.write('\n')

    git = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
    runners = git.runners.list()
    print runners[0].id

    for y in range(iterations):
        for x in range(maxrepos):
            groupname = listofgroups[y][x]
            reponame = listofprojects[y][x]
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

            print "Creating group " + groupname + " and adding below members to the group"
            # Create team groups.
            ldiffile.write("dn: cn=" + groupname + ",ou=groups,dc=hs-esslingen,dc=de\n")
            ldiffile.write("changetype: add\n")
            ldiffile.write("objectClass: groupOfNames\n")
            ldiffile.write("objectClass: top\n")
            ldiffile.write("description: group of lab students\n")
            ldiffile.write("cn: " + groupname + "\n")
            projectfound = git.projects.get('LaborAufgaben/' + reponame)
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
                        "member: cn= " + membertoadd + ",ou=" + currentOUunit + ",ou=people,dc=hs-esslingen,dc=de\n")
                    print membertoadd
                    if git_option == 'y':
                        memberfound = git.users.list(username=membertoadd)
                        print "userfound", memberfound
                        if len(memberfound) > 0:
                            user = memberfound[0]
                            user_id = user.id
                        else:
                            print "Creating new member in GITLAB", membertoadd
                            user = git.users.create({'email': membertoadd + '@hs-esslingen.de',
                                                     'password': 'ezsiscool',
                                                     'username': membertoadd,
                                                     'name': membertoadd})
                            user_id = user.id
                        print user_id
                        member = projectfound.members.create(
                            {'user_id': user.id, 'access_level': gitlab.DEVELOPER_ACCESS})
                else:
                    ldiffile.write("member: cn=dummy,ou=" + currentOUunit + ",ou=people,dc=hs-esslingen,dc=de\n")
                    print "dummy"
                    # End of adding members to the team groups.
            ldiffile.write('\n')
            # End of create team groups.

            for i in range(len(groupmembers)):
                membertoadd = groupmembers[i]
                if membertoadd != '':
                    # Add team group members to LDAP
                    ldiffile.write(
                        "dn: cn=" + membertoadd + ",ou=" + currentOUunit + ",ou=people,dc=hs-esslingen,dc=de\n")
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

                    # Modify members password to Standard Password
                    ldifmodfile.write(
                        "dn: cn=" + membertoadd + ",ou=" + currentOUunit + ",ou=people,dc=hs-esslingen,dc=de\n")
                    ldifmodfile.write("changetype: modify\n")
                    ldifmodfile.write("replace: userpassword\n")
                    ldifmodfile.write("userpassword: ezsiscool\n")
                    ldifmodfile.write('\n')
                    # End of modify members password

if __name__ == '__main__':
    main()

# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
# curl --header "PRIVATE-TOKEN: pHNJ8ksUCCssCDmtyZxh" --data-urlencode "name=ezsrepo4" --data-urlencode "namespace_id=10" "https://wwwitrt.hs-esslingen.de:8443/api/v3/projects"
# curl --request POST --header "PRIVATE-TOKEN: pHNJ8ksUCCssCDmtyZxh" https://wwwitrt.hs-esslingen.de:8443/api/v3/projects/:id/members/:user_id?access_level=30
# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif