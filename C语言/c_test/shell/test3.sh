#!/bin/bash


if test -e $1 
then
	echo "发现文件"
elif test -r $1
then
	echo "内容如下："
	echo $1
	cat $1
else
	echo "该文件不存在"
fi
