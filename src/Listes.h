/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 13-03-2022
 * Modification : 16-03-2022*/

#ifndef __Listes__
#define __Listes__

typedef struct cellule {
    char *m;
    struct cellule * suivant;
} Cellule, *Liste;

Cellule * allouer_Cellule(char * mot);

int inserer_en_tete(Liste * L, char * mot);

void liberer_Liste(Liste * L);

void afficher_Liste(Liste L);

#endif
