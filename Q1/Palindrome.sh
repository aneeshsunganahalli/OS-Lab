#!/bin/bash

echo "Enter the number: "
read n
temp=$n
rev=0
while [ $temp -gt 0 ]
do 
  r=$((temp%10))
  rev=$((rev*10+r))
  temp=$((temp/10))
done
if [ $rev -eq $n ]
then 
  echo "Palindrome"
else
  echo "Not Palindrome"
fi