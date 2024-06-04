/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 13-03-2022
 * Modification : 19-03-2022*/

#ifndef __ATR__
#define __ATR__

#define TAILLE_MAX 50

typedef struct noeudLexico{
    char lettre;
    struct noeudLexico *gauche, *fils, *droit;
} Noeud, *ATR;

ATR creer_ATR_vide();

void liberer_ATR(ATR * A);

int inserer_dans_ATR(ATR * A, char * mot);

void supprimer_dans_ATR(ATR * A, char * mot);

void afficher_ATR_aux(ATR A, char* buffer, int pos);

void afficher_ATR(ATR A);

int est_dans_ATR(ATR A, char* mot);

#endif