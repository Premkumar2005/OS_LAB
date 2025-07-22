#!/bin/bash
# Program to find the largest of the given array of numbers

echo "Enter the size of the array:"
read n

echo "Enter the elements of the array:"
for ((i = 0; i < n; i++))
do
    read arr[i]
done

max=${arr[0]}

for ((i = 1; i < n; i++))
do
    if (( arr[i] > max ))
    then
        max=${arr[i]}
    fi
done

echo "The largest of the given numbers is $max"
