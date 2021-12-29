/********************************************************************************************
 *   ex7.h                                                                                  *
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

#ifndef ex7_h
#define ex7_h

/* ---------------------------------------------------------------------------------------- */
/* Includes */

#include <stdio.h> /* Funções básicas */
#include <stdlib.h> /* Funções diversas (rand, malloc, srand)*/ //Saída
#include <ctype.h>  /* Character functions */  //Para usar caracteres
#include <string.h> /* Strings functions definitions */
/* #include <malloc.h> */ /* Dynamic memory allocation */

/* ---------------------------------------------------------------------------------------- */
/* Definitions */

typedef char* string;
typedef enum {FALSE, TRUE} bool;

/* ---------------------------------------------------------------------------------------- */
/* Limits */

#define SBUFF 256 /* String buffer */
#define MaxStackSize 100 /* Max Stackable Size */

/* ---------------------------------------------------------------------------------------- */
/* Prototypes  */

double stk[MaxStackSize];
int stkcount;

void Push(double element);    /* Acrescenta um novo elemento na pilha */
double Pop(void);             /* Retira um elemento do topo da pilha */

void ApplyOperator(char op);  /* Aplica o operador op no topo da pilha */
void DisplayStack(void);      /* Imprime o conteúdo da pilha */
string getLine(void);         /* Lê a linha digitada e a devolve na forma de string */


/* ---------------------------------------------------------------------------------------- */

#endif /* NOT def _EX7_H */

/* ---------------------------------------------------------------------------------------- */

