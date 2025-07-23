#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  int ch;
  
  if (argc < 2){
    printf("No file entered");
    exit(1);
  }
  else
  {
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
      printf("File doesn't exist");
      exit(1);
    }
    while ((ch = fgetc(fp)) != EOF)
      printf("%c",ch);
  }
  fclose(fp);
  return 0;
}