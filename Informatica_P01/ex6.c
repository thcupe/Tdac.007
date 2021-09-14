/* ------------------------------------------------- */
/* Programa do método da bissecção
 * Descrição: Calcular a raiz pelo método da bissecção
 * Copyright (C) Thiago De Azevedo Cavendish, 2021
 * 2021-07-12
 * Contato: tac@poli.br
*/
    
/* ------------------------------------------------- */
/* includes */
#include <stdio.h> // funções básicas
#include <stdlib.h> // saída

/* ------------------------------------------------- */
/* defines */
#define Erro_Max 0.001
/* ------------------------------------------------- */

/* ------------------------------------------------- */
/* function prototypes */
 float raiz(float n);
 // recebe um valor e retorna a sua raiz
 int float_i(float a, float b);

/* ------------------------------------------------- */
// Função principal

int main(void)
{
   float n; //numero que queremos tirar a raiz
   float r; //valor da raiz de n

   printf("\n Digite o valor que vocE quer a raiz: \n\n ");
   scanf("%f", &n);

   r=raiz(n);
   if(n < 1.00)
     printf("\n Erro: NAo calculo nUmeros negativos e ou abaixo de 1!! \n\n ");
   else
     printf("\n O valor da raiz de (%.2f) eh: %.2f \n\n ", n, r);

  return EXIT_SUCCESS;
}

/* ------------------------------------------------- */
/*
  Descrição: Calcula a raiz usando o
 método da bissecção
*/
float raiz(float n)
{
   float r; //valor aproximado da raiz
   float m; //valor aproximado de n
   float b; //fim do intervalo
   float a; //início do intervalo


   if(n < 0.00)
    return -1.00; // Erro, pois não calcula números negativos
   if(n < 1.0)
    return -2.00; // Erro, pois não calcula números entre 0 e 1

   a = 1.00;
   b = n;

   while(1)
   {
    r =(a+b)/2.00; // estimativa inicial
    m = r*r;

    if(float_i(m, n))
     return r;

    if(m<n) //A raiz está no intervalo [r;b]
     a=r;
    else //A raiz está no intervalo [a;r]
     b=r;
   }
   return r;
}
/* ------------------------------------------------- */
/* recebe dois valores float e compara*/
int float_i(float a, float b) //usa a margem de erro para calcular a raiz
{
  if(a-Erro_Max < b && a+Erro_Max > b)
   return 1;
  else
   return 0;
}

/* ------------------------------------------------ */


