#!/usr/bin/env python

import time
import datetime
import subprocess
import gitlab
import sys
import os

# gitlab v3

gitlab_server_url = 'wwwitrt.hs-esslingen.de:8443'
gitlab_server_token = 'Lzx9BbajbRkxhTZjknDt'
user = 'ezslab'
password = 'njn$43EL'


def delete_repos(gl, todo):
    if ( mode == "fresh" ):

        # -------------------------------------DELETE
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


def delete_repo(gl, reponame):
    # Get a project by ID
    try:
	project = gl.projects.get('LaborAufgaben/' + reponame)
	project.delete()
	print "successfully deleted " + project.id
    except:
	print "No repo %s found under LaborAufgaben, Skipping....." % (reponame)


def create_repo(gl, reponame):

       	templateURL="https://vagrawal@gitlab.hs-esslingen.de/IT-Allgemein-LaborVerwaltung/template-repo.git"
	 # -------------------------------------CREATE and FILL
        curdir_save = os.getcwd()
        submodules_dir = curdir_save + '/' + '../submodules/template-repo'
        os.chdir(submodules_dir)
        print os.getcwd()
        subprocess.check_call(["git", "remote", "-v"])
	print "creating repo " + reponame
	project = gl.projects.create({'name': reponame, 'namespace_id': 10})
	time.sleep(1)
	template_repo_original = templateURL
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
	branch = project.branches.create({'branch_name': 'Work', 'ref': 'master'})

        os.chdir(curdir_save)
	return project


def create_user(gl, membertoadd):

	theUserList = gl.users.list(username=membertoadd)
	if not theUserList: 
		print "Creating user " + membertoadd + " here..."
                userObject = {'email': membertoadd + '@hs-esslingen.de',
			'password': 'ezsiscool',
			'username': membertoadd,
			'name': membertoadd}
		theUser = gl.users.create(userObject)
		print "Created new user in GITLAB", membertoadd, theUser.id
	else:
		theUser = theUserList[0]
	return theUser.id


def manage_repo(gl, groupname, groupmembers, reponame):
	# -------------------------------------ADD MEMBERS
	# both incremental and fresh
	# Now find a project with the repo name
	try:
		repo = gl.projects.get('LaborAufgaben/' + reponame)
		print "project found ", repo.id
	except:#if ( repo == None ) :
		print "create a repo with repo name" 
		repo = create_repo(gl,reponame)
		
	actualmembers = repo.members.list()
	if len(actualmembers) > 0:
		for number_of_members in range(len(actualmembers)):
			actualmembers[number_of_members].delete()
 	groupmembers = groupmembers.split(',')
	for x in range(len(groupmembers)):
		membername = groupmembers[x].strip()
       		create_user(membername) # existing users are not re-created.
	        memberfound = gl.users.list(username=membername)
		time.sleep(1) 
		print memberfound
	        repo.members.create({'user_id': memberfound[0].id, 'access_level': gitlab.DEVELOPER_ACCESS})
			
	# End of create team groups.


if __name__ == '__main__':
	
	command = raw_input("Enter value to test - choices are manage_repo, delete_repo, flush_repos, create_repo, create_user :  ")
	print command
	if ( command == "manage_repo"):
		gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
		groupname = "atest_group_test1" 
		groupmembers = "XXXXit00, YYYYit00" 
		reponame = "ctest_repo_test1" 
		manage_repo(gl, groupname, groupmembers, reponame)
	elif ( command == "delete_repo"):
		gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
		groupname = "atest_group_test1" 
		groupmembers = "XXXXit00, YYYYit00" 
		reponame = "ctest_repo_test1" 
		delete_repo(gl, reponame)
	elif ( command == "create_repo"):
		gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
		groupname = "atest_group_test1" 
		groupmembers = "XXXXit00, YYYYit00" 
		reponame = "ctest_repo_test1" 
		create_repo(gl, reponame)
	elif ( command == "flush_repos"):
		gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
		groupname = "atest_group_test1" 
		groupmembers = "XXXXit00, YYYYit00" 
		reponame = "ctest_repo_test1" 
		flush_repois(gl, reponame)
	elif ( command == "create_user"):
		gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
		groupname = "atest_group_test1" 
		groupmembers = "XXXXit00, YYYYit00" 
		username = "ZZZZit00" 
		create_user(gl, username)
	else:
		print "nothing to do  - aborting...."

# curl --header "PRIVATE-TOKEN: <my token>" -X POST "https://gitlab.com/api/v3/projects?name=foobartest8&namespace_id=10"
# curl --request POST --header "PRIVATE-TOKEN: $gitlab_server_TOKEN" https://gitlab.example.com/api/v3/projects/:id/members/:user_id?access_level=30
# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
# curl --request POST --header "PRIVATE-TOKEN: pHNJ8ksUCCssCDmtyZxh"
# https://wwwitrt.hs-esslingen.de:8443/api/v3/projects/:id/members/:user_id?access_level=30
# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
