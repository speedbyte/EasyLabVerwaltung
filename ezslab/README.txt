All the files are under the SVN version control

PREPARE

----------------------
This is a read me to prepare the ezs lab.

The first thing is to change the authorization-file.opt and enter the ids of the students.
Then the file prepare-ezs-lab.sh has to be called by issuing the command sudo bash prepare-ezs-lab.sh.
The execution of the file is done in 4 stages:

STAGE 1

First stage is if you want to switch on the verbose or not. Type 'on' for verbose on and 'off' for verbose off.
If you have verbose as on, all the commands are executed with -v option otherwise there is no verbose of the executed commands. 
The stdout is sent to the folder logs/. However stderr is still on the console.
 
STAGE 2 

This stage is to delete and create the entries in the LDAP. This stage reads the file authorizatzion-file.opt
and creates new ldap entries under ou=students,ou=people,dc=hs-esslingen,dc=de. The students are automatically assigned the group membership.
In this stage, type freshldap if you want to delete all the students and start from fresh. If you are doing everything from 
scratch, then further stages ( svn and jenkins ) would be processed otherwise not.
The default is that you want to add or delete individual members.

STAGE 3

You come in this stage only if you have opted for a freshldap.
This stage is the deletion and the creation of the svn repositories. You will be prompted if you want to continue 
this step. If you type y, then the repositories would be deleted. Here you can select, which repositories you would
like to have deleted.
The SVN repositories would be created according to the number of teams written in the bash file. 
Please note that there is no way to add a new repository, hence 25 repositories has been added here which might be the maximum 
for one semester.

STAGE 4

You come in this stage, only if you have opted for a freshldap.
This stage is the deletion of the Jenkins Jobs. Once deleted, new Jenkins jobs would be created and the 
rights to view, build the jobs would be automatically assigned to them. Here too, 25 jobs has been created which might be the maximum.
Type y to continue.

-----------------------------

ACCESS

SVN
wwwitrt.hs-esslingen.de/svn/labor/
svn co --username viaggsoo https://wwwitrt.hs-esslingen.de/svn/labor/teama1

JENKINS
wwwitrt.hs-esslingen.de/jenkins

To access as admin, type ezslab and the password njn$43EL in Shibboleth.
You will get a complete access of all the teams and their configuration

To access as student, type viaggsoo and the password pfl$51GU in Shibboleth.
You will get the access of only the repository and jobs where viaggsoo in authoritation-file.opt.

PWM
Change your password by typing in 
wwwitrt2.hs-esslingen.de/pwm
For admin access to PWM, type pwmadmin as username and password marc276%!
For Configuration editor, type marc276%! as password.

To change the password of a student, please login as pwmadmin and go to Helpdesk. Type the name of the student
and change his password. 

------------------------------


