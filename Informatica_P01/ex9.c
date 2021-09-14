/* -------------------------------------------------------------- */
/* Nome do programa: Sorteio FDP normal
 * Descrição do programa: sorteio de uma variAvel aleatOria
                                              de FDP normal
 * Copyright (C) Thiago De Azevedo Cavendish, 2021
 * 2021-08-01
 * Contato: tac@poli.br
*/
/* -------------------------------------------------------------- */
/* includes */
#include <stdio.h>  // funções básicas
#include <stdlib.h> // saída
#include <time.h>   // função randômica
#include <math.h>   // funções matemáticas
/* -------------------------------------------------------------- */
/* defines */
#define Dsv 0.48 //(Desvio padrAo)
#define Pi 3.141592654
#define e 2.718281828
#define Vm 5 //(Valor mEdio) ou (EsperanCa)
/* -------------------------------------------------------------- */

/* -------------------------------------------------------------- */
/* function prototypes */
 //sorteio
 // Simula o sorteio de uma variAvel aleatOria de FDP normal
 //                                               (de Gauss)
/* -------------------------------------------------------------- */
/*
  *Descrição da função: Simula o sorteio de uma variAvel aleatOria
                        de FDP normal (de Gauss)
  *valores que entram como argumentos:
                                      Dsv: Desvio padrAo
                                      Vm: Valor mEdio (esperanCa)
  *valor'es retornados: y = normal
*/
int main()
{
  double y;
  int x;
  y = 0.000000000000000;
  x = 0;
  double base2, base3;
  base2, base3 = 0.000000000000000;
  char letra;
  srand(time(NULL));

  while(1)
  {
   printf("\n Sorteio de nUmeros aleatOrios ");
   printf("\n--------------------------------\n");

   printf("   completamente legItimo\n");

   x = rand() % 11;
   //y = (1/(Dsv*sqrt(2*Pi)));
   //y = (pow(e, (-0.5*2)));
   //y = ((x - Vm)/Dsv);

   base2 = ((x - Vm)/Dsv);
   base3 = pow(base2, 2);
   y =(1/(Dsv * sqrt(2 * Pi))) * (pow(e, (-0.5*base3)));

   printf("\n  Seu nUmero aleatOrio eh: %d ", x);
   printf("\n  A normal eh: %.15f \n", y);

   while(1)
   {
    printf("\n  Deseja continuar s/n: \n");
    printf("  ");
    scanf(" %c", &letra);

     if ((letra == 's')||(letra == 'S'))
     {
      printf("-----------------------------\n");
      break;
     }
     else if((letra != 's')||(letra != 'S'))
     printf("\n");
    return 0;
    }
  }
}
/* -------------------------------------------------------------- */
   
