/* ----------------------------------------------- */
/* Nome do programa: Calculadora de raizes da equaCAo do 2* grau
 * Descrição do programa: Ele calcula as raizes da equação:
                                      f(x) = ax^2 + bx + c
 * Copyright (C) Thiago De Azevedo Cavendish, 2021
 * 2021-07-23
 * Contato: tac@poli.br
*/

/* ----------------------------------------------- */
/* includes */
#include <stdio.h> // funções básicas
#include <stdlib.h> // saída
#include <math.h> // funções matemáticas

/* ----------------------------------------------- */
/* defines */
/* ----------------------------------------------- */
/*
 *Descrição da função da função: Ela calcula as raizes da equação:
                                      f(x) = ax^2 + bx + c
*/
int main()
{
// Declarações
  float a, b, c, Delta, x, x1, x2;

  printf("\n == Calculadora de raizes da equaCAo do 2* grau == \n ");
  printf("\n   Insira o valor de a : ");
  scanf("%f", &a);
// verificação
  if(a != 0)
  {
   printf("   Insira o valor de b : ");
   scanf("%f", &b);
   printf("   Insira o valor de c : ");
   scanf("%f", &c);
   //exibindo o f(x)
   printf("\n   f(x) = (%.2f)x^2 + (%.2f)x + (%.2f) \n", a, b, c);

   Delta = pow(b, 2) -( 4 * a * c); //calcula Delta
   printf("\n  Delta = %.2f", Delta); //exibe o valor de Delta

   if(Delta > 0)
   {//se for maior que 0, vamos ter 2 raízes reais e distintas

    // por Bhaskara
    x1 = (-b + sqrt(Delta))/2 * a;
    x2 = (-b - sqrt(Delta))/2 * a;

    printf("\n  Delta > 0, f(x) tem duas raIzes reais e distintas \n");
    printf("\n  As raIzes sAo:");
    printf("\n  x1 = %.2f e x2 = %.2f \n\n ", x1, x2); //exibe os valores de x1 e x2
   }
   if(Delta == 0)
   { //se delta for = 0 vamos ter 1 única raiz real

    // por Bhaskara
    x = (-b + sqrt(Delta))/2 * a; //calcula o valor da única raiz
    printf("\n  Delta = 0, uma Unica raiz real \n");
    printf("\n  A raIz eh:");
    printf("\n x = %.2f \n", x); //exibe o valor da raiz
   }
   if(Delta < 0)
   { //se Delta < 0 não existe raíz real
    printf("\n  Delta < 0, NAo existem raIzes reais !! \n");
   }

   }
  else
  {
   printf("\n  FunCAo invAlida pois a = 0!!! \n");
  }
    return 0;
}

/* ----------------------------------------------- */

