/* ---------------------------------------------------------------- */
/* Nome do programa: Exercício da string
 * Descrição do programa: conta +1 para '(' e -1 para ')'
 * Copyright (C) Thiago De Azevedo Cavendish, 2021
* 2021-08-01
 * Contato: tac@poli.br
*/
/* ---------------------------------------------------------------- */
/* includes */
#include <stdio.h>  // funções básicas
#include <stdlib.h> // saída
#include <string.h> // string
/* --------------------------------------------------------------- */
/*
  *Descrição da função: dada uma string, ela conta +1 para '(' e
                                                   -1 para ')'                                         
*/
int main()
{
  char entrada[100];

  printf("\n Entre com o texto: ");
  fgets(entrada, 100, stdin);

  printf("\n VocE entrou com o texto: %s", entrada);

  int i = 0;
  int resultado = 0;

  while(entrada[i] != '\0')
  {
    if (entrada[i] == '(')
    {
      resultado++;
    }
    else if(entrada[i] == ')')
    {
      resultado--;
    }
    i++;
  }
  printf("\n\n O texto digitado possui %d caracteres", i);
  printf("\n O resultado eh %d \n\n", resultado);
  return 0;
}
/* --------------------------------------------------------------- */

