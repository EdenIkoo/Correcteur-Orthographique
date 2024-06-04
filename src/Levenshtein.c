/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 30-03-2022
 * Modification : 02-04-2022*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Levenshtein.h"

int Levenshtein(char * un, char * deux) {
    int i, j, len_un, len_deux, cmt;
    int ** distance;

    len_un = strlen(un);
    len_deux = strlen(deux);

    distance = (int **)malloc(sizeof(int*) * (len_un + 1));

    for (i = 0; i < len_un + 1; i++)
        distance[i] = (int *)malloc(sizeof(int) * (len_deux + 1));

    for (i = 0; i <= len_un; i++)
        distance[i][0] = i;

    for (j = 0; j <= len_deux; j++)
        distance[0][j] = j;

    for (i = 1; i <= len_un; i++){
        for (j = 1; j <= len_deux; j++){
            if (un[i-1] == deux[j-1])
                cmt = 0;
            else
                cmt = 1;

            distance[i][j] = min(min(distance[i-1][j] + 1, distance[i][j-1] + 1), distance[i-1][j-1] + cmt);
        }
    }
    return(distance[len_un][len_deux]);
}

void lev_dico_aux(ATR A, char* buffer, int pos, Liste* correction, char* m, int * dmin){
    int d; /*Distance de Levenshtein*/
    if (A){ /*Si noeud != NULL*/
        lev_dico_aux(A->gauche, buffer, pos, correction, m, dmin); /*On regarde à gauche*/
        buffer[pos] = A->lettre; /*On prend la lettre la plus à gauche*/

        if (A->lettre == '\0'){ /*Si fin de mot*/
            buffer[pos] = '\0'; /*On marque la fin dans le mot*/

            d = Levenshtein(m, buffer); /*Calcul de la distance de Levenshtein*/
            if (d <= *dmin){ /*Si résultat au plus égal au min actuel*/
                if (d < *dmin){ /*Si résultat inférieur au min actuel*/
                    *dmin = d; /*Nouveau minimum*/
                    liberer_Liste(correction); /*Libération de la liste des corrections*/
                }
                inserer_en_tete(correction, buffer); /*Insertiond dans la liste des corrections*/
            }

            if(A->fils){ /*Si mot après*/
                buffer[pos] = A->fils->lettre; /*On remplace la fin de mot par la lettre*/
                pos -= 1; /*On se replace dans le mot*/
            }
        }

        lev_dico_aux(A->fils, buffer, pos + 1, correction, m, dmin); /*Puis on regarde en dessous*/

        lev_dico_aux(A->droit, buffer, pos, correction, m, dmin); /*Puis on regarde à droite*/
    }
}

void lev_dico(ATR A, char* m, Liste* correction, int * dmin){
    char buffer[TAILLE_MAX];
    lev_dico_aux(A, buffer, 0, correction, m, dmin);
}
