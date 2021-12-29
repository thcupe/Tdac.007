/* ************************************************************************** *
 *    Ex10.c, V1.0                                                            *
 *    Multiplicador de matrizes, demonstration by lib_Cavendish.h             *
 *                                                                            *
 * ************************************************************************** */

#include "lib_Cavendish.h"

int main()
{
    printf("------------------------------------------------------\n");
    printf("      Welcome to the Ex10 Matrix multiplicator \n");
    printf("   Powered by lib_Cavendish (no rights reserved). \n ");
    printf("---------------------------------------------------- \n");

int i, j, linhaA, colunaA, linhaB, colunaB, x;  // Definição do tamanho das matrizes

    printf("\n\n Declare a quantidade de linhas para a matriz A: ");
    scanf("%d", &linhaA);

    printf("\n Declare a quantidade de colunas para a matriz A: ");
    scanf("%d", &colunaA);

    printf("\n");

    printf("\n Declare a quantidade de linhas para a matriz B: ");
    scanf("%d", &linhaB);

    printf("\n Declare a quantidade de colunas para a matriz B: ");
    scanf("%d", &colunaB);

    Fmatriz(i, j, linhaA, colunaA, linhaB, colunaB, x);
}

