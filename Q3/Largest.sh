#!/bin/bash
echo -n "Enter number of elements: "
read n
echo -n "Enter $n elements: "
for ((i=0;i<n;i++))
do
  read numbers[$i]
done
largest=${numbers[0]}
for num in ${numbers[@]}
do
  if [ $num -gt $largest ]
  then
    largest=$num
  fi
done
echo "$largest"