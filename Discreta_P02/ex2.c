/* ************************************************************************ *
 *    Ex2.c, V1.0                                                           *
 *    Random permutation demonstration via lib_Cavendish.h                  *
 *                                                                          *
 * ************************************************************************ */

#include "lib_Cavendish.h"

int main(void)
{
    char c;
    int contador;
    int perm_number;
    int valid = 0;
    int* permutation;

    printf("------------------------------------------------\n");
    printf(" Welcome to the ex2 random number permuter \n");
    printf(" Powered by lib_Cavendish (no rights reserved). \n ");

    printf("\n Please insert the Maximum number : ");

    do
    {
        valid = scanf("%d", &perm_number);
        while((c=getchar()) != '\n' && c != EOF);
        if(valid != 1 || perm_number < 1)
            printf(" Error! Insira um Numero valido : ");
    }
    while(valid != 1 || perm_number < 1);

    permutation = random_n_permutation(perm_number);

    if(permutation == NULL)
        return EXIT_FAILURE;

    printf ("\n Your numbers are : ");

    
     for(contador = 0; contador < perm_number - 1; ++contador)
    //  for(contador = 0; contador < 9; ++contador) // para um teste de numeros maiores que 9 esorteia 10 numeros 
        printf("%d, ", permutation[contador]);
    printf("%d.\n", permutation[contador]);

    free(permutation);
    printf("\n");

    return EXIT_SUCCESS;
}

