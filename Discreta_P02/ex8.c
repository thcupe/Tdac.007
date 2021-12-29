/* ************************************************************************ */
/*    Ex8:                                                                  *
 *    Programa de Ordenação e comparação de vetores                         *
 *                                                                          *
 *  Descrição: Implementação de                                             *
 *             um Programa de Ordenação e comparação de vetores             *
 *                                                                          *
 *  Copyright (C) Thiago De Azevedo Cavendish, 2021                         *
 *                                                                          *
 *  2021-11-21                                                              *
 *  Contato: tac@poli.br                                                    *
 * ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Includes */

#include <stdio.h> /* Funções basicas */
#include <stdlib.h> /* Funções diversas (rand, malloc, srand)*/ //Saída
#include <time.h> /* time functions */
#include <float.h> /* Constantes flutuantes */
#include <ctype.h>  /* Character functions */  //Para usar caracteres
#include <string.h> /* Strings functions definitions */

//#include <getopt.h> /* Recebe opções do sistema argc/argv */

/* ------------------------------------------------------------------------ */

/*FUNCTIONS*/
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
    int i,
        j,
        change=0,
        comparison=0;
    for (i = 0; i < n-1; i++)

    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
    {
        if (arr[j] > arr[j+1])
        {
            swap(&arr[j], &arr[j+1]);
            ++change;
        }
        ++comparison;
    }


    printf(" * %12i * %12i *", change, comparison);
    return;
}

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
    int i,
        key,
        j,
        change=0,
        comparison=0,
        flag=0; //flag adicionada p/ 1 mudanca, ja que mudamos 2 numeros simultaneamente
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        ++comparison;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            if(flag==0)
            {
                change += 2;
                flag=1;
            }
            else
            {
                ++change;
            }
        }
        arr[j + 1] = key;
        flag=0;
    }
    printf(" * %12i * %12i *", change, comparison);
    return ;
}

/* --------------------------------------------------------------------- */
/*MAIN*/
// Driver program to test above functions
int main()
{
    int i,
        j,
        arr1[500],
        arr2[500],
        casa=0;


    int n = sizeof(arr1)/sizeof(arr1[0]);

    printf("*************************************************\n");
    printf("*                   %-12s * %-12s *", "Changes","Comparisons");
    printf("\n*************************************************");
    printf("\n* %-15s %31s","Melhor caso:", "*");
    printf("\n* --------------------------------------------- *");
    for(j=0; j < 500; j++)
    {
        arr1[j] = j+1;
        arr2[j] = j+1;
    }
    printf("\n* %-15s","Bubble Sort:");
    bubbleSort(arr1, n);
    casa +=2;

    printf("\n* %-15s","Insertion Sort:");
    insertionSort(arr2, n);

    printf("\n*************************************************");
    printf("\n* %-15s %31s","Caso Aleatorio:", "*");
    printf("\n* --------------------------------------------- *");
    srand(time(NULL));
    for(j=0; j < 500; j++)
    {
        i = rand() % 501;
        arr1[j] = i;
        arr2[j] = i;
    }
    printf("\n* %-15s","Bubble Sort:");
    casa +=2;
    bubbleSort(arr1, n);
    printf("\n* %-15s","Insertion Sort:");
    casa += 2;
    insertionSort(arr2, n);

    printf("\n*************************************************");
    printf("\n* %-15s %31s", "Pior Caso:", "*");
    printf("\n* --------------------------------------------- *");
    for(i = 500,j=0; j < 500; i--, j++)
    {
        arr1[j] = i;
        arr2[j] = i;
    }
    printf("\n* %-15s","Bubble Sort:");
    casa +=2;
    bubbleSort(arr1, n);
    printf("\n* %-15s","Insertion Sort:");
    casa +=2;
    insertionSort(arr2, n);
    printf("\n*************************************************\n");
    return EXIT_SUCCESS;
}
/* --------------------------------------------------------------------- */

