/* ************************************************************************ */
/*    Ex6:                                                                  *
 *    Programa de listas lineares                                           *
 *                                                                          *
 *  Descrição: Implementação inicial do código de listas lineares           * 
 *  Copyright (C) Thiago De Azevedo Cavendish, 2021                         *
 *                                                                          *
 *  2021-11-07                                                              *
 *  Contato: tac@poli.br                                                    *
 * ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Includes */

#include <stdio.h> // funções básicas
#include <stdlib.h> // saída
#include <string.h> // string
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Function prototypes */

typedef struct st_lista
{
    int c;
    struct st_lista *prox;
} lista;

/* ------------------------------------------------------------------------ */
/* Funções Utilizadas */


lista *buscar(lista *cabeca, int x)
{
    lista *pl = cabeca;
    while(pl != NULL)
    {
        if(pl-> c == x)
            return pl;
        pl = pl->prox;
    }
    return NULL;
}


void inserir(lista **cabeca, int x)
{
    lista *pl = *cabeca;
    lista *plant = NULL;
    while(pl != NULL)
    {
        plant = pl;
        pl = pl->prox;
    }

    pl = malloc(sizeof(lista));
    pl->c = x;
    pl->prox = NULL;
    if(plant != NULL)
       plant->prox = pl;
    else
       *cabeca = pl;
}


void remover(lista **cabeca, lista *r)
{
    lista *pl = *cabeca;
    lista *plant = NULL;
    if(r == NULL)
       return;

    while(pl != NULL && pl != r)
    {
        plant = pl;
        pl = pl->prox;
    }
    if(pl == NULL)
       return;
    if(plant != NULL)
       plant->prox = pl->prox;
    else
       *cabeca = pl->prox;
    free(pl);

    return;
}


lista *anterior(lista *cabeca, lista *r)
{
    lista *pl = cabeca, *plant = NULL;
    if(r == NULL)
       return NULL;
    while(pl != NULL && pl != r)
    {
          plant = pl;
          pl = pl->prox;
    }
    return plant;
}


void imprimir(lista *cabeca)
{
    lista *pl = cabeca;
    while(pl != NULL)
    {
          printf(" %d->", pl->c);
          pl = pl->prox;
    }
    printf(" NULL \n ");
}


/* ------------------------------------------------------------------------ */
/* Função principal */

int main(void)
{
    printf("\n/* -------------------------------------------------------------------------- */ \n");
    printf("           Welcome to the Ex6 Linear list initial implementation \n");
    lista *l1 = NULL, *b = NULL, *a = NULL;

    printf(" \n /* ------------------------------------------------------------------------ */ \n Insere 1, 2 e 3 : \n ");
    printf(" NULL \n ");
    inserir(&l1,  1);
    imprimir(l1);
    inserir(&l1,  2);
    imprimir(l1);
    inserir(&l1,  3);
    imprimir(l1);
    printf(" \n /* ------------------------------------------------------------------------ */ \n Busca 2 : \n ");
    b = buscar(l1, 2);
    if(b != NULL)
        printf(" b->c: %d \n ", b->c);
    printf(" \n /* ------------------------------------------------------------------------ */ \n Anterior 2 : \n");
    a = anterior(l1, b);
    if(a != NULL)
        printf("  a->c: %d \n ", a->c);
    printf(" \n /* ------------------------------------------------------------------------ */ \n Remove 2 : \n ");
    remover(&l1, b);
    imprimir(l1);
    printf("\n");
    printf("/* -------------------------------------------------------------------------- */ \n\n");
}
