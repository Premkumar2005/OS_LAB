#include <stdio.h>
#include <string.h>

void main()
{
    char fn[10], pat[10], temp[200];
    FILE *fp;

    printf("Enter file name\n");
    scanf("%s", fn);
    printf("Enter pattern to be searched\n");
    scanf("%s", pat);

    fp = fopen(fn, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    while (!feof(fp))
    {
        fgets(temp, 100, fp);
        if (strstr(temp, pat))
            printf("%s", temp);
    }

    fclose(fp);
}
// Enter file name
// data.txt
// Enter pattern to be searched
// hello
// hello this for grep test