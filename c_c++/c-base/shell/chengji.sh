#! /bin/bash
read a
if ((a<=100 && a>=0))
then
	b=$(( a / 10 ))
	echo $b
	case $b in
		6|7|8)
			echo B
			;;
		9)
			echo A
			;;
		10)
			echo A
			;;
		*)
			echo C
			;;
	esac
else 
	echo error
fi
