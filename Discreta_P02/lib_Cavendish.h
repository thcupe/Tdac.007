/********************************************************************************************
 *   lib_Cavendish.h                                                                        *
 *                                                                                          *
 * Descrição do programa: Biblioteca pessoal                                                *
 * Copyright (C) Thiago De Azevedo Cavendish, 2021                                          *
 *                                                                                          *
 * 2021-11-28                                                                               *
 * Contato: tac@poli.br                                                                     *
 ********************************************************************************************/

/* ---------------------------------------------------------------------------------------- */

#ifndef _LIB_CAVENDISH_H
#define _LIB_CAVENDISH_H

/* ---------------------------------------------------------------------- */
/* Includes */

#include <stdio.h> /* Funções básicas */
#include <stdlib.h> /* Funções diversas (rand, malloc, srand)*/ //Saída
#include <time.h> /* time functions */
#include <float.h> /* constantes Float */
#include <ctype.h>  /* Character functions */  //Para usar caracteres
#include <string.h> /* Strings functions definitions */

//#include <getopt.h> /* Recebe opções do sistema argc/argv */

/* ---------------------------------------------------------------------- */
/* Definitions */

/* Debug */
#ifndef DEBUG /* gcc -DDEBUG=1 */
#define DEBUG 0 /**< Activate/deactivate debug mode */
#endif

#if DEBUG==0
#define NDEBUG
#endif

/** @brief Debug message if DEBUG on */
#define IFDEBUG(M) if(DEBUG) fprintf(stderr, "[DEBUG file:%s line:%d]: " M "\n", __FILE__, __LINE__); else {;}

/* limits */
#define SBUFF 256 /**< String buffer */

/* ---------------------------------------------------------------------- */

/* Prototypes */

int* random_n_permutation(int);
void normalizer(); // Normalizador

/* -------------- FunCoes da linguagem ------------------- */
int kprefix(char a[20],char e[20]);  //Prefixo
int ksufix(char a[20], char e[20]);  //Sufixo
int ksubword(char a[20],char e[20]); //Sub-palavra (no meio)
/* ------------------------------------------------------- */

//void inv(char *string); // Invertedor de string inicial

// Matrix multiplicator //
int Fmatriz(int i, int j, int linhaA, int colunaA, int linhaB, int colunaB, int x); 

// Random Matrix multiplicator //
int Fmatrizale(int linhaA, int colunaA, int linhaB, int colunaB);

// Sparse Matrix multiplicator //
void multiply(k, count, m, n);

/* ---------------------------------------------------------------------- */

#endif /* NOT def _LIB_CAVENDISH_H */

/* ---------------------------------------------------------------------- */

