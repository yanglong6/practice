#! /bin/bash
flist=`ls`
for i in $flist
do
	if test -f $i
	then
		echo $i is a file
	elif test -d $i
	then
		echo %i is a directory
	fi
done
