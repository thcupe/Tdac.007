/********************************************************************************************
 *   lib_Cavendish.c                                                                        *
 *                                                                                          *
 * Descrição do programa: Biblioteca pessoal                                                *
 * Copyright (C) Thiago De Azevedo Cavendish, 2021                                          *
 *                                                                                          *
 * 2021-11-28                                                                               *
 * Contato: tac@poli.br                                                                     *
 ********************************************************************************************/

/* ---------------------------------------------------------------------------------------- */
/* includes na Biblioteca pessoal.h                                                         */

#include "lib_Cavendish.h" 

/* --------------------------------------------------------------------------------------- */
/*
 * @ingroup GroupUnique
 * @brief Random Permutation Based on a Number
 * @details Randomly Permutes a set of 0 to rand_max-1 with rand_max members and no repetitions.

 * @param[in] rand_max maximum random value generated, and also the number of members
 *
 * @returns array storing the permutation(must have size equal to n)
 * @retval NULL if it fails to allocate memory
 *
 * @warning remember to free up the var later!
 *
 */
/* --------------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------------- */
/* -----------------  FunCOes personalizadas  -------------------- */
/* --------------------------------------------------------------------------------------- */

int* random_n_permutation(int rand_max) // PermutaCAo aleatOria
{
    int buffer; /* temp buffer to store swaps */
    int contador;
    int shuffler; // embaralhador
    int* permutation = malloc(rand_max * sizeof(int)); /* permuted array */

    if(permutation == NULL)
    {
        printf(" Error: Failed to allocate memory!\n");
        return permutation;
    }

    /* set up the base sorted array */
    for(contador = 0; contador < rand_max; ++contador)
        permutation[contador] = 1 + contador;

    /* shuffles them based on the modern fisher-yates shuffle, taken from wikipedia */
    for(contador = rand_max - 1; contador > 1; --contador)
    {
        srand(time(NULL));

        shuffler = rand()%(contador+1); /* random int from 0 to contador */
        buffer = permutation[contador];
        permutation[contador] = permutation[shuffler];
        permutation[shuffler] = buffer;
    }

    return permutation;
}


/* --------------------------------------------------------------------------------------- */

void normalizer() // Normalizador
{
 // VariAveis declaradas
    float min,max,x;
    float result;

    srand(time(NULL));

    min = rand() % 100;
    max = 0;

    while(max <= min)
    {
        max = rand() % 100;
    }
    while(x < min || x > max)
    {
       x = rand() % 100;
    }

    result = (x - min)/(max - min);

    printf("\n  NUmero Minimo eh : %.0f\n ", min);
    printf(" NUmero Maximo eh : %.0f\n ", max);
    printf(" NUmero a ser normalizado eh : %.0f\n", x);
    printf("  Resultado eh : %.2f\n ", result);
    printf("\n");
}


/* --------------------------------------------------------------------------------------- */

/* -------------- FunCoes da linguagem --------------- */

int kprefix(char a[20],char e[20]) //Prefixo
{
    char b[4];

    for(int i=0;i<3;i++)
    {
        b[i]=a[i];
    }
    if(strstr(b,e) != NULL)
    {
       return 1;
    }
    else
     return 0;
}

int ksufix(char a[20], char e[20]) //Sufixo
{
    int k = strlen(a);
    char c[4];
    int j=0;

    for(int l=3;l>0;l-=1)
    {
        c[j]=a[k-l];
        j+=1;
    }
    if(strstr(c,e) != NULL)
    {
       return 2;
    }
    else
     return 0;
}

int ksubword(char a[20],char e[20]) //Sub_palavra (no meio)
{
    int k = strlen(a);
    char d[20];
    int j=0;

    for(int i=3;i<k-3;i++)
    {
        d[j]=a[i];
        j++;
    }
    if(strstr(d,e))
    {
       return 3;
    }
    else
     return 0;
}


/* --------------------------------------------------------------------------------------- */
//void inv(char *string) //invertedor de string inicial
//{
//   if(*string)
//   {
//          inv(string+1);
//          putchar(*string);
//   }
//}
/* --------------------------------------------------------------------------------------- */


/* -------------- Matrix multiplicator --------------- */

int Fmatriz(int i, int j, int linhaA, int colunaA, int linhaB, int colunaB, int x)
{
   float matrizA[linhaA][colunaA], matrizB[linhaB][colunaB], matrizC[linhaA][colunaB], aux = 0;
  
  // printf("\n");

   if(colunaA == linhaB)
   {
      for(i = 0; i < linhaA; i++)
      {
          for(j = 0; j < colunaA; j++)
          {
           printf("\n\n Informe o valor da %da Linha e da %da Coluna da Matriz A:  ", i+1, j+1);
           scanf("%f", &matrizA[i][j]);
          }
          printf("\n");
      }
     
      printf("\n");

      for(i = 0; i < linhaB; i++)
      {
          for(j = 0; j < colunaB; j++)
          {
           printf("\n\n Informe o valor da %da Linha e da %da Coluna da Matriz B: ", i+1, j+1);
           scanf("%f", &matrizB[i][j]);
          }
          printf("\n");
      }

      printf("\n\n");

// Imprime as matrizes definidas
    printf("---------------------------- 1 - Matriz Gerada ---------------------------------\n\n");

      for(i = 0; i < linhaA; i++)
      {
          for(j = 0; j < colunaA; j++)
          {
           printf("%7.f", matrizA[i][j]);
          }
          printf("\n\n");
      }

    printf("---------------------------- 2 - Matriz Gerada ---------------------------------\n\n");

      for(i = 0; i < linhaB; i++)
      {
          for(j = 0; j < colunaB; j++)
          {
           printf("%7.f", matrizB[i][j]);
          }
          printf("\n\n");
      }

//  printf("---------------------------- 3 - Matriz Gerada ---------------------------------\n\n");
//  para um projeto futuro

    printf("--------------------------- 3 - Produto gerado ---------------------------------\n\n");
 // Processamento e saida em tela  =  PRODUTO DAS MATRIZES
      for(i = 0; i < linhaA; i++)
      {
          for(j = 0; j < colunaB; j++)
          {
              matrizC[i][j] = 0;
              for(x = 0; x < linhaB; x++)
              {
                  aux +=  matrizA[i][x] * matrizB[x][j];
              }
                  matrizC[i][j] = aux;
                  aux = 0;
          }
      }

      for(i = 0; i < linhaA; i++)
      {
          for(j = 0; j < colunaB; j++)
          {
              printf("%7.f", matrizC[i][j]);
          }
              printf("\n\n");
      }

    printf("--------------------------------------------------------------------------------\n\n");
  //  printf("\n");
   }
   else
   {
    printf("\n\n NAo eh possivel multiplicar as matrizes geradas ! \n");
   }
}


/* --------------------------------------------------------------------------------------- */

/* -------------- Random Matrix multiplicator --------------- */

int Fmatrizale(int linhaA, int colunaA, int linhaB, int colunaB)
{
   int matrizA[linhaA][colunaA], matrizB[linhaB][colunaB], matrizC[linhaA][colunaB], aux = 0;
   int i, j, x, iAux, jAux, flag=0;

   printf("\n");
   srand(time(NULL));
   
   if(colunaA == linhaB)
   {
      for(i = 0; i < linhaA; i++)
      {
          for(j = 0; j < colunaA; j++)
          {
              flag = 0;
              matrizA[i][j] = rand() % 500;
         
              if(i != 0 && j != 0)
              {
                 for(iAux=0; iAux<i; iAux++)
                 {
                     for(jAux=0; jAux<j; jAux++)
                     {
                         if(matrizA[iAux][jAux] == matrizA[i][j])
                            flag = 1; // Valor repetido
                     }
                 }
              }

           if(flag == 1) // Numero repetido
           {
              j -= 1; // Repete esse mesmo ciclo para gerar outro valor aleatorio
           }
          }
      }

    for(i = 0; i < linhaB; i++)
    {
        for(j = 0; j < colunaB; j++)
        {
            flag = 0;
            matrizB[i][j] = rand() % 500;
            
            if(i != 0 && j != 0)
            {
               for(iAux = 0; iAux < i; iAux++)
               {
                for(jAux=0; jAux<j; jAux++)
                {
                    if(matrizB[iAux][jAux] == matrizB[i][j])
                       flag = 1; // Valor repetido
                }
               }
            }

            if(flag == 1) // Numero repetido
            {
               j -= 1; // Repete esse mesmo ciclo para gerar mais um valor aleatorio
            }
        }
    }

// Imprime as matrizes definidas
 // printf("\n");
    printf("\n---------------------------- 1 - Matriz A ---------------------------------\n\n");

    for(i = 0; i < linhaA; i++)
    {
        for(j = 0; j < colunaA; j++)
        {
            printf("%6i", matrizA[i][j]);
        }
        printf("\n\n");
    }

    printf("---------------------------- 2 - Matriz B ---------------------------------\n\n");

    for(i = 0; i < linhaB; i++)
    {
        for(j = 0; j < colunaB; j++)
        {
            printf("%6i", matrizB[i][j]);
        }
        printf("\n\n");
    }

//    printf("---------------------------- 3 - Matriz A * Matriz B ---------------------------------\n\n");
//  para um projeto futuro

    printf("--------------------------- 3 - Produto gerado ---------------------------------\n\n");
 // Processamento e saida em tela  =  PRODUTO DAS MATRIZES
    for(i = 0; i < linhaA; i++)
    {
        for(j = 0; j < colunaB; j++)
        {
            matrizC[i][j] = 0;
           
            for(x = 0; x < linhaB; x++)
            {
                aux +=  matrizA[i][x] * matrizB[x][j];
            }
            matrizC[i][j] = aux;
            aux = 0;
        }
    }

    for(i = 0; i < linhaA; i++)
    {
        for(j = 0; j < colunaB; j++)
        {
            printf("%10i", matrizC[i][j]);
        }
        printf("\n\n");
    }
   printf("--------------------------------------------------------------------------------\n\n"); 
  //  printf("\n\n");
   }
   else
   {
    printf("\n\n NAo eh possivel multiplicar as matrizes geradas ! \n");
   }
}
/* --------------------------------------------------------------------------------------- */

/* -------------- Sparse Matrix multiplicator --------------- */

void print(int k[3][100], int count)
{
    int i, j;

   // printf("\n----------------------------------------------------\n");
   // printf("\n           A sua matriz esparsa eh:           \n");
   // printf("\n----------------------------------------------------\n");
   
    printf("%d",count);

    for (j = 0; j < 3; j++)
    {
        for(i = 0; i < count; i++)
        {
            printf("%d", k[j][i]);
        }
        printf("\n");
    }
    printf("%d",count);
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int k[3][100], int count)
{
    int i, j;

    for(i = 0; i < count; i++)
    {
        for(j = 0; j < count - i - 1; j++)
        {

            if(k[0][j] > k[0][j + 1])
            {
               swap(&k[0][j], &k[0][j + 1]);
               swap(&k[1][j], &k[1][j + 1]);
               swap(&k[2][j], &k[2][j + 1]);
            }
            else if(k[0][j] == k[0][j + 1])
            {
                if(k[1][j] > k[1][j + 1])
                {
                   swap(&k[0][j], &k[0][j + 1]);
                   swap(&k[1][j], &k[1][j + 1]);
                   swap(&k[2][j], &k[2][j + 1]);
                }
            }
        }
    }
}

void transpose(int k[3][100], int count)
{
    int i, j, temp;

    printf("\n");

    for(j = 0; j < count; j++)
    {

        swap(&k[0][j], &k[1][j]);
    }
    sort(k, count);
    print(k,count);
}

void multiply(int k[3][100], int count, int r1, int c1)
{
    int b[20][20], l[3][100], i, j, r2, c2, size = 0, kpos, lpos, result[3][100], r, c, tempk, templ, sum, rcount = 0;

    printf("\n Agora declare a quantidade de linhas da matriz B: ");
    scanf("%d", &r2);

    printf("\n Agora declare a quantidade de colunas da matriz B: ");
    scanf("%d", &c2);

    printf("\n Digite cada elemento da sua matriz B: \n(OBS: Utilize a tecla EspaCo pra designar as colunas e a tecla ENTER quando for determinar os elementos de uma nova linha) \n ");

    for(i = 0; i < r2; i++)
    {
        for(j = 0; j < c2; j++)
        {
            scanf("%d", &b[i][j]);

            if(b[i][j] != 0)
            {
               l[0][size] = i;
               l[1][size] = j;
               l[2][size] = b[i][j];

             size++;
            }
        }
    }

    printf("\n----------------------------------------------------\n");
    printf("\n           A sua matriz esparsa eh:           \n");
    printf("\n----------------------------------------------------\n");

    if (c1 != r2)
    {
        printf(" Not possible ! \n");
        printf("---------------------------------------------------- \n");

        return;
    }

    transpose(l, size);

    for(kpos = 0; kpos < count;)
    {
        r = k[0][kpos];

        for(lpos = 0; lpos < size;)
        {
            c = l[0][lpos];

            tempk = kpos;
            templ = lpos;

            sum = 0;

            while(tempk < count && k[0][tempk] == r && templ < size && l[0][templ] == c)
            {
                if(k[1][tempk] < l[1][templ])
                {
                 tempk++;
                }
                else if(l[1][templ] > k[1][tempk])
                {
                 templ++;
                }
                else
                {
                 sum += k[2][tempk++] * l[2][templ++];
                }
            }

            if(sum != 0)
            {
               result[0][rcount] = r;
               result[1][rcount] = c;
               result[2][rcount] = sum;
               rcount++;
            }
            while(lpos < size && l[0][lpos] == c)
            {
             lpos++;
            }
        }
        while(kpos < count && k[0][kpos] == r)
        {
         kpos++;
        }
    }

    print(result, rcount);
    printf("\n---------------------------------------------------- \n");
}

/* --------------------------------------------------------------------------------------- */ 

