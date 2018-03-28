#!/bin/sh
#Create an array
Array=(71 12 34 5 61 13)
N=6
#Sort for asscending order
for (( i=0; i<$N; i++ ))
do
	for (( j=$i; j<$N; j++ ))
	do
		if [ ${Array[$i]} -gt ${Array[$j]} ]; then
			temp=${Array[$i]}
			Array[$i]=${Array[$j]}
			Array[$j]=$temp
		fi
	done
done
#Output sorted array
for ((i=0; i<N; i++))
do
	echo ${Array[$i]}
done
