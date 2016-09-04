# Beginning of GITLAB API
import gitlab
import os
import random
import string

dict_d = {'a':1, 'b':2, 'c':3}
print dict_d

user = os.environ.get('gitlab_user', 'root')
password = os.environ.get('gitlab_password', 'LigAlkUgCy')
host = os.environ.get('gitlab_host', 'https://wwwitrt3.hs-esslingen.de:8443')

print "hello"
git = gitlab.Gitlab(host)
git.login(user, password)
user = git.getusers(search="ezslab")[0]
user_id = user['id']
print user_id
#user_name = user['username']
#print user_id, user_name
#group = git.getgroups()[0]
#groupid = git.getgroupmembers(group["id"]) 
#print group
#newproject = self.git.createproject(name)
#list_of_all_projects = git.getprojectsall(page=2)
list_of_all_projects = git.getprojectsall()
#print list_of_all_projects
#print len(list_of_all_projects)	
try:
	for y in range(10):
		list_of_all_projects = git.getprojectsall(page=y)
		for x in range(20):
			project_name = list_of_all_projects[x]["name"]
			project_id = list_of_all_projects[x]["id"]
			#print project_id, project_name
			if ( "ezsrepo" in project_name  or  "sarepo" in project_name ):
				print project_id, project_name
except:
	print "No more pages"
	#project_id = project['id']
#name = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(8))
#print name
#newproject = git.createproject(name)
# set it as forker from the main project
#git.createforkrelation(newproject["id"], project_id)
#newproject = git.getproject(newproject["id"])

