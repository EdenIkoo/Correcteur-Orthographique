/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 18-04-2022
 * Modification : 24-04-2022*/

#include <stdlib.h>
#include <string.h> 
#include "ArbreBK.h"
#include "Levenshtein.h"
#include "Listes.h"

NoeudBK * allouer_noeud(char * mot, int distance) {
    NoeudBK * n = (NoeudBK *) malloc(sizeof(NoeudBK));
    if(n != NULL){
        n->mot = (char *)malloc(sizeof(char) * (strlen(mot) + 1));
        if (n->mot == NULL)
            return NULL;
        strcpy(n->mot, mot);
        n->valeur = distance;
        n->filsG = NULL;
        n->frereD = NULL;
    }
    return n;
}

int inserer_dans_ArbreBK(ArbreBK * A, char * mot) {
    ArbreBK nouv, tmp, prev;
    int dist, dist_frere;

    if((*A) == NULL){ /*Arbre vide*/
        if((*A = allouer_noeud(mot, 0)) == NULL)
            return 0;
        return 1;
    }
    dist = Levenshtein((*A)->mot, mot);

    if((*A)->filsG == NULL){ /*Pas de fils gauche*/
        if((nouv = allouer_noeud(mot, dist)) == NULL)
            return 0;
        (*A)->filsG = nouv; /*insertion*/
        return 1;
    }
    if((*A)->filsG->valeur > dist){ /*Distance plus petite que le fg actuel*/
        if((nouv = allouer_noeud(mot, dist)) == NULL)
            return 0;
        nouv->frereD = (*A)->filsG; /*fG devient fD du nouveau noeud*/
        (*A)->filsG = nouv; /*insertion*/
        return 1;
    }
    if((*A)->filsG->valeur > dist){ /*Distance plus petite que le fg actuel*/
        if((nouv = allouer_noeud(mot, dist)) == NULL)
            return 0;
        nouv->frereD = (*A)->filsG; /*fG devient fD du nouveau noeud*/
        (*A)->filsG = nouv; /*insertion*/
        return 1;
    }
    if((*A)->filsG->valeur == dist){ /*Même distance*/
        inserer_dans_ArbreBK(&((*A)->filsG), mot);
        return 1;
    }

    prev = (*A)->filsG;
    tmp = (*A)->filsG->frereD;

    while (tmp != NULL) {
        dist_frere = tmp->valeur;
        if (dist_frere > dist) {
            if((nouv = allouer_noeud(mot, dist)) == NULL)
                return 0;
            nouv->frereD = tmp;
            prev->frereD = nouv;
            return 1;
        }
        if (dist_frere == dist) {
            inserer_dans_ArbreBK(&tmp, mot);
            return 1;
        }
        if (dist_frere < dist) {
            if (tmp->frereD != NULL) {
                prev = tmp;
                tmp = tmp->frereD;
            }
            else {
                if((nouv = allouer_noeud(mot, dist)) == NULL)
                    return 0;
                tmp->frereD = nouv;
                return 1;
            }
        }
    }
    if((nouv = allouer_noeud(mot, dist)) == NULL)
        return 0;
    (*A)->filsG->frereD = nouv;
    return 1;
}

void rechercher_dans_ArbreBK_aux(ArbreBK A, char * mot, Liste * corrections, int * seuil){
    int dist;
    int val;
    if (!A) /*Arbre vide*/
        return;

    dist = Levenshtein(A->mot, mot);

    if (dist == *seuil){
        inserer_en_tete(corrections, A->mot);
    }
    if (dist < *seuil){
        liberer_Liste(corrections);
        inserer_en_tete(corrections, A->mot);
        *seuil = dist;
    }
    if(A->filsG){
        val = A->filsG->valeur;
        if (abs(val - dist) <= *seuil)
            rechercher_dans_ArbreBK_aux(A->filsG, mot, corrections, seuil);
    }
    if(A->frereD){
        val = A->frereD->valeur;
        if (abs(val - dist) <= *seuil)
            rechercher_dans_ArbreBK_aux(A->frereD, mot, corrections, seuil);
    }
}

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot) {
    int seuil;
    Liste corrections = NULL; /*Création liste vide*/
    seuil = Levenshtein(A->mot, mot); /*Seuil = distance au premier mot de l'arbre*/
    inserer_en_tete(&corrections, A->mot); /*Insertion du 1er mot dans la liste*/
    rechercher_dans_ArbreBK_aux(A->filsG, mot, &corrections, &seuil);
    return corrections;
}

int est_dans_Arbre_BK(ArbreBK dico, char * mot) {
    if (!dico)
        return 0;

    if (strcmp(dico->mot, mot) == 0) {
        return 1;
    }
    if(dico->filsG)
        if (est_dans_Arbre_BK(dico->filsG, mot))
            return 1;

    return est_dans_Arbre_BK(dico->frereD, mot);
}

ArbreBK creer_ArbreBK(FILE * dico) {
    ArbreBK nouv = NULL;
    char m[50];
    while(fscanf(dico, "%s", m) != EOF){
        inserer_dans_ArbreBK(&nouv, m);
    }
    return nouv;
}

void liberer_ArbreBK(ArbreBK * A) {
    if((*A)->filsG != NULL)
        liberer_ArbreBK(&(*A)->filsG);
    if((*A)->frereD != NULL)
        liberer_ArbreBK(&(*A)->frereD);
    free(*A);
    *A = NULL;
}

void afficher_ArbreBK(ArbreBK A, int decalage) {
    int i;
    if (A->valeur == 0)
        printf("%s\n", A->mot);
    else {
        for (i = 1; i < decalage; i++)
            printf(("        "));
        printf("|--%d--> %s\n", A->valeur, A->mot);
    }

    if (A->filsG != NULL)
        afficher_ArbreBK(A->filsG, decalage + 1);
    if (A->frereD != NULL)
        afficher_ArbreBK(A->frereD, decalage);
}