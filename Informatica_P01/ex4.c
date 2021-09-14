#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num1, num2, div;
    printf(" Calculadora.\n\n");

    printf(" Digite o primeiro numero: ");
    scanf( "%f", &num1 );
    printf(" Digite o segundo numero: ");
    scanf( "%f", &num2 );

    div = num1 / num2 ;

    printf( "\n O resultado da divisao eh : %f\n", div );

    return 0;
}
