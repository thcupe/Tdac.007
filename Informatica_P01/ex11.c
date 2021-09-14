/* ----------------------------------------------- */
/* Nome do programa: Calculadora de primos
 * Descrição do programa: Calcula se o número é primo
 * Copyright (C) Thiago De Azevedo Cavendish, 2021
 * 2021-08-01
 * Contato: tac@poli.br
*/

/* ----------------------------------------------- */
/* includes */
#include <stdio.h> // funções básicas
#include <stdlib.h> // saída
/* ----------------------------------------------- */
/*
  *Descrição da função da função: Calcula se o número é ou não primo
*/
int main(void)
{
// Declarações
  int num, i, resultado = 0;
  char letra;

  while(1)
  {
   resultado = 0;
   printf(" \n Calculadora de primos\n");
   printf("------------------------\n\n");
   printf(" Digite um nUmero: ");
   scanf("%d", &num);

    for(i = 2; i <= num / 2; i++)
    {
      if (num % i == 0)
      {
       resultado++;
        break;
      }
    }
    if (resultado == 0)
      printf("\n %d eh um nUmero primo\n", num);
    else
      printf("\n %d nAo eh um nUmero primo\n", num);
    while(1)
    {
      printf("\n Deseja continuar s/n: \n");
      printf("  ");
      scanf(" %c", &letra);

      if ((letra == 's')||(letra == 'S'))
      {
       printf("---------------------------\n");
       break;
      }
      else if((letra != 's')||(letra != 'S'))
      printf(" ");  
      return 0;
    }
   }
}
/* ----------------------------------------------- */
