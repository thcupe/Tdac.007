 /**************************************************************************
 *   pe3.c                                    Version 20190817.235856      *
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
/* #define PEN pe ## 3 */
#define SPEN "pe" "3"

/* ---------------------------------------------------------------------- */
/* prototypes */
void pe3(void); /* Proj. Euler problem #3 */

/* ---------------------------------------------------------------------- */
/* main function */
/* Do not change the main function. Use the void pe3(void) and
 * others you create here or in the myeulerlib.c and myeulerlib.h files
 */
int main(void)
{
    printf("Project Euler 20190817.233439, %s\n", SPEN);
    help(); /* optional help message at start */
    GRABsignals(); /* grab interruption signals */
    pe3(); /* Proj. Euler problem #3 */
    LEGOsignals(); /* restore interruption signals */
    return EXIT_SUCCESS;
}

/* ---------------------------------------------------------------------- */
/* Proj. Euler problem #3 */
/* Problem description:
 *
 */

void pe3(void)
{
     long long numb;
   int maxPrime, PrImpar;

   numb = 600851475143;
   maxPrime = 0;
   PrImpar = 3;

   //pois o menor nUmero primo impar eh 3
   while (numb % 2 == 0)
   {
           maxPrime = 2;
           numb /= 2;
   }
   while (numb != 1)
   {
           while (numb % PrImpar == 0)
           {
                 maxPrime = PrImpar;
                 numb /= PrImpar;

           }
           PrImpar += 2;

   }
  // printf("\n  %d\n", maxPrime);
    /* local variables */
    ulong r=maxPrime; /* answer */

    /* Put this command inside a loop to get previews when pressing CTRL-C */
    /* ctrlc_printf("%s: Trying now %u\n", __FUNCTION__, r); */

    /* Use to count minutes running: */
    /* if(minutes() >= 2) break; */

    printf("%s: %lu\n", __FUNCTION__, r); /* answer */
    return;
}

/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20160612.142044      */

