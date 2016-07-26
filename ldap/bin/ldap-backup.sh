#!/bin/bash

/etc/init.d/slapd stop
ps -eaf | grep ^slapd
sleep 2
ps -eaf | grep ^slapd
#killall slapd


slapcat -l /root/ldap-backups/`date +"%d"`.ldif

/etc/init.d/slapd start
ps -eaf | grep ^slapd


echo "siehe auch"
echo "  cat /root/ldap-backups/RESTORE.txt"


