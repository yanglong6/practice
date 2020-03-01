echo "input a:"
read a
echo "input b:"
read b
SUM=`expr $a + $b`
test "$b" = "$a"
echo $?
echo SUM=$SUM
$(())
