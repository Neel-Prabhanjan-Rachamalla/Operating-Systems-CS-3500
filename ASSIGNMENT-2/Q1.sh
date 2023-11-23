#!/bin/bash

echo "Enter name of file : "
read file

#	Finds the path of the file starting from root directory.
path=$(find /home -name $file)

#	Returns the top 3 occuring elements of the given file.
tr -c '[:graph:]' '[\n*]' < $path | sort | uniq -c | sort -nr | head -3
