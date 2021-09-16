/*****************************************************************************
 *   ex15.c                                    Version 20180714.101818       *
 *                                                                           *
 *   Brief description : Biblioteca pessoal                                  *
 *   Copyright (C) 2016-2018    by Ruben Carlo Benante                       *
 *****************************************************************************
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License.          *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************
 *   To contact the author, please write to:                                 *
 *   Ruben Carlo Benante                                                     *
 *   Email: rcb@beco.cc                                                      *
 *   Webpage: www.beco.cc                                                    *
 *   Phone: +55 (81) 3184-7555                                               *
 *****************************************************************************/

/* ------------------------------------------------------------------------- */
/**
 * @file ex15.c
 * @ingroup GroupUnique
 * @brief Brief description : Biblioteca pessoal
 * @details This program really do a nice job as a template, and template only!
 * @version 20160908.182830
 * @date 2016-09-08 // 30/08/2021
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
 *   $gcc ex15.c -o ex15.x -Wall
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
 *      $astlye -A1 -s4 -k3 -xj -SCNeUpv ex15.c
 */

/* ------------------------------------------------------------------------- */
/* includes at ex15.h */

#include "ex15.h" /* To be created for this template if needed */

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief description: Biblioteca pessoal
 * @details Ladies and Gentleman...

 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 *
 */
int main(int argc, char *argv[])
{
    int opt; /* return from getopt() */
    int kpress; /* tecla pressionada no laCo principal */
    wins_t win; /* info para ncurses */
    livro_t bib;

    IFDEBUG("Starting optarg loop...");

    /* getopt() configured options:
     *        -h  Help
     *        -V  version
     */
    opterr = 0;
    while((opt = getopt(argc, argv, "hV")) != EOF)
        switch(opt)
        {
            case 'h':
                Help();
                break;
            case 'V':
                copyr();
                break;
            case '?':
            default:
                printf("Type\n\t$man %s\nor\n\t$%s -h\nfor Help.\n\n", argv[0], argv[0]);
                return EXIT_FAILURE;
        }

    /* inicializando o ncurses */
    ex15_init(&win);

    /* laCo principal */
    
    kpress=getch();
    pkeyf(&win,&bib,kpress);

    //bomb(win, "\n", 0, NULL);
}

/* ------------------------------------------------------------------------- */
/* Navegação no programa */
void pkeyf(wins_t *pw, livro_t *aw, int kpress)
{
    flushinp();
   // int kpress;

   // kpress = getch();
    if(kpress == 'q')
        bomb(*pw, "\n", 0, NULL);
    if(kpress == KEY_F(1) || kpress == '1')
    {
       pw->wi=0;
       pHelp(pw,aw);
    }

    if(kpress == 's')
       msgstatus(*pw, "Status: Oi na linha de status ", STOK);

    if(kpress == KEY_F(5) || kpress == '5')
       pw->wi = (pw->wi+1)%NWIN;
    
    if(kpress == KEY_F(6) || kpress == '6')
    {
       if(pw->wi != 0){pw->wi = (pw->wi-1)%NWIN;}
       else{pw->wi=NWIN-1;}
    }
    if(kpress == KEY_F(7) || kpress == '7')
    {
       pw->wi=5;
       pabout(pw,aw);
    }

    switch(pw->wi)
    {
        case 0: /* Tela de Help */
            pHelp(pw,aw);
            break;
        case 1: /* Adicionar livro */
            padd(pw,aw);
            break;
        case 2: /* Pesquisar livro */ 
            psearch(pw,aw);           
            break;   
        case 3: /* Editar livro */ 
            pchange(pw,aw);           
            break;
        case 4: /* Deletar livro */ 
            pdel(pw,aw);           
            break;
        case 5: /* Sobre */ 
            pabout(pw,aw);           
            break;
        default:
            break;
    }
    
    napms(50);
    wrefresh(pw->w[pw->wi]);
}
/* ------------------------------------------------------------------------- */
/* Confere se a tela atual precisa de um clear */ // cabeCalho
void pheader(wins_t *pw)
{
    int c; /* coluna */
    int k=0; /*contador */

    c=ccentral(pw->cmax, TTITULO);
    
    if(pw->wi != pw->wo)
    { 
       pw->wo = pw->wi;
       wclear(pw->w[pw->wi]);
       box(pw->w[pw->wi], 0, 0);
    }
    mvwprintw(pw->w[pw->wi], 1, c-4, "%s", TTITULO);
    mvwhline(pw->w[pw->wi], 2, 1, '-', COLS-2); /* horizontal line */
    mvwprintw(pw->w[pw->wi], 3, 2, "%s", stela[pw->wi]);
    mvwhline(pw->w[pw->wi], 4, 1, '-', COLS-2); /* horizontal line */

    mvwhline(pw->w[pw->wi], STLINE-1, 1, '-', COLS-2); /* status horizontal line */ 

    c=4;
    wattron(pw->w[pw->wi],A_REVERSE);
    while(k<4)
    {
        mvwprintw(pw->w[pw->wi], STLINE-2, c-1, "%s", tfunction[k]); /* imprime as teclas de função */
        k++;
        c+=12;
    }
    c=COLS-48;
    while(k<8) 
    {
        mvwprintw(pw->w[pw->wi], STLINE-2, c, "%s", tfunction[k]); /* imprime as teclas de função */
        k++;
        c+=12;
    }

    wattroff(pw->w[pw->wi],A_REVERSE);
    wrefresh(pw->w[pw->wi]);
}

/* ------------------------------------------------------------------------- */
/* centraliza coluna */
int ccentral(int cl, char *msg)
{
    int sl; /* string lenght */

    sl=strlen(msg);
    return (cl - sl)/2;
}

/* ------------------------------------------------------------------------- */
/* Recolher dados a serem enviados para o file */
void pdados(wins_t *pw, livro_t *aw)
{
    int kpress;
    int tier; /* indica a mudança de linha */
    tier=0;

    mvwhline(pw->w[pw->wi], STLINE, 5, ' ', COLS-3); /* horizontal line */
    msgstatus(*pw, " Pressione a tecla para cima ou para baixo para se mover e enter para inserir dados na linha ",0);
    wrefresh(pw->w[pw->wi]);

    aw->titulo[0] = '\0'; /* limpa todas as strings, fazer função */
    aw->autor[0] = '\0';
    aw->editora[0] = '\0';
    aw->local[0] = '\0';
    aw->ano[0] = '\0';
    aw->ed[0] = '\0';
    aw->isbn[0] = '\0';

    while(1)
    {
        switch(tier)
        {
            case 0:
                napms(50);
                wmove(pw->w[pw->wi],6,10); /* move para o titulo */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n') /* permite inserir strings na linha atual */
                {
                    echo();
                    //aw->titulo[0] = '\0';
                    wmove(pw->w[pw->wi],6,10);
                    wgetnstr(pw->w[pw->wi],aw->titulo,SGRA-1);
                    flushinp(); /* limpa o buffer, apenas um teste */
                    noecho();
                }
                break;
            case 1:
                napms(50);
                wmove(pw->w[pw->wi],7,9); /* move para o autor */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n')
                {
                    echo();
                    //aw->autor[0] = '\0';
                    wmove(pw->w[pw->wi],7,9);
                    wgetnstr(pw->w[pw->wi],aw->autor,SGRA-1);
                    flushinp();
                    noecho();
                }
                break;
            case 2:
                napms(50);
                wmove(pw->w[pw->wi],8,11); /* move para a editora */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n')
                {
                    echo();
                    //aw->editora[0] = '\0';
                    wmove(pw->w[pw->wi],8,11);
                    wgetnstr(pw->w[pw->wi],aw->editora,SMED-1);
                    flushinp();
                    noecho();
                }
                break;
            case 3:
                napms(50);
                wmove(pw->w[pw->wi],6,COLS/2 -2); /* move para o local */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n')
                {
                    echo();
                    //aw->local[0] = '\0';
                    wmove(pw->w[pw->wi],6,COLS/2 -2);
                    wgetnstr(pw->w[pw->wi],aw->local,SMED-1);
                    flushinp();
                    noecho();
                }
                break;
            case 4:
                napms(50);
                wmove(pw->w[pw->wi],7,COLS/2 -4); /* move para o ano */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n')
                {
                    echo();
                   // aw->ano[0] = '\0';
                    wmove(pw->w[pw->wi],7,COLS/2 -4);
                    wgetnstr(pw->w[pw->wi],aw->ano,SPEQ-1);
                    flushinp();
                    noecho();
                }
                break;
            case 5:
                napms(50);
                wmove(pw->w[pw->wi],6,COLS-22); /* move para a edicao */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n')
                {
                    echo();
                    //aw->ed[0] = '\0';
                    wmove(pw->w[pw->wi],6,COLS-22);
                    wgetnstr(pw->w[pw->wi],aw->ed,SPEQ-1);
                    flushinp();
                    noecho();
                }
                break;
            case 6:
                napms(50);
                wmove(pw->w[pw->wi],7,COLS-24); /* move para o isbn */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n')
                {
                    echo();
                    //aw->isbn[0] = '\0';
                    wmove(pw->w[pw->wi],7,COLS-24);
                    wgetnstr(pw->w[pw->wi],aw->isbn,SISBN-1);
                    flushinp();
                    noecho();
                }
                break;
            case 7:
                napms(50);
                wmove(pw->w[pw->wi],8,COLS-22); /* move para o codigo */
                wrefresh(pw->w[pw->wi]);
                kpress=getch();
                if(kpress=='\n')
                {
                    echo();
                    //aw->isbn[0] = '\0';
                    wmove(pw->w[pw->wi],8,COLS-22);
                    wscanw(pw->w[pw->wi],"%d",&(aw->cod));
                    flushinp();
                    noecho();
                }
                break;
            default:
                break;
        }
        switch(kpress)
        {
            case KEY_DOWN: /* muda para a linha de baixo */
                tier++;
                if(pw->wi == 1 || pw->wi == 3)
                {
                    if(tier > 6)
                       tier=0;
                }
                if(pw->wi == 2)
                {
                    if(tier >7)
                       tier=0;
                }
                break; 
            case KEY_UP:   /* muda para a linha de cima */
                tier--;
                if(pw->wi == 1 || pw->wi ==3)
                {
                    if(tier < 0)
                       tier=6;
                }
                if(pw->wi == 2)
                {
                    if(tier < 0)
                        tier=7;
                }
                break;
        }
        
     if(kpress==KEY_F(4)) /* sai sem salvar. obs: (com erro, não capta o char caso eu não já tenha escrito nada */
     {
        mvwhline(pw->w[pw->wi], STLINE, 2, ' ', COLS-2); /* limpa a linha de status */
        
        msgstatus(*pw," Você tem certeza que quer sair sem salvar os dados ? eles podem ser perdidos: Y/N ",0);

        flushinp();
        kpress=getch();

        //if(pw->wi==1)
        //{
            if(kpress=='y' || kpress=='Y') /* limpeza de tela */
            {
               mvwhline(pw->w[pw->wi], STLINE, 5, ' ', COLS-3); /* horizontal line */
               //mvwhline(pw->w[pw->wi], STLINE, 1, ' ', COLS-2);
               msgstatus(*pw," Descartando dados ... ",0);
               wrefresh(pw->w[pw->wi]);  
               napms(2000);
               flushinp();
               wclear(pw->w[pw->wi]); 
               box(pw->w[pw->wi],0,0);
               padd(pw,aw);
               wrefresh(pw->w[pw->wi]);  
               break;
            }
       // }
     } 
     if(kpress==KEY_F(3)) /* sai e salva os dados */
     {
        mvwhline(pw->w[pw->wi], STLINE, 2, ' ', COLS-2);
        if(pw->wi==1)
        {
            msgstatus(*pw," Você tem certeza que quer salvar os dados ? Y/N ",0);
            flushinp();
            kpress=getch();

            if(kpress=='y' || kpress=='Y')
            {
               mvwhline(pw->w[pw->wi], STLINE, 5, ' ', COLS-3); /* horizontal line */
               msgstatus(*pw," Salvando ... ",0);
               wrefresh(pw->w[pw->wi]);  
               aw->cod = pcount(pw);
               pbiblio(pw,aw);
               napms(2000);
               flushinp();
               wclear(pw->w[pw->wi]); 
               box(pw->w[pw->wi],0,0);
               padd(pw,aw);
               wrefresh(pw->w[pw->wi]);  
               break;
            }
          }
          if(pw->wi == 2)
          {
            for(int k=11;k<30;k+=2) /* limpa a tela de baixo */
            {
               mvwhline(pw->w[pw->wi], k, 2, ' ', COLS-3); /* horizontal line */
            
            }
            msgstatus(*pw," Pesquisando ... ",0);
            napms(1750);
            mvwhline(pw->w[pw->wi], STLINE, 2, ' ', COLS-2);
            kpesquisa(pw,aw);
            box(pw->w[pw->wi],0,0);
            wrefresh(pw->w[pw->wi]);
            break;

          }
          if(pw->wi ==3)
          { 
              kpesquisa(pw,aw);
              aw->cod=pcount(pw);
              pbiblio(pw,aw);
              pconcatenar();
              break;
          }
        }
    }
    wrefresh(pw->w[pw->wi]);  
}

/* ------------------------------------------------------------------------- */
/* Envia dados para o file */
void pbiblio(wins_t *pw, livro_t *aw)
{
    if(pw->wi==1)
    {
        biblio= fopen("livros.txt","a");
        fprintf(biblio,"%i;", aw->cod);
        fprintf(biblio,"%s;", aw->titulo);
        fprintf(biblio,"%s;", aw->autor);
        fprintf(biblio,"%s;", aw->editora);
        fprintf(biblio,"%s;", aw->local);
        fprintf(biblio,"%s;", aw->ano);
        fprintf(biblio,"%s;", aw->ed);
        fprintf(biblio,"%s;\n", aw->isbn);
        fclose(biblio); 
    }
    if(pw->wi==3)
    {
        pchange1= fopen("pchange1.txt","a");
        fprintf(biblio,"%i;", aw->cod);
        fprintf(biblio,"%s;", aw->titulo);
        fprintf(biblio,"%s;", aw->autor);
        fprintf(biblio,"%s;", aw->editora);
        fprintf(biblio,"%s;", aw->local);
        fprintf(biblio,"%s;", aw->ano);
        fprintf(biblio,"%s;", aw->ed);
        fprintf(biblio,"%s;\n", aw->isbn);
        fclose(pchange1);
    
    }
    if(pw->wi==4)
    {
        pchange1 = fopen("pchange1.txt","a");
        fprintf(biblio,"D;");
        fprintf(biblio,";");
        fprintf(biblio,";");
        fprintf(biblio,";");
        fprintf(biblio,";");
        fprintf(biblio,";");
        fprintf(biblio,";");
        fprintf(biblio,";\n");
        fclose(pchange1);
    }
} 
/* ------------------------------------------------------------------------- */
/* Numero de contagem dos livros */
int pcount(wins_t *pw)
{
    char b[625];
    int k;
    k=1;
   
    if(pw->wi==1)
    {
        biblio = fopen("livros.txt","r+");
        if(biblio == NULL)
        {
            return k;
        }

        while((fgets(b,625,biblio)) !=NULL)
        {
            k++;
        }
        fclose(biblio);
    }
    if(pw->wi==3)
    {
        pchange1 = fopen("pchange1.txt","r+");
        if(pchange1 == NULL)
        {
            return k;
        }
        while((fgets(b,625,pchange1)) != NULL)
        {
            k++;
        }
        fclose(pchange1);
    }
    return k;   
}

/* -------------------------------------------------------------------------- */
/* Procura a palavra chave na biblioteca */
void kpesquisa(wins_t *pw, livro_t *aw)
{
    char msg[625];
    char msg2[]="D;;;;;;;";
    int k;
    char frase[625]="\0";
    char frase2[625]="\0";
    int flag = 0;
    biblio = fopen("livros.txt","r"); /* Abre o arquivo para leitura */
    if(pw->wi ==2)
    {
        k = pcondicao(aw);
        patribuir(aw,k,msg);
    

        pesquisa = fopen("apoio.txt","w+"); /* Limpa tudo que estiver dentro e permite inserir dados */
        altera=fopen("altera.txt","w+");
        while((fgets(frase,625,biblio)) != NULL) /* Le todas as linhas do arquivo */
        {
            if((strstr(frase,msg)) != NULL) /* Verifica se alguma possui a palavra-chave pesquisada */
            {
                if((strstr(frase,msg2) == NULL))
                {
                    fputs(frase,pesquisa); /* Coloca a string no arquivo de apoio */
                    flag++;
                }
                if(flag == 1)
                {
                    fputs(frase,altera);
                }
            }
        }
        if(flag==0)
        {
            mvwprintw(pw->w[pw->wi],12,5,"Não encontrado");
            if(altera != NULL)
            {
                fclose(altera);
                remove("altera.txt");
            }
            if(pesquisa != NULL)
            {
                fclose(pesquisa);
                remove("apoio.txt");
            }
        }
        if(flag > 1)
        {
            fclose(pesquisa);
            remove("altera.txt");
            pread(pw); /* inicializa função de leitura do arquivo de apoio */
        }
        if(flag == 1)
        {
            fclose(pesquisa);
            fclose(altera);
            pread(pw); /* inicializa função de leitura do arquivo de apoio */
            
        }
    }
    if(pw->wi == 3 || pw->wi == 4)
    {
        msg[0]='\0';
        frase[0]='\0';
        altera = fopen("altera.txt","r");
        if(altera != NULL)
        {
            if(fgets(frase,625,altera) != NULL)
            {
                strcat(msg,frase);
            }
        }
        fclose(altera);
        pchange1 = fopen("pchange1.txt","w+");
        
        while((fgets(frase2,625,biblio)) != NULL)
        {
            if(pchange2 != NULL)
            {
                fputs(frase2,pchange2);
                frase2[0]='\0';
            }
            if((strstr(frase2,msg))!= NULL)
            {
                fclose(pchange1);
                pchange2 = fopen("pchange2.txt","w+");
                frase2[0]='\0';
            }
            if(pchange1 != NULL)
            {
                fputs(frase2,pchange1);
            }
        }
        fclose(pchange2);
    }
    
    fclose(biblio);
}
/* -------------------------------------------------------------------------- */
/* concatena dois files */
void pconcatenar()
{
    char frase[625];
    char frase2[625];

    biblio = fopen("livros.txt","w+");
    pchange1=fopen("pchange1.txt","a");
    pchange2=fopen("pchange2.txt","r");
    while((fgets(frase,625,pchange2)) != NULL)
    {
        fputs(frase,pchange1);
    }
    fclose(pchange1);
    fclose(pchange2);
    pchange1 =  fopen("pchange1.txt","r");
    while((fgets(frase2,625,pchange1)) != NULL)
    {
        fputs(frase2,biblio);
    }
    fclose(biblio);
    fclose(pchange1);
    
    if(pchange1 != NULL)
    {
        remove("pchange1.txt");
    }
    if(pchange2 != NULL)
    {
        remove("pchange2.txt");
    }
    if(altera != NULL)
    {
        remove("altera.txt");
    }
}
/* -------------------------------------------------------------------------- */
/* Le e mostra na tela o que tem em um arquivo */
void pread(wins_t *pw)
{
    char frase[625];
    int j = 11;
    pesquisa = fopen("apoio.txt","r"); /* Abre o arquivo no modo leitura */

    while((fgets(frase,625,pesquisa)) != NULL) /* Capta todas as linhas do arquivo */
    {
        mvwprintw(pw->w[pw->wi],j,2,"%s",frase); /* Coloca na tela as linhas */
        j+=2;
    }

    fclose(pesquisa);
    remove("apoio.txt"); /* Remove o arquivo de apoio do seu diretorio */
}
/* -------------------------------------------------------------------------- */
/* Verifica se foi inserido uma string ou todas */
int pcondicao(livro_t *aw)
{
    int k=0;
    
    if(aw->titulo[0] != '\0')
    {
        k++;
    }
    if(aw->autor[0] != '\0')
    {
        k++;
    }
    if(aw->editora[0] != '\0')
    {
        k++;
    }
    if(aw->local[0] != '\0')
    {
        k++;
    }
    if(aw->ano[0] != '\0')
    {
        k++;
    }
    if(aw->ed[0] != '\0')
    {
        k++;
    }
    if(aw->isbn[0] != '\0')
    {
        k++;
    }
    return k;
}
/* -------------------------------------------------------------------------- */
void patribuir(livro_t *aw, int k, char *msg)
{
    if(k <7)
    {
        if(aw->titulo[0] != '\0')
        {
            strcpy(msg,aw->titulo);
        }
        if(aw->autor[0] != '\0')
        {
            strcpy(msg,aw->autor);
        }
        if(aw->editora[0] != '\0')
        {
            strcpy(msg,aw->editora);
        }
        if(aw->local[0] != '\0')
        {
            strcpy(msg,aw->local);
        }
        if(aw->ano[0] != '\0')
        {
            strcpy(msg,aw->ano);
        }
        if(aw->ed[0] != '\0')
        {
            strcpy(msg,aw->ed);
        }
        if(aw->isbn[0] != '\0')
        {
            strcpy(msg,aw->isbn);
        }
    }
    if(k==7)
    {
        if(aw->titulo[0] != '\0')
        {
            strcat(aw->titulo,";");
            strcat(msg,aw->titulo);
        }
        if(aw->autor[0] != '\0')
        {
            strcat(aw->autor,";");
            strcat(msg,aw->autor);
        }
        if(aw->editora[0] != '\0')
        {
            strcat(aw->editora,";");
            strcat(msg,aw->editora);
        }
        if(aw->local[0] != '\0')
        {
            strcat(aw->local,";");
            strcat(msg,aw->local);
        }
        if(aw->ano[0] != '\0')
        {
            strcat(aw->ano,";");
            strcat(msg,aw->ano);
        }
        if(aw->ed[0] != '\0')
        {
            strcat(aw->ed,";");
            strcat(msg,aw->ed);
        }
        if(aw->isbn[0] != '\0')
        {
            strcat(aw->isbn,";");
            strcat(msg,aw->isbn);
        }
    }
    
}
void pdividestring(wins_t *pw)
{

    char a[625]= "\0";
    char b[625]= "\0";
    int k =0;
    char *token = "\0";

    altera = fopen("altera.txt","r");
    if(altera != NULL)
    {
        while(fgets(a,625,altera) != NULL)
        {
            strcat(b,a);
        }
        fclose(altera);
        token = strtok(b,";");

        while(token != NULL)
        {
            switch(k)
            {
                case 0:
                    if(pw->wi == 4)
                        mvwprintw(pw->w[pw->wi],7,10,"%s",token);
                    break;
                case 1:
                    if(pw->wi==3)
                        mvwprintw(pw->w[pw->wi],12,10,"%s",token);
                    if(pw->wi==4)
                        mvwprintw(pw->w[pw->wi],8,10,"%s",token);
                    break;
                case 2:
                    if(pw->wi==3)
                        mvwprintw(pw->w[pw->wi],13,9,"%s",token);
                    if(pw->wi==4)
                        mvwprintw(pw->w[pw->wi],9,9,"%s",token);
                    break;
                case 3:
                    if(pw->wi==3)
                        mvwprintw(pw->w[pw->wi],14,11,"%s",token);
                    if(pw->wi==4)
                        mvwprintw(pw->w[pw->wi],10,11,"%s",token);
                    break;
                case 4:
                    if(pw->wi==3)
                        mvwprintw(pw->w[pw->wi],15,9,"%s",token);
                    if(pw->wi==4)
                        mvwprintw(pw->w[pw->wi],11,9,"%s",token);
                    break;
                case 5:
                    if(pw->wi==3)
                        mvwprintw(pw->w[pw->wi],16,7,"%s",token);
                    if(pw->wi==4)
                        mvwprintw(pw->w[pw->wi],12,7,"%s",token);
                    break;
                case 6:
                    if(pw->wi==3)
                        mvwprintw(pw->w[pw->wi],17,10,"%s",token);
                    if(pw->wi==4)
                        mvwprintw(pw->w[pw->wi],13,10,"%s",token);
                    break;
                case 7:
                    if(pw->wi==3)
                        mvwprintw(pw->w[pw->wi],18,8,"%s",token);
                    if(pw->wi==4)
                        mvwprintw(pw->w[pw->wi],14,8,"%s",token);
                    break;
                default:
                    break;
            }
            wrefresh(pw->w[pw->wi]);
            k++;
            token = strtok(NULL,";");
        }
    
       }
}

/* -------------------------------------------------------------------------- */
                              // Telas
/* -------------------------------------------------------------------------- */

/* imprime Tela 00: Help */
void pHelp(wins_t *pw, livro_t *aw)
{
    IFDEBUG("pHelp()");
    
    pheader(pw);
    box(pw->w[pw->wi], 0, 0);
    int kpress;
    int c; /* Coluna */ //teste
    c=ccentral(pw->cmax, Tmsg); //teste

    mvwprintw(pw->w[pw->wi], 5, c-2, " == Teclas de Funcao == ");

    mvwprintw(pw->w[pw->wi], 7, 2, "<F1> ou <1>  : para esta tela de ajuda.");
    mvwprintw(pw->w[pw->wi], 8, 2, "<F2> ou <L>  : para descartar suas alteracoes.");
    mvwprintw(pw->w[pw->wi], 9, 2, "<F3>         : para salvar suas alteracoes.");
    mvwprintw(pw->w[pw->wi], 10, 2, "<F4>         : para sair do programa, apos a confirmacao.");
    mvwprintw(pw->w[pw->wi], 11, 2, "<q>          : para sair do programa, imediatamente.");
    mvwprintw(pw->w[pw->wi], 12, 2, "<F5 e <F6>   : para navegar pelas telas disponiveis.");
    mvwprintw(pw->w[pw->wi], 13, 2, "<F7> ou <7>  : ir para a tela de about.");
    mvwprintw(pw->w[pw->wi], 14, 2, "<F8>         : ainda nao definido.");

    mvwprintw(pw->w[pw->wi], 15, c-2, " == Tela de Selecao == ");
    mvwprintw(pw->w[pw->wi], 16, 2, "<UP>         : sobe para o nome anterior.");
    mvwprintw(pw->w[pw->wi], 17, 2, "<DOWN>       : desce para o nome seguinte.");
    mvwprintw(pw->w[pw->wi], 18, 2, "<RIGHT>      : avanca 1 espaco para a direita.");
    mvwprintw(pw->w[pw->wi], 19, 2, "<LEFT>       : avanca 1 espaco para a esquerda.");
    wrefresh(pw->w[pw->wi]);

    kpress=getch();
    pkeyf(pw,aw,kpress);
}

/* ------------------------------------------------------------------------- */
/* Tela 01: Adicionar livro */
void padd(wins_t *pw, livro_t *aw)
{
    int kpress;

    IFDEBUG("padd()");

    pheader(pw);
 // int c; /* coluna */ //código teste
 // c=ccentral(pw->cmax, Tmsg); //código teste

    /* Imprimir tela toda */
    mvwprintw(pw->w[pw->wi], 5, 2, "Campos obrigatorios ");
    mvwprintw(pw->w[pw->wi], 6, 2, "Titulo:");
    mvwprintw(pw->w[pw->wi], 7, 2, "Autor:");
    mvwprintw(pw->w[pw->wi], 8, 2, "Editora:");
    mvwprintw(pw->w[pw->wi], 6, COLS/2 -9, "Local:");
    mvwprintw(pw->w[pw->wi], 7, COLS/2 -9, "Ano:");

    mvwprintw(pw->w[pw->wi], 5, COLS-30, "Campos opcionais ");
    mvwprintw(pw->w[pw->wi], 6, COLS-30, "Edicao:");
    mvwprintw(pw->w[pw->wi], 7, COLS-30, "ISBN:");
    
 
    mvwhline(pw->w[pw->wi], 9, 1, '_', COLS-2); /* Divisão horizontal de tela */

    wrefresh(pw->w[pw->wi]);
    msgstatus(*pw," Pressione a tecla tab para inserir dados ",0);
    wrefresh(pw->w[pw->wi]);
    flushinp();
    kpress=getch(); // tentando implementar kpress no pkeyf e mudando wgetch pra getch //

    if(kpress == '\t')
    {
         mvwprintw(pw->w[pw->wi], 21, 28, "Caso tenha problemas para sair do programa, insira qualquer coisa e aperte F4 e Y ");
        //msgstatus(*pw, " Pressione a tecla para cima ou para baixo para se mover e enter para inserir dados na linha ",0);
        //wrefresh(pw->w[pw->wi]);
        pdados(pw,aw); // inicia a função de coletar dados /
        wrefresh(pw->w[pw->wi]);
        flushinp();
    } 
    //flushinp();
    pkeyf(pw,aw,kpress);
}

/* ------------------------------------------------------------------------- */
/* Tela 02: Pesquisar livro */
  void psearch(wins_t *pw, livro_t *aw)
{
    IFDEBUG("psearch()");

    pheader(pw);
    //char titu[200]="\0";
    //char frase[625]="\0";
    int kpress;
 // int c; /* coluna */ //código teste
 // c=ccentral(pw->cmax, Tmsg); //código teste

    /* imprimir a tela inteira */
    mvwprintw(pw->w[pw->wi], 5, 2, "Preencha total ou parcialmente um ou mais campos"); 
    mvwprintw(pw->w[pw->wi], 8, COLS-30, "Codigo:");
    mvwprintw(pw->w[pw->wi], 6, 2, "Titulo:");
    mvwprintw(pw->w[pw->wi], 7, 2, "Autor:");
    mvwprintw(pw->w[pw->wi], 8, 2, "Editora:");
    mvwprintw(pw->w[pw->wi], 6, COLS/2 -9, "Local:");
    mvwprintw(pw->w[pw->wi], 7, COLS/2 -9, "Ano:");
    mvwprintw(pw->w[pw->wi], 6, COLS-30, "Edicao:");
    mvwprintw(pw->w[pw->wi], 7, COLS-30, "ISBN:");

  
    mvwhline(pw->w[pw->wi], 9, 1, '_', COLS-2); /* divisão horizontal de tela */
    /* mover cursor para titulo do livro */
 //   wrefresh(pw->w[pw->wi]);

    msgstatus(*pw, "                                                             ",0);
    msgstatus(*pw, "Pressione tab para pesquisar livros ",0);
    wrefresh(pw->w[pw->wi]);
    flushinp();
    kpress=getch();


    if(kpress=='\t') /* prototipo */
    {
        wclear(pw->w[pw->wi]); 
        box(pw->w[pw->wi],0,0);
        pheader(pw);
        mvwprintw(pw->w[pw->wi], 5, 2, "Preencha total ou parcialmente um ou mais campos"); 
        mvwprintw(pw->w[pw->wi], 8, COLS-30, "Codigo:");
        mvwprintw(pw->w[pw->wi], 6, 2, "Titulo:");
        mvwprintw(pw->w[pw->wi], 7, 2, "Autor:");
        mvwprintw(pw->w[pw->wi], 8, 2, "Editora:");
        mvwprintw(pw->w[pw->wi], 6, COLS/2 -9, "Local:");
        mvwprintw(pw->w[pw->wi], 7, COLS/2 -9, "Ano:");
        mvwprintw(pw->w[pw->wi], 6, COLS-30, "Edicao:");
        mvwprintw(pw->w[pw->wi], 7, COLS-30, "ISBN:");
  
        mvwhline(pw->w[pw->wi], 9, 1, '_', COLS-2); /* divisão horizontal de tela */

        mvwprintw(pw->w[pw->wi], LINES-5, COLS/2-26, "Pressione F3 para obter o resultado da sua pesquisa ");
        wrefresh(pw->w[pw->wi]);
        pdados(pw,aw);
        flushinp();
    }
    wrefresh(pw->w[pw->wi]);
    pkeyf(pw,aw,kpress);
}

/* ------------------------------------------------------------------------- */ 
/* Tela 03: Editar livro */ // teste
  void pchange(wins_t *pw, livro_t *aw)
{
    IFDEBUG("pchange()");
    pheader(pw);

    int kpress;

    mvwprintw(pw->w[pw->wi], 5, 2, "Dados alterados: ");
    mvwprintw(pw->w[pw->wi], 6, 2, "Titulo:");
    mvwprintw(pw->w[pw->wi], 7, 2, "Autor:");
    mvwprintw(pw->w[pw->wi], 8, 2, "Editora:");
    mvwprintw(pw->w[pw->wi], 6, COLS/2 -9, "Local:");
    mvwprintw(pw->w[pw->wi], 7, COLS/2 -9, "Ano:");
    mvwprintw(pw->w[pw->wi], 6, COLS-30, "Edicao:");
    mvwprintw(pw->w[pw->wi], 7, COLS-30, "ISBN:");

    mvwhline(pw->w[pw->wi], 9, 1, '_', COLS-2); /* divisão horizontal de tela */
    
    mvwprintw(pw->w[pw->wi], 10, 2, "Dados originais: ");
    mvwprintw(pw->w[pw->wi], 12, 2, "Titulo:");
    mvwprintw(pw->w[pw->wi], 13, 2, "Autor:");
    mvwprintw(pw->w[pw->wi], 14, 2, "Editora:");
    mvwprintw(pw->w[pw->wi], 15, 2, "Local:");
    mvwprintw(pw->w[pw->wi], 16, 2, "Ano:");
    mvwprintw(pw->w[pw->wi], 17, 2, "Edicao:");
    mvwprintw(pw->w[pw->wi], 18, 2, "ISBN:");

    wrefresh(pw->w[pw->wi]);
    if(altera != NULL)
    {
        pdividestring(pw);
    }

    msgstatus(*pw, "                                 ",0);
    msgstatus(*pw, "Pressione tab para editar livros ",0);
    flushinp();
    kpress=getch();

   if(kpress=='\t') /* prototipo */
   {

      mvwprintw(pw->w[pw->wi], 21, 33, "Pressione F3 para obter o resultado da sua pesquisa "); 
      
      pdados(pw,aw);
      flushinp();

   }
   wrefresh(pw->w[pw->wi]);    
   pkeyf(pw,aw,kpress);
}

/* ------------------------------------------------------------------------- */
/* Tela 04: Deletar livro */
  void pdel(wins_t *pw, livro_t *aw)
{

    IFDEBUG("pdel()");

    pheader(pw);
    int kpress;

  //  int c; /* Coluna */ //teste
   // c=ccentral(pw->cmax, Tmsg); //teste

    /* Imprimir tela toda */
    mvwprintw(pw->w[pw->wi], 5, 2, "Livro a ser deletado:");

    mvwprintw(pw->w[pw->wi], 7, 2, "Codigo:");
    mvwprintw(pw->w[pw->wi], 8, 2, "TItulo:");
    mvwprintw(pw->w[pw->wi], 9, 2, "Autor:");
    mvwprintw(pw->w[pw->wi], 10, 2, "Editora:");
    mvwprintw(pw->w[pw->wi], 11, 2, "Local:");
    mvwprintw(pw->w[pw->wi], 12, 2, "Ano:");
    mvwprintw(pw->w[pw->wi], 13, 2, "Edicao:");
    mvwprintw(pw->w[pw->wi], 14, 2, "ISBN:");

   // mvwhline(pw->w[pw->wi], 9, 1, '_', COLS-2); /* divisão horizontal de tela */

    char c[625];
    char d[625];
    d[0]='\0';
    wrefresh(pw->w[pw->wi]);
    if(altera != NULL)
    {
        pdividestring(pw);
    }
    if(altera != NULL)
    {
        altera = fopen("altera.txt","r");
        while(fgets(c,625,altera) != NULL)
        {
            strcat(d,c);
        }
        fclose(altera);
    }

    msgstatus(*pw, "                                 ",0);
    msgstatus(*pw, "Pressione F3 para excluir livro ",0);
    flushinp();
    kpress=getch();
    if(kpress == KEY_F(3))
    {
        if(altera != NULL)
        {
            if(pchange1 == NULL)
            {
                if(pchange2 == NULL)
                {
                   kpesquisa(pw,aw);
                   pbiblio(pw,aw);
                   pconcatenar();
                   mvwhline(pw->w[pw->wi], STLINE, 5, ' ', COLS-3); /* horizontal line */
                   msgstatus(*pw," Deletando livro ... ",0);
                   wrefresh(pw->w[pw->wi]);  
                   napms(2000);
                   flushinp();
                   wclear(pw->w[pw->wi]); 
                   box(pw->w[pw->wi],0,0);
                } 
            }
        }
    }
    wrefresh(pw->w[pw->wi]);
    pkeyf(pw,aw,kpress);
}

/* ------------------------------------------------------------------------- */
/* Tela 05: Sobre */
  void pabout(wins_t *pw, livro_t *aw)
{

    IFDEBUG("pabout()");

    pheader(pw);

    int kpress;
    
    int c; /* Coluna */ //teste
    c=ccentral(pw->cmax, VERSION); //teste
    c=ccentral(pw->cmax, Tmsg); //teste

    /* Imprimir tela toda */
    mvwprintw(pw->w[pw->wi], 5, c-1, "Version: %s", VERSION);

    mvwprintw(pw->w[pw->wi], 7, 2, "Universidade de Pernambuco (UPE)");
    mvwprintw(pw->w[pw->wi], 8, 2, "Escola Politecnica de Pernambuco (Poli)");
    mvwprintw(pw->w[pw->wi], 9, 2, "Semestre: 2020.2");
    mvwprintw(pw->w[pw->wi], 10, 2, "Disciplina: Informatica para controle e automacao");
    mvwprintw(pw->w[pw->wi], 11, 2, "Professor: Dr. Ruben Carlo Benante"); 
    
    mvwprintw(pw->w[pw->wi], 13, c-2, "Integrantes do grupo Maria:");
    mvwprintw(pw->w[pw->wi], 15, 2, "1. Thiago De Azevedo Cavendish");
    mvwprintw(pw->w[pw->wi], 16, 2, "2. Ulisses Mosart Sobrinho");
    mvwprintw(pw->w[pw->wi], 17, 2, "3. Mateus Simplicio De Barros");
    mvwprintw(pw->w[pw->wi], 18, 2, "4. Matheus Luiz Ferreira Dos Santos");
    mvwprintw(pw->w[pw->wi], 19, 2, "5. Bernardo Lima Milhomens Salomoni");
    mvwprintw(pw->w[pw->wi], 20, 2, "6. Filipe Mateus Figueiredo Silva");
    mvwprintw(pw->w[pw->wi], 21, 2, "7. Luiz Carlos Guedes Estelita Neto"); 

    wrefresh(pw->w[pw->wi]);

    kpress=getch();
    pkeyf(pw,aw,kpress);
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints Help information and exit
 * @details Prints Help information (usually called by opt -h)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 *
 */
void Help(void)
{
    IFDEBUG("Help()");
    printf("%s - %s\n", "ex15", "Brief description");
    printf("\nUsage: %s [-h|-v]\n", "ex15");
    printf("\nOptions:\n");
    printf("\t-h,  --Help\n\t\tShow this Help.\n");
    printf("\t-V,  --version\n\t\tShow version and copyright information.\n");

    printf("\nExit status:\n\t0 if ok.\n\t1 some error occurred.\n");
    printf("\nTodo:\n\tLong options not implemented yet.\n");
    printf("\nAuthor:\n\tWritten by %s <%s>\n\n", "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_FAILURE);
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief Prints version and copyright information and exit
 * @details Prints version and copyright information (usually called by opt -V)
 * @return Void
 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 *
 */
void copyr(void)
{
    IFDEBUG("copyr()");
    printf("%s - Version %s\n", "ex15", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>. This  is  free  software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. USE IT AS IT IS. The author takes no responsability to any damage this software may inflige in your data.\n\n", 2016, "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_FAILURE);
}

/* ------------------------------------------------------------------------- */
/* Imprime na linha de status */
int msgstatus(wins_t win, char *msg, int tipo)
{
    switch(tipo)
    {
        case STOK:
            mvwprintw(win.w[win.wi], STLINE, 5, "%s", msg);
            break;
        case STYESNO:
            mvwprintw(win.w[win.wi], STLINE, 5, "%s", msg);
            break;
        default:
            mvwprintw(win.w[win.wi], STLINE, 5, "status type undefined");
            break;
    }
    wrefresh(win.w[win.wi]);
    return 1;
}

/* ------------------------------------------------------------------------- */
/* Termina o programa graciosamente */
void bomb(wins_t win, char *msg, int status, FILE *f)
{
    IFDEBUG("bomb()");
    int i;
    if(altera != NULL)
    {
        remove("altera.txt");
    }
    if(pesquisa != NULL)
    {
        remove("apoio.txt");
    }
    if(pchange1 != NULL)
    {
        remove("pchange1.txt");
    }
    if(pchange2 != NULL)
    {
        remove("pchange2.txt");
    }
    if(f)
       fclose(f);

    for(i = 0; i < NWIN; i++)
        delwin(win.w[i]);

    endwin();
    fprintf(stderr, msg);

    exit(status);
}

/* ------------------------------------------------------------------------- */
/**
 * @ingroup GroupUnique
 * @brief This function initializes some operations before start
 * @details Details to be written in
 * multiple lines
 *
 * @return Void
 *
 * @author Ruben Carlo Benante
 * @version 20160908.182830
 * @date 2016-09-08
 * @copyright Use this tag only if not the same as the whole file
 *
 */
void ex15_init(wins_t *pw)
{
    IFDEBUG("ex15_init()");
    int i; /* indice */

    for(i = 0; i < NWIN; i++)
        pw->menu[i] = 0;

    pw->wi = 0; /* inicia na Tela de Help */
    pw->wo = 1; /* tela anterior a da mudanca */

    initscr(); /* inicializa ncurses */
    napms(10); /* aguarda initscr() */
    refresh(); /* inicializar tela */
    halfdelay(2); /* cbreak sem espera ocupada */
    noecho(); /* desliga eco de teclado */
    keypad(stdscr, TRUE); /* liga teclas de funcao */

    /* criar janelas */
    for(i = 0; i < NWIN; i++)
    {
        pw->w[i] = newwin(LINES, COLS, 0, 0);
        if(pw->w[i] == NULL)
        {
            for(--i; i >= 0; --i)
                delwin(pw->w[i]);
            endwin();
            fprintf(stderr, "Error: can't create windows\n");
            exit(EXIT_FAILURE);
        }
    }

    pw->lmax = LINES; /* qntd de linhas na tela */
    pw->cmax = COLS; /* qntd de colunas na tela */
    wclear(pw->w[pw->wi]);
    box(pw->w[pw->wi], 0, 0);

    return;
}

/* ------------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline    */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20180716.101436   */

