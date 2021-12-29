/********************************************************************************************
 *   ex7.c                                                                                  *
 *                                                                                          *
 * Descrição do programa: Calculadora Polonesa com Pilhas                                   *
 *                                                                                          *
 * Copyright (C) Grupo Hermes, 2021                                                         *
 *                                                                                          *
 *  Integrantes :                                                                           *
 *                                                                                          *
 *   Guilherme Rodrigues Chaves Do Nascimento                                               *
 *   Thiago De Azevedo Cavendish                                                            *
 *                                                                                          *
 * 2021-11-14                                                                               *
 * Contato: grcn@poli.br                                                                    *
 * Contato: tac@poli.br                                                                     *
 ********************************************************************************************/

/* ---------------------------------------------------------------------------------------- */
// Esse programa simula uma calculadora polonesa

// À medida que a expressão é digitada, o programa exibe o valor da expressão atual
//                                    (Como se fosse a tela de uma calculadora normal)
//
// Cada linha digitada deve conter um número, um operador (+, -, ., /), ou um dos
// seguintes comandos :

//   * Q (Quit):   Sair do programa
//   * C (Clear):  Limpar a calculadora
//   * S (Stack):  Exibir o contéudo da pilha

// * Restrição : cada linha deve ter no máximo 100 caracteres.


////////////////////////////////////////
//  Seção 1 : Biblioteca
////////////////////////////////////////

#include "ex7.h"

/* ---------------------------------------------------------------------------------------- */

///////////////////////////////////////////////////////////////////////////////////////////
//  Seção 2 : Pilha(= stack)
///////////////////////////////////////////////////////////////////////////////////////////
// O programa armazena os resultados intermediários em uma pilha de números do tipo double
// Essa estrutura está sujeita a duas operações :

//  * Push Empilhar/Acrescentar um novo elemento no topo da pilha
//  * Pop retirar um elemento do topo da pilha

//////////////////////////////////////////////////////////////////////////////////////////

// A pilha estrá no vetor stk[0..stkcount-1],
// sendo stkcount - 1 o índice do tipo da pilha


//#define MaxStackSize 100
//double stk[MaxStackSize];
//int stkcount;


// Operação Empilha : Coloca o elemento na pilha stk[0..stkcount-1].
void Push(double element)
{
   if(stkcount == MaxStackSize)
   {
      printf(" Stack Size Exceeded !\n\n");
      exit(EXIT_FAILURE);
   }
   stk[stkcount++] = element;
}


// Operação Desempilha : Retira o elemento que está no topo da pilha.
double Pop(void)
{
   if(stkcount == 0)
   {
      printf(" Pop of an Empty Stack !\n\n");
      exit(EXIT_FAILURE);
   }
   return stk[--stkcount];
}


/* ---------------------------------------------------------------------------------------- */

///////////////////////////////////////////////////////////////////////////////
//  Seção 3: Código do programa de simulação da calculadora
//////////////////////////////////////////////////////////////////////////////

//void ApplyOperator(char op);
//void DisplayStack(void);
//string getLine(void);

int main(void)
{
   string line;
   char ch;

   printf("\n-------------------------------------------------\n");
   printf("  Welcome to the Polish Calculator Simulation\n");
   printf("\n    It's time to declarate the operation !\n\n");

   stkcount = 0;
   while (TRUE)
   {
      printf(" > ");
      line = getLine();
      ch = toupper(line[0]);
      switch (ch)
      {
         case 'Q': return 0;
         case 'C': stkcount = 0; break;
         case 'S': DisplayStack(); break;
         default : if(isdigit(ch))
                      Push(atof(line));
                   else
                      ApplyOperator(ch);
                   break;
      }
   }
}

/* ---------------------------------------------------------------------------------------- */


// Está função aplica o operador op aos dois operandos que estão no topo da pilha stk[]
void ApplyOperator(char op)
{
   double lhs, rhs, result;

   rhs = Pop(); // Operando direito
   lhs = Pop(); // Operando esquerdo
   switch(op)
   {
      case '+': result = lhs + rhs; break;
      case '-': result = lhs - rhs; break;
      case '*': result = lhs * rhs; break;
      case '/': result = lhs / rhs; break;
      default : printf(" Illegal operator !\n");
                exit(EXIT_FAILURE);
   }
   printf(" %g\n", result);
   Push(result);
}


// Imprime o conteúdo da pilha stk[0..stkcount-1]
void DisplayStack(void)
{
   int i;

   printf("\n Stack : ");
   if(stkcount == 0)
      printf("Empty !\n\n");
   else
   {
      for(i = 0; i < stkcount; i++)
      {
         if(i > 0) printf(", ");
         printf("%f", stk[i]);
      }
      printf("\n\n");
   }
}


// Lê a linha digitada pelo usuário e a devolve na forma de string
string getLine(void)
{
   string line;
   int n, ch;

   n = 0;
   line = malloc(100+1);
   if(line == NULL) exit(EXIT_FAILURE);
   while((ch = getc(stdin)) != '\n')
   {
      if(n >= 100)
      {
         free(line);
         printf("\n");
         exit(EXIT_FAILURE);
      }
      line[n++] = ch;
   }
   line[n] = '\0';
   return line;
}

