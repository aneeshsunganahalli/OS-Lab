#!/bin/bash

echo "Enter the number: "
read n
temp=$n
while [ $temp -ne 0 ]
do
  r=$((temp%10))
  rev=$((rev*10+r))
  temp=$((temp/10))
done

if [ $n -eq $rev ]
then 
  echo "Palindrome"
else
  echo "Not Palindrome"
fi
