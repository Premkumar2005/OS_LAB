#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int main()
{
    char buffer[BUFFER_SIZE];
    int fd = open("myfile.txt", O_RDONLY);
    int n;

    if (fd == -1)
    {
        printf("Failed to open file.\n");
        exit(1);
    }

    printf("File discriptor is %d\n", fd);

    // i. Reading first 10 characters
    printf("Reading first 10 charecters from file:\n");
    n = read(fd, buffer, 10);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    // ii. Skip 5 characters from current position
    printf("Skipping 5 charecters from current position in the file:\n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buffer, 10);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    // iii. Go 10 characters before the current position
    printf("Going 10 charecters before the current position in the file:\n");
    lseek(fd, -10, SEEK_CUR);
    n = read(fd, buffer, 10);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    // iv. Go to 5th last character in the file
    printf("Going to 5th last charecter in the file:\n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buffer, 5);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    // v. Go to the 3rd character in the file
    printf("Going to the 3rd charecter in the file:\n");
    lseek(fd, 2, SEEK_SET);
    n = read(fd, buffer, 10);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    close(fd);
    return 0;
}

/*
File discriptor is 3
Reading first 10 charecters from file:
abcdefghij
Skipping 5 charecters from current position in the file:
pqrstuvwxy
Going 10 charecters before the current position in the file:
pqrstuvwxy
Going to 5th last charecter in the file:
vwxyz
Going to the 3rd charecter in the file:
cdefghijkl
*/