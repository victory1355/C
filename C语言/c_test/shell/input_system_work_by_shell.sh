#!/bin/bash

#    用shell做一个简单的实锹枷低衬？�

#    简单的登录界面
echo '+++++++++++++++++++++++'
echo 'welcome to victory shell'
echo '+++++++++++++++++++++++'


#    定义变量
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


#    退出界面 
echo '+++++++++++++++++++++++'
echo '   exit victory shell  '
echo '+++++++++++++++++++++++'










