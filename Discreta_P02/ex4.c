/* ************************************************************************ *
 *    Ex4.c, V1.0                                                           *
 *    FunCoes da linguagem, demonstration by lib_Cavendish.h                *
 *                                                                          *
 * ************************************************************************ */

#include "lib_Cavendish.h"

int main(void)
{
    printf("------------------------------------------------\n");
    printf(" Welcome to the Ex4 language functioner \n");
    printf(" Powered by lib_Cavendish (no rights reserved). \n ");

    char c[20];
    char d[20];
    int flag=0;
    printf("\n Digite a palavra alvo : \n  ");
    scanf("%s", c);
    printf("\n Digite um pedaço de uma palavra para verificar a sua classificacao : \n  ");
    scanf("%s", d);

    flag+=kprefix(c,d);  //Prefixo
    flag+=ksufix(c,d);   //Sufixo
    flag+=ksubword(c,d); //Sub-palavra (no meio)

    switch (flag)
    {
        case 0:
            printf("\n  Nao possui relacao com a palavra ou eh a igual a primeira palavra inserida \n\n");
            break;
        case 1:
            printf("\n  Eh um prefixo da palavra \n\n");
            break;
        case 2:
            printf("\n  Eh um sufixo da palavra \n\n");
            break;
        case 3:
            printf("\n  Eh uma sub-palavra \n\n");
            break;
        default:
            printf("\n  Erro !\n");
            break;
    } 

return 0;
}
