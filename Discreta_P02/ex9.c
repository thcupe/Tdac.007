/* ************************************************************************ *
 *    Ex9.c, V1.0                                                           *
 *    Invertedor de StrNs, demonstration by lib_Cavendish.h               *
 *                                                                          *
 * ************************************************************************ */

#include "lib_Cavendish.h"

void inv(char *string) //invertedor de string inicial
{
   if(*string)
   {
          inv(string+1);
          putchar(*string);
   }
}

int main()
{
   printf(" String Normal: ");
   printf("\n         Thiago De Azevedo Cavendish !     \n");

   printf(" String Invertida: ");
   inv("\n            Thiago De Azevedo Cavendish !         \n");
   return 0;
}

