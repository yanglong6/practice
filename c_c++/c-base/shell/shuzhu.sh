#! /bin/bash
for((i=0; i<5; i++))
do
	a[i]=$i
done
for((j=0; j<5; j++))
do
	echo ${a[j]}
done
sum=${#a[@]}
echo sum=$sum
