#!/bin/bash

echo "�����ĸ���Ϊ��"
echo $#
echo "���еĲ���:"
echo $*
echo "���еĲ���:"
echo $@
echo "---------------------------------"

echo "��1������Ϊ��"
echo $1
echo "��2������Ϊ��"
echo $2
echo "��3������Ϊ��"
echo $3
echo "--------------------------------"
myname=victoryzhan
echo "my name is $myname"
fruit=apple
echo "fruit == $fruit"
mytree="$fruit tree"
echo "mytree == $mytree"
echo "now time is `date`"
var='$myname,time:`date`'
echo $var
