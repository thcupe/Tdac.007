 /**************************************************************************
 *   pe6.c                                    Version 20190817.235856      *
 *                                                                         *
 *   Project Euler                                                         *
 *   Copyright (C) 2015-2019   Template by Ruben Carlo Benante             *
 *   Author: Thiago De Azevedo Cavendish                                   *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
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
 **************************************************************************/

/* ---------------------------------------------------------------------- */
/* includes */
#include "projecteuler.h"
#include "myeulerlib.h"

/* ---------------------------------------------------------------------- */
/* defines */
/* Project Euler Exercise Number */
/* #define PEN pe ## 6 */
#define SPEN "pe" "6"

/* ---------------------------------------------------------------------- */
/* prototypes */
void pe6(void); /* Proj. Euler problem #6 */

/* ---------------------------------------------------------------------- */
/* main function */
/* Do not change the main function. Use the void pe6(void) and
 * others you create here or in the myeulerlib.c and myeulerlib.h files
 */
int main(void)
{
    printf("Project Euler 20190817.233439, %s\n", SPEN);
//  help(); /* optional help message at start */
//  GRABsignals(); /* grab interruption signals */
    pe6(); /* Proj. Euler problem #6 */
//  LEGOsignals(); /* restore interruption signals */
    return EXIT_SUCCESS;
}

/* ---------------------------------------------------------------------- */
/* Proj. Euler problem #6 */
/* Problem description:
 *
 */

void pe6(void)
{  
   /* local variables */
   ulong r=0; /* answer */
   int x, soma_Quadrados, quadrado_Soma, dif;

   x = 1;
   soma_Quadrados = quadrado_Soma = dif = 0;

// os nUmeros x devem variar nessa faixa
   for (x = 1; x <= 100; x++)
   {
    soma_Quadrados += (x*x);
    quadrado_Soma += x;
   }
   quadrado_Soma = quadrado_Soma * quadrado_Soma;
   dif = quadrado_Soma - soma_Quadrados;

   r =  dif;
// printf("\n %d \n", dif);

    /* Put this command inside a loop to get previews when pressing CTRL-C */
    /* ctrlc_printf("%s: Trying now %u\n", __FUNCTION__, r); */
    /* Use to count minutes running: */
    /* if(minutes() >= 2) break; */

    printf("\n %s: %lu\n \n", __FUNCTION__, r); /* answer */
    return;
}

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20160612.142044      */

