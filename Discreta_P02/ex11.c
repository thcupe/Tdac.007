/* ************************************************************************ *
 *    Ex11.c, V1.0                                                          *
 *    Multiplicador de matrizes aleatOrias (sem repetiCAo)                  *
 *    Demonstration by lib_Cavendish.h                                      *
 *                                                                          *
 * ************************************************************************ */

#include "lib_Cavendish.h"

int main()
{
    printf("------------------------------------------------------\n");
    printf("   Welcome to the Ex11 Random Matrix Multiplicator \n");
    printf("    Powered by lib_Cavendish (no rights reserved). \n ");
    printf("---------------------------------------------------- \n");


    int linhaA, colunaA, linhaB, colunaB; //Definição de variaveis

    srand(time(NULL)); // Parametro aleatorio

    linhaA = rand() %10 + 1;
    colunaA = rand() %10 + 1;

    linhaB = colunaA;

    colunaB = rand() %10 + 1; // Atribuir valores aleatorios para a Coluna B

    Fmatrizale(linhaA, colunaA, linhaB, colunaB);    
}

