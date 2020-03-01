#! /bin/bash
read a
sum=0
for b in $a
do
	sum=$(( $sum + $b ))
done
echo $sum
