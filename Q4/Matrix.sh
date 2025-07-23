#!/bin/bash
read -p "Enter rows and cols: " m n
declare -A m1
declare -A m2
declare -A res
echo "Enter elements of m1: "
for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    read m1[$i,$j]
  done
done
echo "Enter elements of m2: "
for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    read m2[$i,$j]
  done
done

for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    res[$i,$j]=$((m1[$i,$j]+m2[$i,$j]))
  done
done

echo "Result: "
for ((i=0;i<m;i++))
do
  for ((j=0;j<n;j++))
  do
    echo -n "${res[$i,$j]} " 
  done
  echo
done