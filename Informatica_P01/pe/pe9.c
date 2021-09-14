 /**************************************************************************
 *   pe9.c                                    Version 20190817.235856      *
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
/* #define PEN pe ## 9 */
#define SPEN "pe" "9"

/* ---------------------------------------------------------------------- */
/* prototypes */
void pe9(void); /* Proj. Euler problem #9 */

/* ---------------------------------------------------------------------- */
/* main function */
/* Do not change the main function. Use the void pe9(void) and
 * others you create here or in the myeulerlib.c and myeulerlib.h files
 */
int main(void)
{
    printf("Project Euler 20190817.233439, %s\n", SPEN);
//  help(); /* optional help message at start */
//  GRABsignals(); /* grab interruption signals */
    pe9(); /* Proj. Euler problem #9 */
//  LEGOsignals(); /* restore interruption signals */
    return EXIT_SUCCESS;
}

/* ---------------------------------------------------------------------- */
/* Proj. Euler problem #9 */
/* Problem description: Encontre o produto abc
 *
 */

void pe9(void)
{
   /* local variables */
   ulong r=0; /* answer */
   int a, b, c, sum, product, aQ, bQ, cQ;

   a = b = c = product = aQ = bQ = cQ = 0;
   sum = 1000;

   for (a = 1; a < (sum / 3); a++)
   {
     for (b = 2; b < (sum / 2); b++)
     {
       c = sum - b - a;//pois a + b + c = 1000(sum)
       aQ = a*a;
       bQ = b*b;
       cQ = c*c;

       if ((aQ + bQ) == cQ)
       {
         printf("\n %d %d %d \n", a, b, c);
         product = a * b * c;
         r = product;
         printf("\n %s: %lu\n", __FUNCTION__, r); /* answer */
       }
     }
   }

    /* Put this command inside a loop to get previews when pressing CTRL-C */
    /* ctrlc_printf("%s: Trying now %u\n", __FUNCTION__, r); */

    /* Use to count minutes running: */
    /* if(minutes() >= 2) break; */
    return;
}

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20160612.142044      */

