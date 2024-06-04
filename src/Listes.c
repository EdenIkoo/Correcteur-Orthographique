/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 13-03-2022
 * Modification : 02-04-2022*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listes.h"

Cellule * allouer_Cellule(char * mot){
    Cellule * n = (Cellule *) malloc(sizeof(Cellule));
    if(n != NULL){
        n->m = (char *)malloc(sizeof(char) * (strlen(mot) + 1));
        if (n->m == NULL)
            return NULL;
        strcpy(n->m, mot);
        n->suivant = NULL;
    }
    return n;
}

int inserer_en_tete(Liste * L, char * mot){
    Liste tmp;
    tmp = allouer_Cellule(mot);
    if(tmp != NULL){
        tmp->suivant = *L;
        *L = tmp;
        return 1;
    }
    return 0;
}

void liberer_Liste(Liste * L){
    Liste * tmp = NULL;
    while(*L != NULL){
        tmp = L;
        *L = (*L)->suivant;
        free(*tmp);
        *tmp = NULL;
    }
    *L = NULL;
}

void afficher_Liste(Liste L){
    while (L != NULL) { 
        printf("%s, ", L->m);
        L = L ->suivant;
    }
    printf("\n");
}
