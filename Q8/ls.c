#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc < 2)
    {
        printf("Too few arguments\n");
        exit(1);
    }
    if ((dp = opendir(argv[1])) == NULL)
    {
        printf("Directory not found\n");
        exit(1);
    }

    while ((dirp = readdir(dp)) != NULL)
    {
        printf("%s\n", dirp->d_name);
    }

    closedir(dp);
    return 0;
}
