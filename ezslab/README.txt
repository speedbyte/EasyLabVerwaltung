

PREPARE

----------------------
This is a read me to prepare the ezs lab.

The first thing is to change the authorization-file.opt and enter the ids of the students.
Then the file prepare-ezs-lab.sh has to be called by issuing the command sudo bash prepare-ezs-lab.sh.

There are various parameters and each parameter does something. The details can be found by passing the -h parameter to 
the shell script prepare-ezs-lab.sh

-----------------------------

ACCESS

ACCESS via GIT

Cloning via: git@wwwitrt3.hs-esslingen.de:LaborVerwaltung/LaborVorbereitungSkripte.git
Cloning is only possible if you have stored your public ssh key in the GITLAB profile section.

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


