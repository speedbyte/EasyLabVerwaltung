#!/bin/bash

while getopts ":l:jsf:h" opt; do
  case $opt in
    l)
      echo "-l was triggered, Parameter: $OPTARG" >&2
      LDAP_OPTION="y"
      LDAP_PARAMETER=$OPTARG
      if (( "fresh" != "$LDAP_PARAMETER" || "incremental" != "$LDAP_PARAMETER" )); then
      	  echo "-l expects only following two parameters: fresh or incremental. Type -h for more information. Exiting script"
	  exit 1
      fi
      ;;
    j)
      echo "-j was triggered, Parameter: $OPTARG" >&2
      if [ "fresh" == "$LDAP_PARAMETER" ]; then 
      	  echo "jenkins jobs would be generated" >&2
          JENKINS_OPTION="y"
      else
	  echo "This option can only be used in combination with -l fresh. Type -h for more information. Exiting Script"
          exit 1
      fi
      ;;
    s)
      echo "-s was triggered, Parameter: $OPTARG" >&2
      if [ "fresh" == "$LDAP_PARAMETER" ]; then 
          echo "svn repos would be generated" >&2
          SVN_OPTION="y"
      else
	  echo "This option can only be used in combination with -l fresh. Type -h for more information. Exiting Script"
          exit 1
      fi
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    h)
      echo "Options are \
      -l fresh or -l incremental \
      -j \
      -s \
      -h \
      -f \
       " 
      echo
      echo "=====> use this option -f to explicitly select the authorization file" 
      echo
      echo "=====> use this option -j if you want to recreate jenkins jobs. This option can only be used in combination with -l fresh option. Beware that all jenkins jobs would be put in the backup folder and new jenkins jobs would be created." 
      echo
      echo "=====> use this option -s if you want to recreate svn repos. This option can only be used in combination with -l fresh option. Beware that all svn repos would be put in the backup folder and new svn repos would be created." 
      echo
      echo "=====> Option -l has one mandatory argument, either fresh or incremental. Arguement fresh will delete all the entries in LDAP under ou=labor,ou=people and Arguement incremental will not delete any entry in LDAP, but modify the entries under ou=groups and additionally add members if not already present in LDAP" 
      echo
      echo "=====> The LDAP entries are added / modified / deleted after reading the entry in the authorization file"
      echo "Please see the file authorization file ( normally authorization-file.opt )  for more information"
      exit 1
      ;;
    f)
      echo "-f was triggered, Parameter: $OPTARG" >&2
      if [ -f $OPTARG ]; then
	  echo "$OPTARG Authorization file found"
          AUTHORIZATIONFILE=$OPTARG
          AUTHORIZATIONGROUP=$(echo $AUTHORIZATIONFILE | cut -d. -f1 | sed s/authorization-file-//g)
	  if [ "$AUTHORIZATIONGROUP" != "intern" ] && [ "$AUTHORIZATIONGROUP" != "labor" ]; then
		echo "Either labor or intern authorization file is required.. Exiting"
		exit 1
	  fi
      else
          echo "$OPTARG Authorization file not found" 
          exit 1
      fi
      ;;		
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

if [ $# -eq 0 ]; then
	echo "The script takes a minimum of one arguement, 0 given. Please type -h to see the help file"
        exit 1
fi
# Script to generate Subversion repositories for HE project
#
if [ "$AUTHORIZATIONGROUP" == "intern" ]; then
	MAXREPOS=1   #each entry in PREFIXREPOLIST would be generated MAXREPOS times
	PREFIXREPOLIST=( "helikopterdev" "ezslabscriptsdev" "trackplusdev" ) # you can add upto 10 labs here
	ITERATIONS=${#PREFIXREPOLIST[@]}
	SVNREPOS=/var/repos/INTERN
else
	MAXREPOS=25
	PREFIXREPOLIST=( "ezs" "sa" ) # you can add upto 10 labs here
	ITERATIONS=${#PREFIXREPOLIST[@]}
	SVNREPOS=/var/repos/LABOR
fi
JENKINS=/usr/share/tomcat7/.jenkins
ADMINDIR=$HOME
LDAP=/etc/ldap
currentdate=$(date +"%0Y%0m%0d-%0H%0M%0S")
if [ "-v" == $1 ]
then
  VERBOSE='on'
fi
if [ "$VERBOSE" == "on" ]; then do_verbose='-v'; else do_verbose=''; fi

function 1_prepare_svnrepos
{
echo "-----------------SVN LOG ------------------------\n\n" > logs/lab-svn.log
SVNGROUP=svn
BACKUPSVNREPO=$ADMINDIR/svn/backups/repos-$currentdate
mv $do_verbose $SVNREPOS $BACKUPSVNREPO>>logs/lab-svn.log 
mkdir $do_verbose $SVNREPOS>>logs/lab-svn.log
cp -R $do_verbose $ADMINDIR/svn/template /var/repos/LABOR/>>logs/lab-svn.log
chown -R $do_verbose root:svn $SVNREPOS/template>>logs/lab-svn.log
chmod -R $do_verbose 770 $SVNREPOS/template>>logs/lab-svn.log
count=1
type=repo
for ((i=1;i<=$(($MAXREPOS*$ITERATIONS));i++));
do
  index=$(($(($i-1))/$MAXREPOS))
  PREFIXREPO=${PREFIXREPOLIST[$index]}
  g=$PREFIXREPO$type$count
  if [ $count -ge $MAXREPOS ]; then count=1; else count=$(($count+1)); fi
  echo "Creating svn repo $g"
  if [ ! -d $SVNREPOS ]; then mkdir $do_verbose $SVNREPOS>>logs/lab-svn.log; fi
  if [ -d $SVNREPOS/$g ]; then rm -rf $SVNREPOS/$g>>logs/lab-svn.log; fi 
  svnadmin create --fs-type fsfs $SVNREPOS/$g
  svnadmin load $SVNREPOS/$g < ezsrepo-template.dump>>logs/lab-svn.log
  #svn mkdir file:///$SVNREPOS/$g/docs -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/docs/pm -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/docs/se -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/docs/qa -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/docs/cm -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/scratch -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/impl -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/impl/Application -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/impl/HAL-Host -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/impl/HAL-Target -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/impl/IDE-Host -q --message "Initial commit"
  #svn mkdir file:///$SVNREPOS/$g/impl/IDE-Target -q --message "Initial commit"
  #svn import -m "Initial commit" /var/repos/validatebuild.sh file:///$SVNREPOS/$g/impl/IDE-Host/validatebuild.sh        
  chgrp -R $do_verbose svn $SVNREPOS/$g>>logs/lab-svn.log
  chmod -R $do_verbose 770 $SVNREPOS/$g>>logs/lab-svn.log
  echo "Completed preparing $g"
  echo
done
echo -----------SVN REPOS under $SVNREPOS-------------------
find /var/repos/LABOR -maxdepth 1 -type d  -printf '%T@ %P\n' | sort -n |  awk '/[a-zA-Z]/{print}'
echo
}

function 2_prepare_jenkins
{
echo "-----------------JENKINS LOG ------------------------\n\n" > logs/lab-jenkins.log
SJENKINSGROUP=tomcat7

rm -rf $ADMINDIR/jenkins/template/*>>logs/lab-jenkins.log
mv $do_verbose $JENKINS/jobs/template/*.* $ADMINDIR/jenkins/template/>>logs/lab-jenkins.log
mv $JENKINS/jobs $ADMINDIR/jenkins/backups/jobs-$currentdate>>logs/lab-jenkins.log
mkdir $JENKINS/jobs>>logs/lab-jenkins.log
cp -r $do_verbose $ADMINDIR/jenkins/template  $JENKINS/jobs/>>logs/lab-jenkins.log
chown -R tomcat7:tomcat7 $JENKINS/jobs>>logs/lab-jenkins.log
chown -R $do_verbose tomcat7:tomcat7 $JENKINS/jobs/template>>logs/lab-jenkins.log

count=1
type=job
group=group
repo=repo
for ((i=1;i<=$(($MAXREPOS*$ITERATIONS));i++));
do
  index=$(($(($i-1))/$MAXREPOS))
  PREFIXREPO=${PREFIXREPOLIST[$index]}
  g=$PREFIXREPO$type$count
  h=$PREFIXREPO$group$count
  r=$PREFIXREPO$repo$count
  if [ $count -ge $MAXREPOS ]; then count=1; else count=$(($count+1)); fi
  cp -r $do_verbose $JENKINS/jobs/template $JENKINS/jobs/$g>>logs/lab-jenkins.log && sed -i.bak s/templategroup/$h/g $JENKINS/jobs/$g/config.xml>>logs/lab-jenkins.log && sed -i.bak s/templaterepo/$r/g $JENKINS/jobs/$g/config.xml>>logs/lab-jenkins.log && rm -r $do_verbose $JENKINS/jobs/$g/config.xml.bak>>logs/lab-jenkins.log && chown -R $do_verbose tomcat7:tomcat7 $JENKINS/jobs/$g>>logs/lab-jenkins.log
done
echo -----------JENKINS JOBS under $JENKINS/jobs/-------------------
find $JENKINS/jobs -maxdepth 1 -type d  -printf '%T@ %P\n' | sort -n |  awk '/[a-zA-Z]/{print}'
}

function 3_prepare_ldap
{
#Script to add ldap groups in the ldap 
#python 3-prepare-ldap.py
python << EOF > logs/log-prepare-ezs-python.log  2>&1
#!/bin/python
#-*- coding: utf-8 -*-

import ConfigParser
maxrepos = int('$MAXREPOS', 10)
iterations = $ITERATIONS
cp = ConfigParser.ConfigParser()
authorizationfile = "$AUTHORIZATIONFILE"
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

listofgroups_prefix = [ "${PREFIXREPOLIST[0]}","${PREFIXREPOLIST[1]}","${PREFIXREPOLIST[2]}","${PREFIXREPOLIST[3]}","${PREFIXREPOLIST[4]}","${PREFIXREPOLIST[5]}","${PREFIXREPOLIST[6]}","${PREFIXREPOLIST[7]}","${PREFIXREPOLIST[8]}","${PREFIXREPOLIST[9]}","${PREFIXREPOLIST[10]}"]    
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
				ldiffile.write("mail: Not configured\n")
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
EOF
}


rm -f logs/*
if [ "$LDAP_OPTION" == "y" ]; then 
    echo "Adding and deleting groups and studentsnames in LDAP as per entries in authorization-file.opt."; 
    3_prepare_ldap
    if [ "fresh" == "$LDAP_PARAMETER" ]; then
	grouptodelete="ou=$AUTHORIZATIONGROUP,ou=people,dc=hs-esslingen,dc=de"
	if [ "$grouptodelete" == "labor" ]; then
	        echo "deleting all members under $grouptodelete"
	        ldapdelete -r -v -x -c -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! $grouptodelete
	fi
	ldapadd -x -c -S logs/ldapadd-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldap.ldif
        #ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
        cat logs/log-prepare-ezs-python.log;
    elif [ "incremental" == "$LDAP_PARAMETER" ]; then
	ldapadd -x -c -S logs/ldapadd-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldap.ldif
        #ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
        cat logs/log-prepare-ezs-python.log;
    fi
fi
if [ "fresh" == "$LDAP_PARAMETER" ]; then
    if [ "y" == "$SVN_OPTION" ]; then 
        1_prepare_svnrepos; 
    fi
    if [ "y" == "$JENKINS_OPTION" ]; then 
        2_prepare_jenkins; 
    fi
fi
echo "Following log-files has been generated"
ls -lt logs/


