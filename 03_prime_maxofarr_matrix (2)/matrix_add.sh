#!/bin/bash
# Matrix Addition of two 3x3 matrices

declare -A X
declare -A Y
declare -A Z

echo "Enter the elements of the first 3x3 matrix:"
for ((i = 0; i < 3; i++))
do
    for ((j = 0; j < 3; j++))
    do
        read -p "X[$i,$j] = " X[$i,$j]
    done
done

echo "Enter the elements of the second 3x3 matrix:"
for ((i = 0; i < 3; i++))
do
    for ((j = 0; j < 3; j++))
    do
        read -p "Y[$i,$j] = " Y[$i,$j]
    done
done

echo "The first matrix is:"
for ((i = 0; i < 3; i++))
do
    for ((j = 0; j < 3; j++))
    do
        echo -ne "${X[$i,$j]}\t"
    done
    echo
done

echo "The second matrix is:"
for ((i = 0; i < 3; i++))
do
    for ((j = 0; j < 3; j++))
    do
        echo -ne "${Y[$i,$j]}\t"
    done
    echo
done

# Matrix Addition
echo "The resultant matrix (X + Y) is:"
for ((i = 0; i < 3; i++))
do
    for ((j = 0; j < 3; j++))
    do
        Z[$i,$j]=$(( X[$i,$j] + Y[$i,$j] ))
        echo -ne "${Z[$i,$j]}\t"
    done
    echo
done
