#!/bin/bash


if test -e $1 
then
	echo "�����ļ�"
elif test -r $1
then
	echo "�������£�"
	echo $1
	cat $1
else
	echo "���ļ�������"
fi
