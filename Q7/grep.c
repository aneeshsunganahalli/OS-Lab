#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char filename[20], buffer[100], pattern[20];
  FILE *fp;
  printf("Enter filename: ");
  scanf("%s", filename);
  printf("Enter pattern: ");
  scanf("%s", pattern);
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Doesn't exist");
    exit(1);
  }
  while (fgets(buffer, 100, fp) != NULL)
  {
    if (strstr(buffer, pattern))
    {
      printf("%s", buffer);
    }
  }
  return 0;
}