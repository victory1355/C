#!/bin/bash


# this is comment
files=`ls`
echo '-------------------------------'
echo "a = $a"
echo "files = $files"
echo '-------------------------------'
for a in $files
do
	echo "a = $a"
	if [ -f $a ]
	then
		wc -l $a
	fi
done
echo '         end                    '
echo '-------------------------------'
echo "\n"
