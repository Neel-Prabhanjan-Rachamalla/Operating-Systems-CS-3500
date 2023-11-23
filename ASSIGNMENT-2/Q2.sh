#!/bin/bash

MergeSort ()
{
	a=("$@")

  	n=${#a[@]}
  	
  	if [ $n -eq 1 ]
  	then
    		echo "${a[@]}"
  	elif [ $n -eq 2 ]
  	then
    		if [ "${a[0]}" '>' "${a[1]}" ]
    		then
      			echo "${a[1]}" "${a[0]}"
    		else
      			echo "${a[@]}"
    		fi
  	else
    		p=($(( ${#a[@]} / 2 )))
    		m1=($(MergeSort "${a[@]::p}"))
    		m2=($(MergeSort "${a[@]:p}"))
    		ret=()

    		while [ ${#m1[@]} -gt 0 ] && [ ${#m2[@]} -gt 0 ]
    		do
      			if [ "${m1[0]}" '>' "${m2[0]}" ]
      			then
        			ret+=("${m2[0]}")
        			m2=("${m2[@]:1}")
      			else
        			ret+=("${m1[0]}")
        			m1=("${m1[@]:1}")
      			fi
    		done
    		echo "${ret[@]}" "${m1[@]}" "${m2[@]}"
  	fi
}

a=(5 4 3 2 1)
b=($(MergeSort "${a[@]}"))
echo "${b[@]}"

