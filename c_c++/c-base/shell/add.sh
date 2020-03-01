#! /bin/bash
add()
{
a=$1
b=$2
sum=$(( $a + $b ))
echo sum=$sum
}
add $1 $2
