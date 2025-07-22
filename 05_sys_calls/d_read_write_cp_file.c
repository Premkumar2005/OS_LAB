#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd1, fd2;
    char buffer[100];
    ssize_t bytesRead;

    // Open source file for reading
    fd1 = open("data.txt", O_RDONLY);
    if (fd1 < 0)
    {
        printf("Failed to open source file.\n");
        exit(1);
    }

    // Create destination file with write permission
    fd2 = open("destination.txt", O_WRONLY | O_CREAT, 0644);
    if (fd2 < 0)
    {
        printf("Failed to create destination file.\n");
        close(fd1);
        exit(1);
    }

    // Read from source and write into destination
    while ((bytesRead = read(fd1, buffer, sizeof(buffer))) > 0)
    {
        write(fd2, buffer, bytesRead);
    }

    printf("File copied successfully using system calls.\n");

    close(fd1);
    close(fd2);
    return 0;
}
