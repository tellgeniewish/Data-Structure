#include <stdio.h>
int main(void)
{
   int i, j;
   int s[3] = { 0 };

   j = 0;
   s[j++] = j;

   for (i = 0; i < 3; i++)
      printf("%d\n", s[i]);
   return 0;
}