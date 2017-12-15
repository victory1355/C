#!/bin/bash
if [ -e $1 ] && [ -r $1 ]
then
	cat $1
fi
