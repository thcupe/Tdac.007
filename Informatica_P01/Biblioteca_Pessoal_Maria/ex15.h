/*****************************************************************************
 *   ex15.h                                    Version 20180714.101818       *
 *                                                                           *
 *   Brief description : Biblioteca pessoal                                  *
 *   Copyright (C) 2016-2018    by Ruben Carlo Benante                       *
 *****************************************************************************
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License.          *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************
 *   To contact the author, please write to:                                 *
 *   Ruben Carlo Benante                                                     *
 *   Email: rcb@beco.cc                                                      *
 *   Webpage: www.beco.cc                                                    *
 *   Phone: +55 (81) 3184-7555                                               *
 *****************************************************************************/

/* ------------------------------------------------------------------------- */
/**
 * \file ex15.h
 * \ingroup GroupUnique
 * \brief Brief description: Biblioteca pessoal
 * \details This program really do a nice job as a template, and template only!
 * \version 20160908.182854
 * \date 2016-09-08 // 30/08/2021
 * \author Ruben Carlo Benante <<rcb@beco.cc>>
 * \par Webpage
 * <<a href="www.beco.cc">www.beco.cc</a>>
 * \copyright (c) 2016 GNU GPL v2
 * \note This program is free software: you can redistribute it
 * and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA. 02111-1307, USA.
 * Or read it online at <<http://www.gnu.org/licenses/>>.
 *
 *
 * \todo Now that you have the template, hands on! Programme!
 * \warning Be carefull not to lose your mind in small things.
 * \bug This file right now does nothing usefull
 *
 */

#ifndef _EXN_H
#define _EXN_H

/* ------------------------------------------------------------------------- */
/* includes */

#include <stdio.h>  /* Funções básicas */
#include <stdlib.h> /* Funções diversas (rand, malloc, srand)*/ //Saída
#include <getopt.h> /* Recebe opções do sistema argc/argv */
#include <math.h>   /* Mathematics functions */
#include <time.h>   /* Time and date functions */
#include <ctype.h>  /* Character functions */  //Para usar caracteres
#include <string.h> /* Strings functions definitions */
#include <ncurses.h>  /* Screen handling and optimisation functions */

/* #include <dlfcn.h> */ /* Dynamic library */
/* #include <malloc.h> */ /* Dynamic memory allocation */
/* #include <unistd.h> */ /* UNIX standard function */
/* #include <errno.h> */ /* Error number codes errno */
/* #include <sys/stat.h> */ /* File status and information */
/* #include <float.h> */ /* Float constants to help portability */
/* #include <stddef.h> */ /* Various types and MACROS */
/* #include <locale.h> */ /* MACROS LC_ for location specific settings */

/* ------------------------------------------------------------------------- */
/* definitions */

#ifndef VERSION /* gcc -DVERSION="0.1.160612.142628" */
#define VERSION "20160908.182854" /**< Version Number (string) */
#endif

/* Debug */
#ifndef DEBUG /* gcc -DDEBUG=1 */
#define DEBUG 0 /**< Activate/deactivate debug mode */
#endif

#if DEBUG==0
#define NDEBUG
#endif
/* #include <assert.h> */ /* Verify assumptions with assert. Turn off with #define NDEBUG */ 

/** @brief Debug message if DEBUG on */
#define IFDEBUG(M) if(DEBUG) fprintf(stderr, "[DEBUG file:%s line:%d]: " M "\n", __FILE__, __LINE__); else {;}

/* limits */
// #define SBUFF 256 /**< String buffer */
#define SGRA 201 /* Autor, TItulo */
#define SMED 101 /* Local */
#define SPEQ 5 /* COdigo, Ano, EdiCAo */
#define SISBN 14 /* ISBN */

#define NWIN 6 /* Help, Adicionar, Pesquisar, Editar, Deletar, Sobre */

/* msgstatus */
#define STLINE (LINES-2) /* linha da msg de status */
#define STOK 0
#define STYESNO 1

/* Strings de Tela */
#define TTITULO "Sistema de Biblioteca do Grupo Maria"
const char *stela[6]={"Tela 00: Ajuda", "Tela 01: Cadastro de Livros", "Tela 02: Pesquisar livro", "Tela 03: Editar livro", "Tela 04: Deletar livro", "Tela 05: Sobre"};

const char *tfunction[10]={"F1 Help ", "F2 Load ", "F3 Save ", "F4 Quit ","F5 Next ", "F6 Prev ", "F7 About ", "F8 Unkn "}; 

#define Tmsg "Ainda esta em desenvolvimento !"

/* File para a biblioteca */
FILE *biblio;
FILE *pesquisa;
FILE *altera;
FILE *pchange1;
FILE *pchange2;

/* ------------------------------------------------------------------------- */
/* structs and globals */

typedef struct slivro
{
    /* Codigo;Titulo;Autor;Editora;Local;Ano;Edicao;ISBN */
    /* 4     ;200  ;200   ;100    ;100  ;4  ;4     ;13   */
    int cod;
    char titulo[SGRA]; 
    char autor[SGRA];
    char editora[SMED];
    char local[SMED];
    char ano[SPEQ];
    char ed[SPEQ];
    char isbn[SISBN];
    //char code[SPEQ];//
} livro_t;

typedef struct swins
{
    int menu[NWIN]; /* linha escolhida TODO avaliar necessidade */
    int lmax, cmax; /* lembra se a janela mudou de tamanho */
    int wi; /* indice da janela atual */
    int wo; /* indice da janela anterior */
    WINDOW *w[NWIN];
} wins_t;

/* ------------------------------------------------------------------------- */
/* prototypes */

/**< Prints Help information and exit */
void Help(void);
/**< Prints copyright information and exit */
void copyr(void);
/**< Initializes some operations before start */
void ex15_init(wins_t *win);
/* termina o programa graciosamente */
void bomb(wins_t win, char *msg, int status, FILE *f);
/* imprime na linha de status */
int msgstatus(wins_t win, char *msg, int tipo);

/* funcoes de imprimir Tela              */

/* imprime Tela 00: Help */
void pHelp(wins_t *pw, livro_t *aw);
/* imprime Tela 01: Adicionar livro */
void padd(wins_t *pw,livro_t *aw);
/* imprime Tela 02: Pesquisar livro */
void psearch(wins_t *pw, livro_t *aw);
/* imprime Tela 03: Editar livro */
void pchange(wins_t *pw, livro_t *aw);
/* imprime Tela 04: Deletar livro */
void pdel(wins_t *pw, livro_t *aw);
/* imprime Tela 05: Sobre */
void pabout(wins_t *pw, livro_t *aw);

/* ------------------------------------------------------------------------- */
/* funcoes auxiliares */

/* confere se a tela atual precisa de um clear */
void pheader(wins_t *pw); // Cabecalho
/* centraliza a coluna */
int ccentral(int cl, char *msg);

/* coleta dados sobre o livro */
void pdados(wins_t *pw, livro_t *aw);
/* imprime dados no file */
void pbiblio(wins_t *pw, livro_t *aw);
/* checa a contagem do livro */
int pcount();
/* procura, na biblioteca, a palavra-chave */
void kpesquisa(wins_t *pw, livro_t *aw);
/* le e coloca na tela o que tem em um arquivo */
void pread(wins_t *pw);
/* navegação do programa */
void pkeyf(wins_t *pw, livro_t *aw, int kpress);
/* verifica se foi inserido algumas strings ou todas do livros_t */
int pcondicao(livro_t *aw);
/* atribui strings */
void patribuir(livro_t *aw, int k, char *msg);
/* concatena dois files */
void pconcatenar();
/* divide a string em tokens */
void pdividestring(wins_t *pw);

#endif /* NOT def _EXN_H */

/* ------------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline    */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20180716.101436   */

