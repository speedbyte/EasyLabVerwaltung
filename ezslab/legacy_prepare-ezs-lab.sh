#!/bin/bash
# _*_ coding: utf-8 _*_

if [ "$(hostname)" == "itlx3304" ]; then
	EZSLAB_PERSONAL_TOKEN=Lzx9BbajbRkxhTZjknDt
	EZSLAB_GITLAB_SERVER=wwwitrt4.hs-esslingen.de:8443
elif [ "$(hostname)" == "itlx3354" ]; then
	EZSLAB_PERSONAL_TOKEN=Lzx9BbajbRkxhTZjknDt
	EZSLAB_GITLAB_SERVER=wwwitrt.hs-esslingen.de:8443
fi
echo $EZSLAB_PERSONAL_TOKEN
echo $EZSLAB_GITLAB_SERVER 
exit

GIT_OPTION="n"
 
while getopts ":l:jsgvf:h" opt; do
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
      if [ "" == "$LDAP_PARAMETER" ]; then 
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
    g)
      echo "-g was triggered, Parameter: $OPTARG" >&2
      echo "git function enabled" >&2
      GIT_OPTION="y"
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
      -g \
      -f \
       " 
      echo
      echo "=====> Option -l has one mandatory argument, either fresh or incremental. Arguement fresh will delete all the entries in LDAP under ou=labor,ou=people and Arguement incremental will not delete any entry in LDAP, but modify the entries under ou=groups and additionally add members if not already present in LDAP" 
      echo
      echo "=====> use this option -j if you want to recreate jenkins jobs. This option can only be used in combination with -l fresh option. Beware that all jenkins jobs would be put in the backup folder and new jenkins jobs would be created." 
      echo
      echo "=====> use this option -s if you want to recreate svn repos. This option can only be used in combination with -l fresh option. Beware that all svn repos would be put in the backup folder and new svn repos would be created." 
      echo
      echo "=====> use this option -g if you want to create git repos. This option can only be used in combination with -l fresh option." 
      echo "=====> The LDAP entries are added / modified / deleted after reading the entry in the authorization file"
      echo
      echo "=====> use this option -f to explicitly select the authorization file" 
      echo "=====> The LDAP entries are added / modified / deleted after reading the entry in the authorization file"
      echo "Please see the file authorization file ( normally authorization-file.opt )  for more information"
      exit 1
      ;;
    f)
      echo "-f was triggered, Parameter: $OPTARG" >&2
      if [ -f $OPTARG ]; then
          echo "$OPTARG Authorization file found"
          AUTHORIZATIONFILE=$OPTARG
      fi
      else
          echo "$OPTARG Authorization file not found" 
          exit 1
      fi
      ;;  
    v)
      echo "-v was triggered, Parameter: $OPTARG" >&2
      VERBOSE='ON'
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
MAXREPOS=35
PREFIXREPOLIST=( "ezs-stud-" "sa-stud-" ) # you can add upto 10 labs here
ITERATIONS=${#PREFIXREPOLIST[@]}
SVNREPOS=/var/repos/LABOR


#source script-config.opt
JENKINS=/usr/share/tomcat7/.jenkins
ADMINDIR=$(pwd)/..
LDAP=/etc/ldap
currentdate=$(date +"%0Y%0m%0d-%0H%0M%0S")
if [ "$VERBOSE" == "ON" ]; then do_verbose='-v'; else do_verbose=''; fi

function 1_prepare_svnrepos
{
echo "-----------------SVN LOG ------------------------\n\n" > logs/lab-svn.log
SVNGROUP=svn
echo "Do you want a backup of the SVN repos (Y/N)"
read ANSWER
if [ "ANSWER" == "Y" ]; then
 echo "Backup SVN repos.. This can take a long time...."
 mv $do_verbose $SVNREPOS $ADMINDIR/svn/backups/repos-$currentdate>>logs/lab-svn.log 
else
 rm -rf $do_verbose $SVNREPOS>>logs/lab-svn.log 
fi

mkdir -p $do_verbose $SVNREPOS>>logs/lab-svn.log
if [ -d $SVNREPOS/examples-repo ]; then rm -rf $SVNREPOS/examples-repo>>logs/lab-svn.log; fi 
svnadmin create --fs-type fsfs $SVNREPOS/examples-repo
svnadmin load $SVNREPOS/examples-repo < $ADMINDIR/svn/ezsrepo-svn-examples.dump>>logs/lab-svn.log
chown -R $do_verbose root:svn $SVNREPOS/examples-repo>>logs/lab-svn.log
chmod -R $do_verbose 770 $SVNREPOS/examples-repo>>logs/lab-svn.log
count=1
type=repo
for ((i=1;i<=$(($MAXREPOS*$ITERATIONS));i++));
do
  index=$(($(($i-1))/$MAXREPOS))
  PREFIXREPO=${PREFIXREPOLIST[$index]}
  g=$PREFIXREPO$type$count
  if [ $count -ge $MAXREPOS ]; then count=1; else count=$(($count+1)); fi
  echo "Creating svn repo $g"
  if [ ! -d $SVNREPOS ]; then mkdir -p $do_verbose $SVNREPOS>>logs/lab-svn.log; fi
  if [ -d $SVNREPOS/$g ]; then rm -rf $SVNREPOS/$g>>logs/lab-svn.log; fi 
  svnadmin create --fs-type fsfs $SVNREPOS/$g
  svnadmin load $SVNREPOS/$g < $ADMINDIR/svn/ezsrepo-svn-template.dump>>logs/lab-svn.log
  chown -R $do_verbose root:svn $SVNREPOS/$g>>logs/lab-svn.log
  chmod -R $do_verbose 770 $SVNREPOS/$g>>logs/lab-svn.log
  echo "Completed preparing $g"
  echo
done
echo -----------SVN REPOS under $SVNREPOS-------------------
find /var/repos/LABOR -maxdepth 1 -type d  -printf '%T@ %P\n' | sort -n |  awk '/[a-zA-Z]/{print}'
echo
}

function 3_prepare_gitrepos_delete_repos
{
echo "Do you want a backup of the GIT repos (Y/N)"
read ANSWER
if [ "ANSWER" == "Y" ]; then
 echo "Backup GIT repos.. This can take a long time...."
 # git rename repos
else
 echo "Not Backup GIT repos.. This can take a long time...."
fi
user=ezslab
pass="njn\$43EL"
count=1
type=repo
DUMMYMAXREPOS=35
for ((i=1;i<=$(($DUMMYMAXREPOS*$ITERATIONS));i++));
do
  index=$(($(($i-1))/$DUMMYMAXREPOS))
  PREFIXREPO=${PREFIXREPOLIST[$index]}
  g=$PREFIXREPO$type$count
  if [ $count -ge $DUMMYMAXREPOS ]; then count=1; else count=$(($count+1)); fi
  echo "deleting project $g" 
  curl --request DELETE --header "PRIVATE-TOKEN: $EZSLAB_PERSONAL_TOKEN" "https://$EZSLAB_GITLAB_SERVER/api/v3/projects/LaborAufgaben%2F$g"
  wait ${!}
  echo
  curl --request GET --header "PRIVATE-TOKEN: $EZSLAB_PERSONAL_TOKEN" "https://$EZSLAB_GITLAB_SERVER/api/v3/projects/LaborAufgaben%2F$g"
  wait ${!}
  echo
#  curl --request POST --header "PRIVATE-TOKEN: $EZSLAB_PERSONAL_TOKEN" https://gitlab.example.com/api/v3/projects/:id/members/:user_id?access_level=30
done 
}

function 3_prepare_gitrepos_create_repos
{
user=ezslab
pass="njn\$43EL"
count=1
type=repo
cd ../submodules/template-repo
echo $(git remote -v)
for ((i=1;i<=$(($MAXREPOS*$ITERATIONS));i++));
do
  index=$(($(($i-1))/$MAXREPOS))
  PREFIXREPO=${PREFIXREPOLIST[$index]}
  g=$PREFIXREPO$type$count
  if [ $count -ge $MAXREPOS ]; then count=1; else count=$(($count+1)); fi
  echo "Creating project $g"
  curl --header "PRIVATE-TOKEN: $EZSLAB_PERSONAL_TOKEN" --data-urlencode "name=$g" --data-urlencode "namespace_id=10" "https://$EZSLAB_GITLAB_SERVER/api/v3/projects"
  #curl --header "PRIVATE-TOKEN: <my token>" -X POST "https://gitlab.com/api/v3/projects?name=foobartest8&namespace_id=10"
  wait ${!}
  echo
  git remote set-url origin https://$user:$pass@$EZSLAB_GITLAB_SERVER/LaborAufgaben/"$g".git
  git push origin master
#  echo "Adding users"
#  curl --request POST --header "PRIVATE-TOKEN: $EZSLAB_PERSONAL_TOKEN" https://gitlab.example.com/api/v3/projects/:id/members/:user_id?access_level=30
done 
git remote set-url origin https://$user@$EZSLAB_GITLAB_SERVER/LaborVerwaltung/template-repo.git
cd ../../ezslab
}


function 2_prepare_jenkins
{
echo "-----------------JENKINS LOG ------------------------\n\n" > logs/lab-jenkins.log
SJENKINSGROUP=tomcat7

rm -rf $ADMINDIR/jenkins/template/*>>logs/lab-jenkins.log
mv $do_verbose $JENKINS/jobs/template/config.xml $ADMINDIR/jenkins/template/>>logs/lab-jenkins.log
chown -R $(whoami):$(whoami) $ADMINDIR/jenkins/template/ 
echo "Do you want a backup of the Jenkins jobs (Y/N)"
read ANSWER
if [ "ANSWER" == "Y" ]; then
 echo "Backup Jenkins jobs.. This can take a long time...."
 mv $JENKINS/jobs $ADMINDIR/jenkins/backups/jobs-$currentdate>>logs/lab-jenkins.log
else
 rm -rf $do_verbose $JENKINS/jobs>>logs/lab-jenkins.log
fi
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
  cp -r $do_verbose $JENKINS/jobs/template $JENKINS/jobs/$g>>logs/lab-jenkins.log && sed -i.bak s/templategroup/$h/g $JENKINS/jobs/$g/config.xml>>logs/lab-jenkins.log && sed -i.bak s/template-repo/$r/g $JENKINS/jobs/$g/config.xml>>logs/lab-jenkins.log  && sed -i.bak s/Verwaltung/Aufgaben/g $JENKINS/jobs/$g/config.xml>>logs/lab-jenkins.log && rm -r $do_verbose $JENKINS/jobs/$g/config.xml.bak>>logs/lab-jenkins.log && chown -R $do_verbose tomcat7:tomcat7 $JENKINS/jobs/$g>>logs/lab-jenkins.log
  echo "Created jenkins jobs $h"
done
echo -----------JENKINS JOBS under $JENKINS/jobs/-------------------
find $JENKINS/jobs -maxdepth 1 -type d  -printf '%T@ %P\n' | sort -n |  awk '/[a-zA-Z]/{print}'
}

function 3_prepare_ldap
{
    #Script to add ldap groups in the ldap 
    #python << EOF > logs/log-prepare-ezs-python.log  2>&1
    python ldap_python.py $AUTHORIZATIONFILE $GIT_OPTION
    #EOF
}

rm -f logs/*
if [ "fresh" == "$LDAP_PARAMETER" ]; then
    if [ "y" == "$SVN_OPTION" ]; then 
        1_prepare_svnrepos; 
    fi
    if [ "y" == "$JENKINS_OPTION" ]; then 
        2_prepare_jenkins; 
    fi
    if [ "y" == "$GIT_OPTION" ]; then 
        3_prepare_gitrepos_delete_repos;
        sleep 10;
        3_prepare_gitrepos_create_repos;
    fi
fi
if [ "$LDAP_OPTION" == "y" ]; then 
    echo "Adding and deleting groups and studentsnames in LDAP as per entries in authorization-file.opt."; 
    3_prepare_ldap
    if [ "fresh" == "$LDAP_PARAMETER" ]; then
        grouptodelete="ou=labor,ou=people,dc=hs-esslingen,dc=de"
        echo "deleting all members under $grouptodelete"
        ldapdelete -r -v -x -c -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! $grouptodelete
        ldapadd -x -c -S logs/ldapadd-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldap.ldif
        #ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
    elif [ "incremental" == "$LDAP_PARAMETER" ]; then
        ldapadd -x -c -S logs/ldapadd-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldap.ldif
        #ldapadd -x -c -S logs/ldapmodify-error.log -D cn=admin,dc=hs-esslingen,dc=de -w marc276%! -f ldif-prepare-ezs-ldapm.ldif
    fi
    else
        if [ "y" == "$JENKINS_OPTION" ]; then
            2_prepare_jenkins;
        fi
    fi
    echo "Following log-files has been generated"
    ls -lt logs/
    #curl --header "PRIVATE-TOKEN: pHNJ8ksUCCssCDmtyZxh" --data-urlencode "name=ezsrepo4" --data-urlencode "namespace_id=10" "https://wwwitrt.hs-esslingen.de:8443/api/v3/projects"
    #curl --request POST --header "PRIVATE-TOKEN: pHNJ8ksUCCssCDmtyZxh" https://wwwitrt.hs-esslingen.de:8443/api/v3/projects/:id/members/:user_id?access_level=30
