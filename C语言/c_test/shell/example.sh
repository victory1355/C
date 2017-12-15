#!/bin/bash

echo "参数的个数为："
echo $#
echo "所有的参数:"
echo $*
echo "所有的参数:"
echo $@
echo "---------------------------------"

echo "第1个参数为："
echo $1
echo "第2个参数为："
echo $2
echo "第3个参数为："
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
