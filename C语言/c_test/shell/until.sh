#!/bin/bash


#  this is comment

declare -i n=0
until [ $n -gt 10 ]
do 
	echo "$n"
	n=$n+5
done
