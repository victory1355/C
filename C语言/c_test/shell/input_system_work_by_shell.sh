#!/bin/bash

#    ÓÃshell×öÒ»¸ö¼òµ¥µÄÊµÇÂ¼ÏµÍ³Ä£¿é

#    ¼òµ¥µÄµÇÂ¼½çÃæ
echo '+++++++++++++++++++++++'
echo 'welcome to victory shell'
echo '+++++++++++++++++++++++'


#    ¶¨Òå±äÁ¿
declare -i n=0

echo 'please input  name'
read name
if $name=victory
then
	echo "valid user name"
else
	echo "please input your name again!"
	read name
fi

echo 'please input  passwd'
read passwd
if $passwd=1355
then
	echo "valid passwd"
else
	echo "please input passwd again!"
	read passwd
fi


if $name=victory && $passwd=1355
	echo "welcome to my world"

while [ $n -le 3 ]
do
	echo 'working.....' 
	n=$n+1


#    ÍË³ö½çÃæ 
echo '+++++++++++++++++++++++'
echo '   exit victory shell  '
echo '+++++++++++++++++++++++'










