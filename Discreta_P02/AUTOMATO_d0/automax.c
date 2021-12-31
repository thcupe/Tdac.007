/***************************************************************************
 *   automax.c                                 Version 20210512.104607     *
 *                                                                         *
 *   Converte AFD, AFND e ER                                               *
 *   Copyright (C) 2016-2021    by Ruben Carlo Benante                     *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation version 2 of the License.                *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Ruben Carlo Benante                                                   *
 *   Email: rcb@beco.cc                                                    *
 *   Webpage: http://www.beco.cc                                           *
 *   Phone: +55 (81) 3184-7555                                             *
 ***************************************************************************/

/* ----------------------------------------------------------------------- */
/**
 * @file automax.c
 * @ingroup GroupUnique
 * @brief Converte AFD, AFND e ER
 * @details This program really do a nice job as a template, and template only!
 * @version 20160618.013215
 * @date 2016-06-18
 * @author Ruben Carlo Benante <<rcb@beco.cc>>
 * @par Webpage
 * <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @copyright (c) 2016 GNU GPL v2
 * @note This program is free software: you can redistribute it
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
 * @todo Now that you have the template, hands on! Programme!
 * @warning Be carefull not to lose your mind in small things.
 * @bug This file right now does nothing usefull
 *
 */

/*
 * Instrucoes para compilar:
 *   $gcc automax.c -o automax.x -Wall
 *        -Wextra -ansi -pedantic-errors -g -O0 -DDEBUG=1 -DVERSION="0.1.160612.142044"
 *   ou preferencialmente inclua um makefile e use:
 *   $make
 *
 * Modelo de indentacao:
 * Estilo: --style=allman ou -A1
 *
 * Opcoes: -A1 -s4 -k3 -xj -SCNeUpv
 *
 *  * No vi use:
 *      :% !astyle -A1 -s4 -k3 -xj -SCNeUpv
 *  * No linux:
 *      $astlye -A1 -s4 -k3 -xj -SCNeUpv automax.c
 */

/* ---------------------------------------------------------------------------- */
/* Includes, definitions, etc., that cannot be in automax.h */

#include "automax.h" /* To be created for this template if needed */

/* ---------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This is the main event of the evening
 * @details Ladies and Gentleman... It's tiiiime!
 * Fightiiiiing at the blue corner,
 * he, who has compiled more C code than any other adversary in the history,
 * he, who has developed UNIX and Linux, and is an inspiration to maaany languages
 * and compilers, the GNU C Compiler, GCC!
 * Fightiiiiing at the red corner, the challenger, in his first fight, lacking of any
 * valid experience but angrily, blindly, and no doubtfully, will try to
 * compile this program without errors. He, the student, the apprentice,
 * the developer, beco!!
 *
 * @param[in] argc Argument counter
 * @param[in] argv Argument strings (argument values)
 *
 * @retval 0 If succeed (EXIT_SUCCESS).
 * @retval 1 Or another error code if failed.
 *
 * @par Example
 * @code
 *    $./automax -h
 * @endcode
 *
 * @warning   Be carefull with...
 * @bug There is a bug with...
 * @todo Need to do...
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Ruben Carlo Benante
 * @version 20210512.104607
 * @date 2016-06-18
 *
 */
/* ------------------------------------------------------------------------------ */

int main(int argc, char *argv[])
{
    int opt; // return from getopt() //
    int convert = 0; // Controla o tipo de conversAo de automato //
    int entrada = 1; // Controla o tipo de entrada -> 0 (Arquivo) e 1 (Manual) //

    char name_file[SBUFF]; // Recebe optarg da flag (-f) //
    char str[SBUFF]; // Recebe a string do Auto3 //

    char entrada1[SBUFF] = "01-teste-AFND.txt";
    char entrada2[SBUFF] = "02-teste-AFND.txt";
    FILE *file; // Arquivo para entrada //
    FILE *arq = NULL; // Entrada manual do Auto 3 //
    FILE *read; // arquivo usado para entrada da string //

    t_quintupla *AFND = NULL;
    t_quintupla *AFD = NULL;


//    IFDEBUG("Starting optarg loop...");

    /* getopt() configured options:
     *        -h  help
     *        -c  copyright and version
     *        -v  verbose
     *        -f  given file name
     */
    opterr = 0;

    while((opt = getopt(argc, argv, "vhcf:nde")) != EOF)
        switch(opt)
        {
            case 'h': // Help //
                help();
                break;
            case 'c': // Copyright //
                copyr();
                break;
            case 'v':
                verb++;
                break;
            case 'f': // File //
                strncpy(name_file, optarg, SBUFF); // Recebe o nome do arquivo //
                entrada = 0; // Entrada -> 0 = Arquivo //
                break;

                /* -n -> Entrada eh uma quIntupla AFND que serA convertida para AFD */ /* Auto 1 */
            case 'n':
                convert = 1; // Converte AFND -> AFD //
                break;

                // case 'd': /* Auto 2 */
                //    convert = 2; // Converte AFD -> ExpressAo Regular //
                //    break;

                /* -e -> Entrada eh uma string (ExpressAo Regular) que serA convertida para AFND */ /* Auto 3 */
            case 'e':
                convert = 3; // Converte ExpressAo Regular -> AFND //
                break;

            case '?':
            default:
                printf("Type\n\t$man %s\nor\n\t$%s -h\nfor help.\n\n", argv[0], argv[0]);
                return EXIT_FAILURE;
        }

    if(verb)
        printf("Verbose level set at: %d\n", verb);

    /* ------------------------------------------------------------------------ */
    /* ----------------------------- Entrada ---------------------------------- */
    /* ------------------------------------------------------------------------ */

    if(entrada) // Manual //
    {
        if(convert == 1 || convert == 2)    // Convert 1 e 2 //
            m_recebe_AFND(&AFND);           // Entrada da quintupla //
        else
        {
            arq = fopen("temp.txt", "a");
            scanf("%s", str);               // Entrada manual //
            fprintf(arq, "%s", str);
            fflush(arq);                    // Atualiza arquivo //
            read = fopen("temp.txt", "r");  // Modo leitura //
            le_arquivo(read);               // ConversAo de ER -> AFND //
            remove("temp.txt");             // Remove //
        }
    }
    else // Entrada por arquivo //
    {
        file = fopen(name_file, "r"); // Abre arquivo com o nome recebido //

        if(!file)                    // Se o arquivo estiver vazio, para o codigo //
            exit(EXIT_SUCCESS);
    }

    /* ------------------------------------------------------------------------ */
    /* ---------------------------- ConversAo --------------------------------- */
    /* ------------------------------------------------------------------------ */

    switch(convert)
    {
        case 1: // AFND -> AFD //
            if(entrada == 0)                // Arquivo //
                recebe_AFND(file, &AFND);    // Recebe AFND //
            AFD = Calc_AFD(AFND);       // Retorna a conversAo //
            print_quintupla(AFD);           // Imprime o AFD //
            break;

        //  case 2: // AFD -> ER //
        //      if(entrada == 0 )               // Arquivo //
        //         recebe_AFD(file, &AFND);     // Recebe AFD //
        //      AFD2er(AFND);                   // Converte para ExpressAo Regular e imprime //
        //      break;

        case 3: // ER -> AFND //
            if(entrada == 0)                // Arquivo //
                le_arquivo(file);            // Recebe arquivo contendo a ExpressAo Regular //
            break;
        default:                            // Caso nAo consiga converter -> help //
            help();
            return EXIT_FAILURE;
    }

    // automax_init(); /* global initialization function: ainda a saber para que usar se precisar */


    /* ...and we are done */
    /* Write your code here... */

    return EXIT_SUCCESS;
}

/* Write your functions here... */

/* ------------------------------------------------------------------------ */
/**
 * @ingroup GroupUnique
 * @brief Prints help information and exit
 * @details Prints help information (usually called by opt -h)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160618.013215
 * @date 2016-06-18
 *
 */
/* ------------------------------------------------------------------------ */
void help(void)
{
    // IFDEBUG("help()");
    printf("%s - %s\n", "automax", "Converte AFD, AFND e ER");
    printf("\nUsage: %s [-h|-v]\n", "automax");
    printf("\nOptions:\n");
    printf("\t-h,  --help\n\t\tShow this help.\n");
    printf("\t-c,  --copyright, --version\n\t\tShow version and copyright information.\n");
    printf("\t-v,  --verbose\n\t\tSet verbose level (cumulative).\n");
    printf("\t-f, --file\n\t\tSet the input filename.\n");
    /* add more options here */
    printf("\t-n, --nfa\n\t\tInput data is a NFA (Nondeterministic Finite Automata) 5-tuple to be converted to a DFA (Deterministic Finite Automata) 5-tuple.\n");
    printf("\t-e, --re\n\t\tInput data is a RE (Regular Expression) string to be converted to a NFA (Nondeterministic Finite Automata) 5-tuple.\n");
    printf("\t-d, --dfa\n\t\tInput data is an DFA (Deterministic Finite Automata) 5-tuple to be converted to RE (Regular Expression) string.\n");
    /*
    * -n : a entrada de dados é uma quíntupla de um AFND que será convertido para AFD.
    * -d : a entrada de dados é uma quíntupla de um AFD que será convertido para uma ER.
    * -e : a entrada de dados é uma _string_ de uma ER que será convertida em um AFND.
    */
    printf("\nExit status:\n\t0 if ok.\n\t1 some error occurred.\n");
    printf("\nTodo:\n\tLong options not implemented yet.\n");
    printf("\nAuthor:\n\tWritten by %s <%s>\n\n", "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_FAILURE);
}

/* ------------------------------------------------------------------------ */
/**
 * @ingroup GroupUnique
 * @brief Prints version and copyright information and exit
 * @details Prints version and copyright information (usually called by opt -V)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160618.013215
 * @date 2016-06-18
 *
 */
/* ------------------------------------------------------------------------ */
void copyr(void)
{
    // IFDEBUG("copyr()");
    printf("%s - Version %s\n", "automax", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>. This  is  free  software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. USE IT AS IT IS. The author takes no responsability to any damage this software may inflige in your data.\n\n", 2016, "Ruben Carlo Benante", "rcb@beco.cc");
    if(verb > 3) printf("copyr(): Verbose: %d\n", verb); /* -vvvv */
    exit(EXIT_FAILURE);
}

/* ------------------------------------------------------------------------ */
/* Functions */
/* ------------------------------------------------------------------------ */
void m_recebe_AFND(t_quintupla **cabeca) // Entrada manual //
{
    t_quintupla *copia = *cabeca;
    char c_file[SBUFF] = "";
    int opt = 0;            // Controla o setor //
    char *token;            // LE os estados finais e delta //
    char *copiatoken;
    char parada[] = "\n";
    copia = malloc(sizeof(t_quintupla)); // AlocaCAo da memoria //

    while(fgets(c_file, sizeof(c_file), stdin) != NULL && strncmp(c_file, parada, 1) != 0)
    {
        if(opt == 1 && strstr(c_file, "#") == NULL) // Pega string, passa para nO e adiciona ao K //
            copia->K = atoi(c_file);
        if(opt == 2 && strstr(c_file, "#") == NULL) // Pega letra e adiciona ao A //
            copia->A = c_file[0];
        if(opt == 3 && strstr(c_file, "#") == NULL) // Pega string, passa para nO e adiciona ao S //
            copia->S = atoi(c_file);
        if(opt == 4 && strstr(c_file, "#") == NULL)
        {
            copiatoken = strdup(c_file);

            while((token = strsep(&copiatoken, " ")) != NULL)
                inserir_final_st(token, &copia);
        }

        if(opt == 5 && strstr(c_file, "#") == NULL)
            inserir_delta_st(c_file, &copia);

        if(strstr(c_file, "#K")) // Proxima linha = nO de estados //
            opt = 1;
        if(strstr(c_file, "#A")) // Proxima linha = Final do alfabeto //
            opt = 2;
        if(strstr(c_file, "#S")) // Proxima linha = Estado Inicial //
            opt = 3;
        if(strstr(c_file, "#F")) // Proxima linha = Estados Finais //
            opt = 4;
        if(strstr(c_file, "#D")) // Proxima linha = TransiCOes D = (ei, le, ef) //
            opt = 5;
    }
    *cabeca = copia;
    return;
}

/* ------------------------------------------------------------------------ */
void recebe_AFND(FILE *file, t_quintupla **cabeca) // Entrada por arquivo //
{
    t_quintupla *copia = *cabeca;
    copia = malloc(sizeof(t_quintupla));     // AlocaCAo da memoria //

    char c_file[256];                        // LE o arquivo //
    char *token;                             // LE os estados finais e delta //
    char *copiatoken;
    int opt = 0;                             // Controla o setor //

    while(fgets(c_file, 256, file) != NULL)  // Le o arquivo //
    {
        if(opt == 1 && strstr(c_file, "#") == NULL)
            copia->K = atoi(c_file);
        if(opt == 2 && strstr(c_file, "#") == NULL)
            copia->A = c_file[0];
        if(opt == 3 && strstr(c_file, "#") == NULL)
            copia->S = atoi(c_file);
        if(opt == 4 && strstr(c_file, "#") == NULL)
        {
            copiatoken = strdup(c_file);

            while((token = strsep(&copiatoken, " ")) != NULL)
                inserir_final_st(token, &copia);
        }

        if(opt == 5 && strstr(c_file, "#") == NULL)
        {
            inserir_delta_st(c_file, &copia); // Insere delta //
        }
        if(strstr(c_file, "#K")) // Proxima linha = nO de estados //
            opt = 1;
        if(strstr(c_file, "#A")) // Proxima linha = Final do alfabeto //
            opt = 2;
        if(strstr(c_file, "#S")) // Proxima linha = Estado Inicial //
            opt = 3;
        if(strstr(c_file, "#F")) // Proxima linha = Estados Finais //
            opt = 4;
        if(strstr(c_file, "#D")) // Proxima linha = TransiCOes D = (ei, le, ef) //
            opt = 5;
    }
    *cabeca = copia; /* passa a nova quintupla copia para a variavel cabeca */
    return;
}

/* ------------------------------------------------------------------------------ */
void print_quintupla(t_quintupla *q) // Imprime os valores da quintupla na tela //
{
    printf(" #K \n%d\n", q->K); // nO de estados //
    printf(" #A \n%c\n", q->A); // Alfabeto //
    printf(" #S \n%d\n", q->S); // Estado Inicial //
    printf(" #F \n");           // Estados Finais //

    while(q->F != NULL)   // Imprime a lista (t_lef) //
    {
        printf("%d ", q->F->f);
        q->F = q->F->prox;
    }

    printf("\n");
    printf(" #D\n");

    while(q->D != NULL)   // Imprime a lista (t_delta) //
    {
        printf("%d %s %d\n", q->D->ei, q->D->le, q->D->ef);
        q->D = q->D->prox;
    }
    return;
}

/* ----------------------------------------------------------------------------- */
t_lef *Calc_E_f(t_quintupla *q, unsigned short int num, char *test)
{
    t_lef *list = NULL;
    t_lef *t_list = NULL;
    t_delta *delta = q->D;  // Recebe delta //

    while(delta != NULL)    // Le delta //
    {
        if(delta->ei == num && (strstr(delta->le, test))) // Procura semelhanCas entre delta e o nO recebido //
        {
            inserir_final(delta->ef, &list);            // Insere o destino na lista //
            t_list = Calc_e_i(q, delta->ef);       // Calcula se esse destino pode ser feito //

            while(t_list != NULL)                       // Verifica se existe //
            {
                if(t_list->f == delta->ei)  // Verifica se eh igual //
                    t_list = t_list->prox;  // Passa para o proximo //
                else
                {
                    inserir_final(t_list->f, &list); // insere na lista //
                    t_list = t_list->prox;           // Passa para o proximo //
                }
            }
        }
        delta = delta->prox; // Passa para o proximo //
    }
    return list;    //retorna a lista de estados finais do nO recebido //
}

/* -------------------------------------------------------------------------- */
t_lef *Calc_novos_finais(t_quintupla *q, t_list_lef *base) // Calcula os novos estados finais //
{
    t_lef *novo = NULL;
    t_lef *copia = NULL;
    t_list_lef *list = base;
    t_lef *final = q->F;

    while(final != NULL)    // Continua, enquando a lista de estados finais != 0 //
    {
        list = base;
        while(list != NULL)
        {
            copia = list->F;        // Copia para fazer a comparacao //

            while(copia != NULL)    // Ate copia = 0 //
            {
                if(final->f == copia->f)                // Confere os antigos estados finais //
                {
                    inserir_final(list->ord, &novo);    // Se sim, então os adiciona na lista //
                    break;
                }
                copia = copia->prox;
            }
            list = list->prox;
        }
        final = final->prox;
    }
    return novo; // Retorna os estados finais //
}

/* -------------------------------------------------------------------------- */
t_lef *Calc_E(t_quintupla *q, t_lef *ei, char *test) // Dado uma lista de estados -> calcula seus destinos //
{
    t_lef *list = NULL;
    t_lef *t_list = NULL;

    while(ei != NULL) // enquanto a lista de estados nao for vazia //
    {
        t_list = Calc_E_f(q, ei->f, test); // calcula o estado final de um estado //
        while(t_list != NULL) // enquanto a lista destino nao for vazia //
        {
            inserir_final(t_list->f, &list); // se ainda nao tiver na lista, insere o destino //
            t_list = t_list->prox;
        }
        ei = ei->prox;
    }
    return list; // retorna lista estado destino da lista dada //
}

// ---------------------------------------------------------------------- //
t_lef *Calc_epsilon(t_quintupla *q, unsigned short int num) // Calcula os estados finais, se tiver transicao em epsilon //
{

    t_lef *list = NULL;
    t_delta *copia = q->D;  // Recebe delta //

    while(copia != NULL)
    {
        if(copia->ei == num && (strstr(copia->le, "E"))) // confere se tem trasicao em epsilon  //
            inserir_final(copia->ef, &list); // Se sim, adiciona //

        copia = copia->prox;
    }
    return list; // Retorna a lista de transiCAo //
}

/* ---------------------------------------------------------------------- */
t_lef *Calc_e_i(t_quintupla *q, unsigned short int num)
// Calcula todos os estados com transiCAo em Epsilon //
{
    t_lef *inic = NULL;
    t_lef *cop = NULL;
    t_lef *n_lef = NULL;

    inserir_final(num, &cop);       // Adiciona o nO na lista (t_lef) //
    n_lef = Calc_epsilon(q, num);   // Calcula se o nO tem transiCAO em Epsilon //

    while(n_lef != NULL)
    {
        inserir_final(n_lef->f, &cop);         // Insere o nO atual //
        inic = Calc_epsilon(q, n_lef->f);      // Calcula se esse nO tem transiCAo em Episilon //

        while(inic != NULL)                    // Se existir //
        {
            if(buscar_f(cop, inic->f) == 0)    // Verifica se esse numero ja esta na lista //
                inserir_final(inic->f, &n_lef); // Se nao, o adiciona, para ser calculado //

            inic = inic->prox;
        }
        if(buscar_f(cop, n_lef->f)) // Verifica se o valor atual ja esta na lista //
            n_lef = n_lef->prox;    // Se nao, passa para o proximo da lista //
    }
    return cop; // Retorna a lista com todas as trasicoes em Episilon //
}

/* ------------------------------------------------------------------------- */
t_delta *novo_delta(t_quintupla *q, t_list_lef *list) // Calcula uma nova lista delta, com a nova lista de estados //
{
    t_list_lef *copia = list; // Copia para teste //
    t_delta *novo = NULL;
    t_lef *destino = NULL;
    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz..."; // Testes com as letras //
    char alf = q->A;                                   // Recebe a ultima letra do alfabeto //
    char *token;
    int i = 0;                                         // Sequencia de letras //

    while(list != NULL)
    {
        while(alf != alfabeto[i - 1])           // Compara se chegou no final do alfabeto //
        {
            token = strndup(&alfabeto[i], 1);   // Recebe as letras //
            i++;                                // Soma em i para proximo ponteiro receber proxima letra //
            destino = Calc_E(q, list->F, token); // Calcula o destino da letra //

            if(destino != NULL)                 // Se existir o destino -> Adiciona delta //
                inserir_delta(ord_novo(copia, list->F),

                              token, ord_novo(copia, destino), &novo);
        }
        i = 0; // Reseta //
        list = list->prox;
    }

    return novo; // Retorna os estados novos //
}

/* ---------------------------------------------------------------------- */
t_list_lef *Calc_list_lef(t_quintupla *q, t_lef *list) // Calcula os estados //
{
    t_list_lef *ll = NULL;
    t_lef *t_list = NULL;
    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz..."; // Calcular o alfabeto //
    char alf = q->A;                                   // Recebe a ultima letra do alfabeto //
    char *token;
    int i = 0;                                         // Sequencia de letras //

    while(alf != alfabeto[i - 1]) // VE se chegou na ultima letra //
    {
        token = strndup(&alfabeto[i], 1);   // Recebe as letras //
        i++;                                // Soma em i para proximo ponteiro receber proxima letra //
        t_list = Calc_E(q, list, token);    // Calcula o destino da letra //

        if(t_list != NULL)       // Se existir o destino -> Adiciona na 'lista' //
            inserir_list_final(t_list, &ll);
    }
    return ll; // Retorna a lista //
}

/* ------------------------------------------------------------------------------ */
t_quintupla *montar_AFD(t_quintupla *q, t_delta *delta, t_list_lef *list, t_lef *ef)
// Recebe as listas anteriores e monta a lista AFD  //
{
    t_quintupla *novo = NULL;
    t_list_lef *copia = list;
    int i = 0;  // NO de estados novos //

    while(copia != NULL) // Confere a qntd de estados novos //
    {
        i++; // +1 para cada novo estado encontrado //
        copia = copia->prox;
    }
    novo = malloc(sizeof(t_quintupla));  // AlocaCAo de memoria //

    novo->K = i;                         // #K = Num de estados //
    novo->A = q->A;                      // #A = Alfabeto do AFnD //
    novo->S = 0;                         // #S = Estado inicial da nova lista //
    novo->F = ef;                        // #F = Novos estados finais //
    novo->D = delta;                     // #D = Lista de estados de transiCAo //

    return novo;                         // Retorna o AFD //
}

/* ---------------------------------------------------------------------------------- */
/* ---------------------------- AFND -> AFD ----------------------------------------- */
/* ---------------------------------------------------------------------------------- */

t_quintupla *Calc_AFD(t_quintupla *q) // Auto 1 //
{
    t_quintupla *AFD = NULL;
    t_delta *n_delta = NULL;
    t_list_lef *base = NULL;
    t_list_lef *ll = NULL;
    t_list_lef *calculo = NULL;
    t_lef *inic = NULL;
    t_lef *n_lef = NULL;

    inic = Calc_e_i(q, q->S);      // Calcula o estado inicial //
    inserir_list_final(inic, &base);    // Adiciona os novos estados //
    ll = Calc_list_lef(q, inic);        // Calcula os estados finais //

    while(ll != NULL)
    {
        calculo = Calc_list_lef(q, ll->F);  // Calcula os estados finais //
        while(calculo != NULL)
        {
            if(buscar_list(calculo->F, base) == 0)  // Caso nao exista o estado final na lista //
                inserir_list_final(calculo->F, &ll); // Adiciona na lista (II) , para calcular os estados finais //
            calculo = calculo->prox;               // Para o proximo da lista //
        }
        inserir_list_final(ll->F, &base);         // Adiciona o valor final na lista //
        ll = ll->prox;                            // Para o proximo da lista //
    }
    n_delta = novo_delta(q, base);          // Calcula o novo delta com a nova lista //
    n_lef = Calc_novos_finais(q, base);     // Calcula a nova lista de estados finais que podem ser aceitados //
    AFD = montar_AFD(q, n_delta, base, n_lef); // Monta o AFD com os valores calculados anteriormente //

    return AFD;                             // Retorna o AFD //
}

/* ------------------------------------------------------------------------------ */
int ord_novo(t_list_lef *list, t_lef *lef) // Confere a ordem dos estados na nova lista //
{
    while(list != NULL)
    {
        if(buscar(list->F, lef) == 1) // Se estiver na lista -> Retorna a ordem //
            return list->ord;
        list = list->prox;
    }

    return -1;                       // Se NAO estiver na lista -> Morte = -1 //
}

/* ------------------------------------------------------------------------------ */
int delta_existe(t_quintupla *q, unsigned short int num, char *test)
// Verifica se esta na lista delta  e se a transiCAo pode ser feita //
{
    t_delta *delta = q->D;

    while(delta != NULL)
    {
        if(delta->ei == num && (strstr(delta->le, test))) // Se existe -> retorna 1 //
            return 1;
        delta = delta->prox;
    }
    return 0;         // Se NAO tiver transiCAo -> Retorna 0 //
}

/* -------------------------------------------------------------------------------- */
int buscar(t_lef *est, t_lef *est2)  // Confere se as listas tem os mesmo valores //
{
    if(est == NULL || est2 == NULL)  // Se sim -> retorna 0 //
        return 0;

    while(est != NULL && est2 != NULL)
    {
        if(est->f != est2->f) // Se != -> retorna 0 //
            return 0;
        est2 = est2->prox;
        est = est->prox;
    }
    if(est == NULL && est2 == NULL) // Se forem = NULL -> retorna 1 //
        return 1;
    else                            // Se nao -> retorna 0 //
        return 0;
}

/* ------------------------------------------------------------------------ */
int buscar_f(t_lef *est, unsigned short int num) // Verifica se existe no t_lef //
{
    while(est != NULL)
    {
        if(est->f == num)
            return 1;
        est = est->prox;
    }
    return 0;   // Se tudo ok -> retorna 0 //
}

/* ------------------------------------------------------------------------------ */
int buscar_list(t_lef *est, t_list_lef *list) // Verifica se existe uma lista t_lef //
{
    if(est == NULL || list == NULL)
        return 0;

    while(list != NULL)
    {
        if(buscar(est, list->F) == 1)   // Se forem = -> retorna 1 //
            return 1;
        list = list->prox;
    }

    return 0;   // Caso != -> retorna 0 //
}

/* ---------------------------------------------------------------------- */
void juntar_lef_list(t_list_lef *est, t_list_lef **est2) // Junta as listas //
{
    while(est != NULL)
    {
        if(buscar_list(est->F, (*est2)) == 0) // Verifica a existEncia na lista //
            inserir_list_final(est->F, est2);
        est = est->prox;
    }
    return;
}

/* ---------------------------------------------------------------------- */
void remover_list_final(t_lef *est, t_list_lef **cabeca)
{
    t_list_lef *copia = *cabeca;
    t_list_lef *plant = NULL;

    if(est == NULL)
        return;

    while(copia != NULL)
    {
        if(buscar(copia->F, est) != 0) // Se achar o estado na lista para o loop //
            break;

        plant = copia;
        copia = copia->prox;
    }
    if(copia == NULL)   // Se nao existe copia retorna //
        return;

    if(plant != NULL)   // Se achou e plant existe retira est da sequencia //
        plant->prox = copia->prox;
    else
        *cabeca = copia->prox;
    free(copia);
    return;
}

/* ---------------------------------------------------------------------- */
void inserir_list_final(t_lef *est, t_list_lef **cabeca)  // Inserir um t_lef de uma t_list_lef //
{
    t_list_lef *copia = *cabeca;
    t_list_lef *plant = NULL;

    if(est == NULL)
        return;

    if(buscar_list(est, (*cabeca)) == 1)
        return;

    while(copia != NULL)
    {
        if(copia->F == est) // se copia tiver mesmo ponteiro de est retorna //
            return;

        plant = copia;
        copia = copia->prox;
    }

    copia = malloc(sizeof(t_list_lef)); // AlocaCao de memoria //
    if(plant != NULL)
        copia->ord = plant->ord + 1;
    else                                // Caso seja o primeiro -> recebe 0 //
        copia->ord = 0;
    copia->F = est;
    copia->prox = NULL;
    if(plant != NULL)
        plant->prox = copia;
    else
        *cabeca = copia;

    return;
}

/* ---------------------------------------------------------------------- */
void inserir_final(int num, t_lef **cabeca) // Insere um numero em uma t_lef //
{
    t_lef *copia = *cabeca; // Copia recebe cabeca //

    while(copia != NULL)
    {
        if(copia->f == num)
            return;
        copia = copia->prox;
    }

    t_lef *aux, *novo = malloc(sizeof(t_lef)); // AlocaCAo memoria para novo nodo //
    novo->f = num; /* recebe num */

    if(*cabeca == NULL)
    {
        novo->prox = NULL;
        *cabeca = novo;
    }
    else
        if(novo->f < (*cabeca)->f)
        {
            novo->prox = *cabeca;
            *cabeca = novo;
        }
        else
        {
            aux = *cabeca;

            while(aux->prox && novo->f > aux->prox->f) // Acha o proximo nodo que seja maior que o nO //
                aux = aux->prox;

            novo->prox = aux->prox;
            aux->prox = novo;
        }
    return;
}

/* ---------------------------------------------------------------------- */
void inserir_delta(int EI, char *LE, int EF, t_delta **cabeca)
{
    t_delta *copia = *cabeca;
    t_delta *plant = NULL;

    while(copia != NULL)
    {
        plant = copia;
        copia = copia->prox;
    }
    copia = malloc(sizeof(t_delta));
    copia->ei = EI;
    copia->le = LE;
    copia->ef = EF;
    copia->prox = NULL;

    if(plant != NULL)
        plant->prox = copia;
    else
        *cabeca = copia;
    return;
}

/* ---------------------------------------------------------------------- */
void inserir_final_st(char *palavra, t_quintupla **cabeca)
{
    t_lef *copia = (*cabeca)->F;
    t_lef *plant = NULL;

    while(copia != NULL)
    {
        plant = copia;
        copia = copia->prox;
    }
    copia = malloc(sizeof(t_lef));
    copia->f = atoi(palavra);       // recebe e passa um char para int //
    copia->prox = NULL;

    if(plant != NULL)
        plant->prox = copia;
    else
        (*cabeca)->F = copia;
    return;
}

/* ---------------------------------------------------------------------------------- */
void inserir_delta_st(char *palavra, t_quintupla **cabeca)
{
    t_delta *copia = (*cabeca)->D;
    t_delta *plant = NULL;
    char *token;                   // Para copiar a palavra //
    while(copia != NULL)
    {
        plant = copia;
        copia = copia->prox;
    }
    copia = malloc(sizeof(t_delta));
    token = strdup(palavra);
    copia->ei = atoi(strsep(&token, " "));  // Primeira parte da palavra -> passa pra int //
    copia->le = strsep(&token, " ");
    copia->ef = atoi(strsep(&token, " "));  // Terceira parte da palavra -> passa pra int //
    copia->prox = NULL;

    if(plant != NULL)
        plant->prox = copia;
    else
        (*cabeca)->D = copia;
    return;
}

/* ---------------------------------------------------------------------------------- */
/* ------------------------------ ER -> AFND ---------------------------------------- */
/* ---------------------------------------------------------------------------------- */
void le_arquivo(FILE *exp_reg) // LE o arquivo do Processo //
{
    char c; // Variável que receberá o caracter da leitura do arquivo de texto //
    char palavra[SBUFF] = ""; // Chamada do allegro //
    int i = 0;
    int j = 0;
    int k = 0; // Realiza o loop auxiliar //
    int contagem = 96; // Conta os caracteres da tabela ascii a partir do numero 96 (letra a) //
    int fsize = 0; // conta a quant de caracteres no arquivo //

    int p1 = 0; // ParEntese aberto (  //
    int p2 = 0; // Parêntese fechado ) //
    t_delta conteudo = {0}; // Armazenará o conteUdo do arquivo de texto //

    if(exp_reg == NULL) // Caso a leitura do arquivo seja vazia, retorna para a função main //
        return;

    while((c = fgetc(exp_reg)) != EOF)
    {
        fsize++; // Incrementa +1 ma contagem de caracteres //

        if(fsize == 1)
        {
            conteudo.le = (char *)malloc(sizeof(char) * 2); // AlocaCAo de memOria //
            conteudo.le[fsize - 1] = c; // Subtrai 1 da posição //
            conteudo.le[fsize] = '\0'; //Define a posição seguinte do array como final.
        }
        conteudo.le = (char *)realloc(conteudo.le, strlen(conteudo.le) + 2);
        conteudo.le[fsize - 1] = c; // Subtrai 1 da posiCao //
        conteudo.le[fsize] = '\0'; //Define a posição seguinte do array como final.

        if(c != '\n')
            palavra[k] = c;
        if(c == '(')
            p1++;
        if(c == ')')
            p2++;
        k++;

    }
    if(p1 != p2)
        exit(1);
    while(conteudo.le[i] != '\0')
    {
        for(j = 97; j < 123; j++)
        {
            if(conteudo.le[i] == j)
            {
                if(conteudo.le[i] != contagem)
                {
                    if(conteudo.le[i] > contagem)
                        contagem = j;
                }
            }
        }


        i++;
    }

    alfabeto.A = contagem;

    divide_expressao(conteudo);

    fclose(exp_reg); //Fecha o arquivo de texto.
    return;
}

/* ---------------------------------------------------------------------- */
//Divide a string er em seus caracteres para serem analisados//

void divide_expressao(t_delta conteudo1) //Recebe o conteúdo de 'conteudo' na função 'le_arquivo'.
{
    t_delta aux = conteudo1; //Atribui para 'aux' o conteúdo de 'e_comp' que, no caso, seria a leitura do arquivo .txt.

    int i; //Variável utilizada para mudança do vetor.
    int j; //Variável utilizada no 'for' que está no fim da função.
    int size_linha; //Irá receber o tamanho total da linha do arquivo .txt.
    int aux1 = 0; //Variável utilizada para mudança do vetor 'string[aux1]'.
    int modo = 0; //Variável utilizada no 'switch' para definir se o 'case' será '0' ou '1'.

    char *caract = NULL; //Variável que armazenará cada caractere da linha.
    char *string[SBUFF] = {0}; //Variável que armazenará, por partes, a linha inteira como String.

    unsigned short int est = 0; //Declara a variável 'est' e define o seu valor inicial.
    t_quintupla *novo_AFND = NULL;

    novo_AFND = gerar_quintupla();

    size_linha = strlen(aux.le); //Armazena o tamanho da linha na variável 'size_linha'.
    caract = malloc(2 * sizeof(char));

    for(i = 0; i < size_linha; i++) //'for' que percorre todo o array de 'aux.le[i]' lendo caractere por caractere até chegar ao tamanho total da linha;
    {
        if((aux.le[i] == '(' && aux.le[i + 2] == ')') || (aux.le[i] == ')' && aux.le[i - 2] == '('))
            i++;
        *caract = aux.le[i]; //Recebe a primeira posição (caractere) da leitura da linha do arquivo .txt.
        caract[1] = '\0'; //Define esta posição do array como nula ou como o fim.

        switch(modo)
        {
            case 0:
                if(string[aux1] == NULL) //Verifica se a string é nula, ou seja, se não há nada ainda.
                {
                    string[aux1] = (char *)malloc(sizeof(char));
                    strcpy(string[aux1], caract); //Copia o caractere lido para a string.
                }
                else
                {
                    if(aux.le[i] == '|') //Quando o caractere lido é '|', ele passa pra próxima posição do array 'string[aux1]', dividindo a linha a cada vez que encontra um '|'.
                    {
                        modo = 0; //Mantém o 'case' em '0'.
                        aux1++; //Passa para a próxima posição do array 'string[aux1]'.
                    }
                    else
                    {
                        if(aux.le[i] == '(') //Caso o caractere a ser lido seja um parêntese aberto, muda o valor de 'tipo' para 1, mudando o 'case' de '0' para '1'.
                        {
                            modo = 1; //Muda o 'case' de '0' para '1'.
                        }
                        string[aux1] = (char *)realloc(string[aux1], strlen(string[aux1]) + 2);
                        strcat(string[aux1], caract); //Sempre que o novo caractere for diferente de '|' e '(', ele é implementado a string.
                    }
                }
                break;

            case 1: //O código rodará no 'case 1' até que seja lido um parêntese fechado.
                if(aux.le[i] != '(')
                {
                    if(aux.le[i] == ')')  //Se ler o parêntese fechado, retorna ao 'case 0', fazendo o armazenamento normal dos caracteres.
                    {
                        modo = 0; //Muda o 'case' de '1' para '0'.
                    }
                    strcat(string[aux1], caract); //Caso o caractere seja diferente de '(' e ')', implementa ele na string.
                }
                break;
        }
    }
    for(j = 0; j <= aux1; j++)
        conversao_er_AFND(string[j], novo_AFND, &est);
    delta_er(novo_AFND->D);
    return;
}

/* ---------------------------------------------------------------------- */
//inicia o espaco na RAM //

t_quintupla *gerar_quintupla(void)
{
    t_quintupla *pl = NULL;

    pl = malloc(sizeof(t_quintupla));

    pl->D = NULL;

    return pl;
}
/* ---------------------------------------------------------------------- */
//responsavel pela parte geral da converssao//

void conversao_er_AFND(char linha[SBUFF], t_quintupla *novo_AFND, unsigned short int *est)
{

    int i = 0; //Variável que representará a posição de 'linha'.

    int cont_aux;
    int ascii;
    int est_aux;
    int contagem = 0;
    int estrela = 0;
    int pesquisa_ef = 0;
    int ei[SBUFF]; //Estados iniciais.
    int cont_ei = 0; //Variável que representará a posição de 'ei'.
    char E = 'E'; //Variável que armazena a letra 'E', a qual simula a letra 'Épsilon'.

    t_quintupla *list_auto = novo_AFND;

    while(linha[i] != '\0')  //Roda o laço até chegar ao fim da palavra.
    {

        if((linha[i] == '.') || ((linha[i] > 96 && linha[i] < 123) && linha[i + 1] == '(') || (linha[i] == ')' && (linha[i + 1] > 96 && linha[i + 1] < 123)))
        {
            organiza_listas(&list_auto->D, *est, E, *est + 1);
            *est += 1;
        }
        if(linha[i] != '\n' && linha[i] != '*' && linha[i] != '.')  //Caso o caracter lido seja uma letra.
        {
            if(i == 0)
            {
                if(*est != 0)  //Ao entrar nesse 'if', o '*est' terá o mesmo valor dos estados de aceitação.
                {
                    pesquisa_ef = buscar_ef(F, *est);
                    if(pesquisa_ef == 0)
                        inserir_ef(&F, *est);
                }
                *est += 1;
                organiza_listas(&list_auto->D, 0, E, *est);
            }

            if(linha[i + 1] == '*')
            {
                estrela = 1;
                if(linha[i] == ')')
                {
                    organiza_listas(&list_auto->D, *est, E, *est + 1);
                    *est += 1;


                    if(cont_ei == 0)
                        montar_loop(list_auto, ei[1], *est);

                    else
                        montar_loop(list_auto, ei[cont_ei], *est);
                }
                else
                    montar_estrela(novo_AFND, linha[i], est);
            }
            else
            {
                if(linha[i] == '(' || linha[i] == ')')
                {
                    if(linha[i] == ')')
                        cont_ei -= 1;
                    else
                    {
                        organiza_listas(&list_auto->D, *est, E, *est + 1);
                        cont_ei += 1;
                        ei[cont_ei] = *est;
                        *est += 1;
                    }
                }
                else
                {
                    if(linha[i] == '|')
                    {
                        organiza_listas(&list_auto->D, ei[cont_ei], E, *est + 1);
                        *est += 1;
                    }
                    else
                    {
                        organiza_listas(&list_auto->D, *est, linha[i], *est + 1);
                        *est += 1;
                        if(linha[i + 1] == '|')
                        {
                            cont_aux = i + 1;
                            while(linha[cont_aux] != '\0')
                            {
                                ascii = linha[cont_aux];
                                if(ascii > 96 && ascii < 123)
                                    contagem++;
                                cont_aux++;
                            }
                            est_aux = (contagem * 2) + 1;
                            organiza_listas(&list_auto->D, *est, E, *est + est_aux);
                        }
                    }
                }
            }
        }
        i++;
    }
    if(estrela != 1)
        conj_est.K = *est + 1;
    i = 0;
}

/* ---------------------------------------------------------------------- */
//FUNCAO DE ORGANIZAR AS LISTAS
void organiza_listas(t_delta **cabeca, unsigned short int i, char a, unsigned short int f)
{

    t_delta *pl = *cabeca;
    t_delta *plant = NULL;

    while(pl != NULL)
    {
        plant = pl;
        pl = pl->prox;
    }

    pl = malloc(sizeof(t_delta));

    pl->ei = i; //Coleta o valor de 'i' e o coloca na lista dos Estados Iniciais.
    pl->le = malloc(sizeof(char));

    *pl->le = a; //Coleta o valor de 'a' e o coloca na lista de Leitura.
    pl->le[1] = '\0';

    pl->ef = f;  //Coleta o valor de 'f' e o coloca na lista dos Estados Finas.
    pl->prox = NULL;

    if(plant != NULL)
        plant->prox = pl;

    else
        *cabeca = pl;
    return;
}

/* ---------------------------------------------------------------------- */


void montar_estrela(t_quintupla *quint, char c, unsigned short int *est)
{
    t_quintupla *list_quint = quint;
    unsigned short int aux;
    char E = 'E';

    aux = *est; // Auxiliar para salvar o estado que vai fazer o loop


    organiza_listas(&list_quint->D, *est, E, *est + 1);
    *est += 1;
    organiza_listas(&list_quint->D, *est, c, *est + 1);
    *est += 1;
    montar_loop(list_quint, aux, *est);
    *est += 1;

    return;
}
/* ---------------------------------------------------------------------- */
// FUNCAO MONTAR LOOP
void montar_loop(t_quintupla *quint, unsigned short int inicio, unsigned short int fim)
{
    t_quintupla *list_auto = quint;
    char c = 'E';
    //inserir_ef(&F, fim+1);
    conj_est.K = fim + 2;

    organiza_listas(&list_auto->D, fim, c, fim + 1);
    organiza_listas(&list_auto->D, fim, c, inicio + 1);
    organiza_listas(&list_auto->D, inicio, c, fim + 1);

    return;
}

/* ---------------------------------------------------------------------- */
// FUNCAO DELTA
void delta_er(t_delta *cabeca)
{

    t_delta *pl = cabeca;

    inserir_ef(&F, conj_est.K - 1);

    printf("#K\n");
    printf("%d\n", conj_est.K);
    printf("#A\n");
    printf("%c\n", alfabeto.A);
    printf("#S\n");
    printf("0\n");
    printf("#F\n");
    imprimir_ef();
    printf("#D\n");


    while(pl != NULL)
    {
        printf("%u %s %u\n", pl->ei, pl->le, pl->ef);
        //if(pl->prox != NULL){
        //printf("\n");
        //}
        pl = pl->prox;
    }

    return;
}

/* ---------------------------------------------------------------------- */
// Poem a informacoes de estados finais em uma lista

void inserir_ef(t_lef **cabeca, int x)
{

    t_lef *pl = *cabeca;
    t_lef *plant = NULL;
    while(pl != NULL)
    {
        plant = pl;
        pl = pl->prox;
    }
    pl = malloc(sizeof(t_lef));
    pl->f = x;
    pl->prox = NULL;
    if(plant != NULL)
        plant->prox = pl;
    else
        *cabeca = pl;
}

/* ---------------------------------------------------------------------- */
//os estados finais

void imprimir_ef()
{
    t_lef *pl = F;
    //t_lef *pl = cabeca;

    while(pl != NULL)
    {
        printf("%d", pl->f);
        if(pl->prox != NULL)
            printf(" ");
        pl = pl->prox;
    }
    printf("\n");
}

int buscar_ef(t_lef *cabeca, int x)
{

    t_lef *pl = cabeca;

    while(pl != NULL)
    {
        if(pl ->f == x)
            return 1;
        pl = pl->prox;
    }
    return 0;
}

/* ----------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This function initializes some operations before start
 * @details Details to be written
 * @return Void
 * @todo Need to implement it. Its empty now.
 * @author Ruben Carlo Benante
 * @version 20160520.000202
 * @date 2016-05-20
 *
 */
/* ------------------------------------------------------------------------ */
//void automax_init(void)
//{
//    IFDEBUG("automax_init()");
//    /* initialization */
//    return;
//}

/* ---------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This function does bla bla bla
 * @details It works by doing first a bla, followed by two bla's, giving
 * bla bla bla
 *
 * @pre You need to call foo() before calling this function
 *
 * @param[in] i Input parameter that does bla
 * @param[out] o Parameter that outputs ble
 * @param[in,out] z The @a z variable is used as input and output
 *
 * @return The returned value @a r means rhit
 * @retval 0 Returned when bli
 * @retval 1 Error code: function returned blo
 *
 * @par Example
 * @code
 *    if(x==funcexample(i, o, z))
 *       printf("And that is it\n");
 * @endcode
 *
 * @warning   Be carefull with blu
 * @deprecated This function will be deactivated in version +33
 * @see help()
 * @see copyr()
 * @bug There is a bug with x greater than y
 * @todo Need to change its output format to conform POSIX
 * @note You can read more about it at <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @author Ruben Carlo Benante
 * @version 20160520.000202
 * @date 2016-05-20
 * @copyright Only if not the same as the whole file
 *
 */
/* ---------------------------------------------------------------------- */

/* ------------------------------------------------------------------ */
/* C config for Vim modeline                                          */
/* vi: set ai cin et ts=4 sw=4 tw=0 wm=0 fo=croqltn :                 */
/* Template by Dr. Beco <rcb at beco dot cc>  Version 20160614.152950 */

