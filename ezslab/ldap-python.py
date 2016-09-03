#!/bin/python
#-*- coding: utf-8 -*-

import ConfigParser
import sys
maxrepos = sys.argv[2]
maxrepos = int(maxrepos, 10)
iterations = int(sys.argv[1], 10) # $ITERATIONS
prefixrepolist = sys.argv[4]
cp = ConfigParser.ConfigParser()
authorizationfile = sys.argv[3] 
cp.read(authorizationfile)
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
print iterations, prefixrepolist, maxrepos, authorizationfile
print "finished"
listofgroups_prefix = prefixrepolist.split(',')
listofgroups = [ listofgroups_1, listofgroups_2, listofgroups_3, listofgroups_4, listofgroups_5, listofgroups_6,listofgroups_7, listofgroups_8, listofgroups_9, listofgroups_10 ]
for y in range(iterations):
	for x in range(1,maxrepos+1):
	    listofgroups[y].append(listofgroups_prefix[y] + 'group'+ str(x))
ldiffile = open('./ldif-prepare-ezs-ldap.ldif','w')
ldifmodfile = open('./ldif-prepare-ezs-ldapm.ldif','w')

if ('intern' in authorizationfile):
	currentOUunit="intern"
elif ('labor' in authorizationfile):
	currentOUunit="labor"
ldiffile.write( "dn: ou="+currentOUunit+",ou=people,dc=hs-esslingen,dc=de\n")
ldiffile.write( "changetype: add\n")
ldiffile.write( "objectClass: organizationalUnit\n")
ldiffile.write( "objectClass: top\n")
ldiffile.write( "ou: "+currentOUunit+"\n")
ldiffile.write('\n')

for y in range(iterations):
	for x in range(maxrepos):
		groupname = listofgroups[y][x]
		try:
                	groupmembers = cp.get('groups',groupname)
		except:
			print "No group entry for %s found in the authorization file, Skipping....." %(groupname)
		        continue	
		groupmembers = groupmembers.split(',')
		#print groupmembers

	#Delete existing team groups.
		# add the group and add group members
		ldiffile.write( "dn: cn=" + groupname + ",ou=groups,dc=hs-esslingen,dc=de\n")
		ldiffile.write( "changetype: delete\n")
		ldiffile.write('\n')
	#End of delete existing team groups.

		print "Creating group "+groupname + " and adding below members to the group"
	#Create team groups.
		ldiffile.write( "dn: cn=" + groupname + ",ou=groups,dc=hs-esslingen,dc=de\n")
		ldiffile.write( "changetype: add\n")
		ldiffile.write( "objectClass: groupOfNames\n")
		ldiffile.write( "objectClass: top\n")
		ldiffile.write( "description: group of lab students\n")
		ldiffile.write( "cn: "+ groupname + "\n")
		for i in range(len(groupmembers)):
	#Add members to team groups.
			membertoadd = groupmembers[i]
                        membertoadd = membertoadd.strip(' ')
			if ( membertoadd != '' ):
				ldiffile.write( "member: cn= " + membertoadd + ",ou="+currentOUunit+",ou=people,dc=hs-esslingen,dc=de\n")
				print membertoadd
			else:
				ldiffile.write( "member: cn=dummy,ou="+currentOUunit+",ou=people,dc=hs-esslingen,dc=de\n")
				print "dummy"
	#End of adding members to the team groups.
		ldiffile.write('\n')
	#End of create team groups.

		for i in range(len(groupmembers)):
			membertoadd = groupmembers[i]
			if ( membertoadd != '' ):

			#Add team group members to LDAP
				ldiffile.write("dn: cn=" + membertoadd + ",ou="+currentOUunit+",ou=people,dc=hs-esslingen,dc=de\n")
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
			#End of add team group members to LDAP

			#Modify members password to Standard Password
				ldifmodfile.write("dn: cn=" + membertoadd + ",ou="+currentOUunit+",ou=people,dc=hs-esslingen,dc=de\n")
				ldifmodfile.write("changetype: modify\n")
				ldifmodfile.write("replace: userpassword\n")
				ldifmodfile.write("userpassword: ezsiscool\n")
				ldifmodfile.write('\n')
			#End of modify members password

