/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 18-04-2022
 * Modification : 23-04-2022*/

#include "Listes.h"
#include <stdio.h>

#ifndef __ArbreBK__
#define __ArbreBK__

typedef struct noeudBK {
    char * mot;
    int valeur;
    struct noeudBK * filsG;
    struct noeudBK * frereD;
} NoeudBK, * ArbreBK;

NoeudBK * allouer_noeud(char * mot, int distance);

int inserer_dans_ArbreBK(ArbreBK * A, char * mot);

void rechercher_dans_ArbreBK_aux(ArbreBK A, char * mot, Liste * corrections, int * seuil);

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot);

int est_dans_Arbre_BK(ArbreBK dico, char * mot);

ArbreBK creer_ArbreBK(FILE * dico);

void liberer_ArbreBK(ArbreBK * A);

void afficher_ArbreBK(ArbreBK A, int decalage);

#endif