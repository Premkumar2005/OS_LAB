#!/bin/bash
# Program to generate the prime numbers of a given range

echo "Enter the lower bound:"
read n1
echo "Enter the upper bound:"
read n2

echo "Prime numbers between $n1 and $n2 are:"

for ((i = n1; i <= n2; i++))
do
    if (( i < 2 )); then
        continue
    fi

    flag=0
    for ((j = 2; j * j <= i; j++))  # Optimized loop till sqrt(i)
    do
        if (( i % j == 0 )); then
            flag=1
            break
        fi
    done

    if (( flag == 0 )); then
        echo -ne "$i "  # Print prime in single line
    fi
done

echo # for newline after output
