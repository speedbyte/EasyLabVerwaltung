#!/usr/bin/env python

import time
import datetime
import subprocess
import gitlab
import sys
import os
import SimpleXMLRPCServer

# gitlab v3

gitlab_server_url = 'wwwitrt.hs-esslingen.de:8443'
gitlab_server_token = 'Lzx9BbajbRkxhTZjknDt'
user = 'ezslab'
password = 'njn$43EL'


def delete_repos():
    if ( mode == "fresh" ):
        # -------------------------------------BACKUP
        answer = raw_input("Do you want a backup of the GIT repos (Y/N)")
        if answer == "Y":
            print "Backup GIT repos.. This can take a long time...."
        else:
            print "No Backup GIT repos"

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


def delete_repo(reponame):
    # Get a project by ID
    try:
	project = gl.projects.get('LaborAufgaben/' + reponame)
    except:
	print "No repo %s found under LaborAufgaben, Skipping....." % (reponame)
    project.delete()


def create_gitlab_repo(gl, reponame, templateURL):
        print "In create_gitlab_repo"
        # -------------------------------------CREATE and FILL
        curdir_save = os.getcwd()
        print "1 " + os.getcwd()
        submodules_dir = curdir_save + '/' + '../submodules/template-repo'
        os.chdir(submodules_dir)
        print "2 " + os.getcwd()
        subprocess.check_call(["git", "remote", "-v"])
	print "Creating repo " + reponame
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
	except:
		print "Create a repo 1 with repo name " + reponame
		templateURL="https://vagrawal@gitlab.hs-esslingen.de/IT-Allgemein-LaborVerwaltung/template-repo.git"
		repo = create_gitlab_repo(gl, reponame,templateURL)
		
	actualmembers = repo.members.list()
	if len(actualmembers) > 0:
		for number_of_members in range(len(actualmembers)):
			actualmembers[number_of_members].delete()
 	groupmembers = groupmembers.split(',')
	for x in range(len(groupmembers)):
		membername = groupmembers[x].strip()
       		create_user(gl, membername) # existing users are not re-created.
	        memberfound = gl.users.list(username=membername)
		time.sleep(1) 
		print memberfound
	        repo.members.create({'user_id': memberfound[0].id, 'access_level': gitlab.MASTER_ACCESS})
			
	# End of create team groups.



#This method is being fired after a user profile has been saved. 
#The password parameter contains the plain password if it was reset or register otherwise the password is an empty String
#Context parameter possible values are: 
#SELFREGISTRATION = 0; PROFILEEDIT = 1; USERADMINADD = 2; USERADMINEDIT = 3;
def postUserProfileSaveHandler(map):
	print("postUserProfileSaveHandler: ")
	print " objectID: " + map["objectID"]
	print " Login name: " + map["loginName"]
	print " First name: " + map["firstName"]	
	print " Last name: " + map["lastName"] 
	print " Email: " + map["email"]	
	print " Password: " + map["password"]
	print " Context: " + map["context"]
	return True
	
#This method is being fired after a group has been saved or group members has been changed.
#The members attribute is either empty (=the group does not contain members) or a comma separated id list like: 100,102
def postGroupSaveHandler(map):
        reponame = map["name"]
	reponame = reponame.replace(" ","-").lower()
	print "Group " + map["name"] + " has changed: "+ reponame + " " +  map["members"] 
        manage_repo(gl, map["name"], map["members"], reponame) 
	return True

#This method is being fired when user(s) are deleted from the system.
def postUserDeleteHandler(map):
	print("postUserDeleteHandler: ")
	print " objectIDS: " + map["objectIDs"]
	return True

#This method is being fired when group(s) are deleted from the system.	
def postGroupDeleteHandler(map):
	print("postGroupDeleteHandler: ")
	print " objectIDS: " + map["objectIDs"]
	return True
	
def main():
	print "Track+ XML-RPC demo server started"
	server = SimpleXMLRPCServer.SimpleXMLRPCServer(("127.0.0.1", 8001))							
	server.register_function(postUserProfileSaveHandler)
	server.register_function(postGroupSaveHandler)	
	server.register_function(postUserDeleteHandler)
	server.register_function(postGroupDeleteHandler)
	print "Press ctrl+c to stop the server!"
	server.serve_forever()
	
	
if __name__ == "__main__":
	gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
	main()

#if __name__ == '__main__':
#	gl = gitlab.Gitlab('https://' + gitlab_server_url, gitlab_server_token)
	
#	groupname = "atest_group_test1" #listofgroups[x][y]
#	groupmembers = "XXXXit00, YYYYit00" 
#	reponame = "ctest_repo_test1" #listofprojects[x][y]
#	manage_repo(gl, groupname, groupmembers, reponame)

# curl --header "PRIVATE-TOKEN: <my token>" -X POST "https://gitlab.com/api/v3/projects?name=foobartest8&namespace_id=10"
# curl --request POST --header "PRIVATE-TOKEN: $gitlab_server_TOKEN" https://gitlab.example.com/api/v3/projects/:id/members/:user_id?access_level=30
# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
# curl --request POST --header "PRIVATE-TOKEN: pHNJ8ksUCCssCDmtyZxh"
# https://wwwitrt.hs-esslingen.de:8443/api/v3/projects/:id/members/:user_id?access_level=30
# ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
