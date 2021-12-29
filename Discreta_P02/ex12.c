/* ************************************************************************ *
 *    Ex12.c, V1.0                                                          *
 *    Multiplicador de matrizes esparsas                                    *
 *    Demonstration by lib_Cavendish.h                                      *
 *                                                                          *
 * ************************************************************************ */

#include "lib_Cavendish.h"

int main()
{
    printf("------------------------------------------------------\n");
    printf("   Welcome to the Ex12 Sparse Matrix Multiplicator \n");
    printf("    Powered by lib_Cavendish (no rights reserved). \n");
    printf(" ---------------------------------------------------- \n");

    int a[20][20], k[3][100], i, j, m, n, count = 0;

    printf(" Digite a quantidade de linhas desejadas: ");
    scanf("%d", &m);

    printf(" Digite a quantidade de colunas desejadas: ");
    scanf("%d", &n);
    
    printf("\n Voce devera digitar cada elemento da sua matriz A: \n(OBS: Utilize a tecla espaço pra designar as colunas e a tecla ENTER quando for determinar os elementos de uma nova linha)\n ");
    
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
           
            if(a[i][j])
            {
               k[0][count] = i;
               k[1][count] = j;
               k[2][count] = a[i][j];
               count++;
            }
        }
    }


    multiply(k, count, m, n);
} 

