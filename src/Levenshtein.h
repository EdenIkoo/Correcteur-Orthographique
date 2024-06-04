/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 30-03-2022
 * Modification : 02-04-2022*/

#include "ATR.h"
#include "Listes.h"

#ifndef __Levenshtein__
#define __Levenshtein__

#define min(a, b) (a < b ? a : b)

int Levenshtein(char * un, char * deux);

void lev_dico(ATR A, char* m, Liste* correction, int * dmin);

void lev_dico_aux(ATR A, char* buffer, int pos, Liste* correction, char* m, int * dmin);

#endif
