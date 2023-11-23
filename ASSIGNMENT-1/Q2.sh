#!/bin/bash

#Q2

echo "Enter a password : "

read pass

#One flag for each condition.
a=0
b=0
c=0
d=0
e=0

#Length of password.
len=${#pass}

#Lower case letters.
if [[ $pass =~ [a-z] ]]
then
	a=1
fi

#Upper case letters.
if [[ $pass =~ [A-Z] ]]
then
	b=1
fi

#Special characters.
if [[ ! $pass =~ ^[[:alnum:]]+$ ]]
then
	c=1
fi

#Digits.
if [[ $pass =~ [0-9] ]]
then
	d=1
fi

#Length.
if [ $len -ge 8 ]
then
	e=2
elif [ $len -ge 6 ]
then
	e=1
fi

#STRONG.
if [ $a == 1 ] && [ $b == 1 ] && [ $c == 1 ] && [ $d == 1 ] && [ $e == 2 ]
then
	echo "STRONG"
#MEDIUM.
elif [ $a == 1 ] && [ $b == 1 ] && [ $c == 1 ] && [ $e == 1 ]
then
	echo "MEDIUM"
#WEAK.
else
	echo "WEAK"
fi
