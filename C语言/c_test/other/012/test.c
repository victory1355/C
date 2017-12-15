#include <stdio.h>
#include <string.h>

char *strip(char *ip);

int main()
{  
    char a[100], *p;
    scanf("%s", a);
 
    p = strip(a);
    printf("%s", p);
 
    return 0; 
}
 
char *strip(char *ip)
{
   char *p;
   int i = 0;
   
   p = ip;
   while(*p != ' ')
   { 
         i++;
         p++;
   }
   for(;i<strlen(ip);i++)
        *p = *(p+i);
   return p;
}