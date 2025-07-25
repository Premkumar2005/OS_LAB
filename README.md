🧾 Operating Systems Lab – Code Sheet
------------------------------------

1  
a. Exposure to Linux Operating System and Environment  
b. Write Shell Scripts for the following:  
   i. Concatenation of two strings  
   ii. Comparison of two strings  
   iii. Maximum of three numbers  

------------------------------------
2  
Write Shell Scripts for the following:  
a. Fibonacci series  
b. Arithmetic operation using case  
c. Check whether a given number is palindrome or not  

------------------------------------
3  
Write Shell Scripts for the following:  
a. Finding largest of N numbers (storing numbers in an array)  
b. Generating prime numbers.  
c. Reading two matrices and finding sum 

------------------------------------
4  
Simulation of ls, rm, cat and grep commands using system calls.  

------------------------------------
5  
a. Write a program to perform the following tasks using system calls:  
   i. Parent process should create a child process  
   ii. Both parent child processes should display their pid and parent’s pid; parent process should also display its child’s pid  
   iii. Load a new program into child process  
   iv. The parent process should terminate after the child process terminates  

b. Program to demonstrate the creation of Zombie and Orphan processes.  

c. Program to perform the following task using I/O system calls for file I/O  
   i. Reading first 10 characters from file  
   ii. Skipping 5 characters from current position in the file  
   iii. Going to 5th last character in the file  
   iv. Going to the 3rd character in the file  

d. Program to read from file and write into a new file using I/O system calls for file I/O 

------------------------------------
6  
a. Program to implement Producer-consumer problem using the following shared memory methods:  
   i. using shm_open and mmap  
   ii. shmget and shmat  

b. Write a program to generate first N ODD numbers with the following requirements:  
   - Parent program should create a child and distribute the task of generating odd numbers to its child.  
   - The code for generating odd numbers should reside in different program.  
   - Child should write the odd numbers to a shared memory.  
   - Parent process has to print the odd numbers by retrieving from the shared memory.  
   i. Implement the above using shmget and shmat  
   Note: Shared object should be removed at the end in the program  
------------------------------------
7  
a. Write a program to generate and print Fibonacci series with the following requirements:  
   - Parent program should create a child and distribute the task of generating Fibonacci series to its child.  
   - The code for generating Fibonacci series should reside in different program.  
   - Child should write the generated Fibonacci series to a shared memory.  
   - Parent process has to print by retrieving the Fibonacci series from the shared memory.  
   i. Implement the above using shmget and shmat  
   ii. Implement the above using shm_open and mmap  
   Note: Shared object should be removed at the end in the program.  

b. Write a program to generate and print Prime numbers between a given range (between M & N) with the following requirements  
   - M & N should be passed as command line arguments  
   - Error checking should be done to verify the required number of arguments at the command line  
   - Parent program should create a child and distribute the task of generating Prime numbers to its child.  
   - The code for generating Prime numbers should reside in different program.  
   - Child should write the generated Prime numbers to a shared memory.  
   - Parent process has to print by retrieving the Prime numbers from the shared memory.  
   i. Implement the above using shm_open and mmap  
   Note: Shared object should be removed at the end in the program.  

------------------------------------

8  
a. Write a program with two threads and a main thread. Schedule the task of calculating the natural sum upto ‘n’ terms and factorial of ‘n’ on these threads.  
   Note: The main thread should read ‘n’ from command line and pass it as parameter to remaining threads. Terminate the threads using system calls.  

b. Implement FCFS scheduling algorithm by defining the process structure.  

------------------------------------
9  
Implement the following CPU scheduling algorithms by defining the process structure:  
a. SJF  
b. SJF (Preemptive)  

------------------------------------
10  
Implement the following CPU scheduling algorithms by defining the process structure:  
a. Priority  
b. Priority (Preemptive)  

------------------------------------
11  
Implement Round Robin CPU scheduling algorithm with arrival time by defining the process structure.  

------------------------------------
12  
Implement the following using mutex and semaphores:  
a. Producer – Consumer problem  
b. Reader’s writers’ problem  
