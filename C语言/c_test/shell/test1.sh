#!/bin/bash
if test -e $1 && test -r $1
then
	echo "the file exist"
	echo "contens like that:"
	cat $1
fi
