#!/bin/sh

#Q1

echo "Enter the address for the directory : "
read directory

#Checking if the input given is directory or not.
if [ -d $directory ]
then
	#Iterating through the list of files and checking whether it is directory or not and then outputting.
	for i in $(ls $directory)
	do
		#Concatinating with source directory.
		dir=$directory"/"$i
		
		if [ -d $dir ]
		then
			echo $i
		fi
	done
else
	echo "Invalid Directory"
fi
