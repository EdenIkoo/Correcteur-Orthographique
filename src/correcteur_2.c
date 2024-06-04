/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 21-03-2022
 * Modification : 24-04-2022*/

/*Algorithme de la partie 3*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Listes.h"
#include "Levenshtein.h"
#include "ArbreBK.h"

int main(int argc, char * argv[]) {

    /*Mesure du temps du programme*/
    clock_t temps_initial, temps_final;
    float temps;

    FILE* dico; /*Dictionnaire*/
    FILE* a_corriger; /*Texte à corriger*/
    char m[TAILLE_MAX]; /*Pour lire les fichiers mot par mot*/
    ArbreBK a = NULL; /*Arbre du dictionnaire*/
    Liste erreurs = NULL; /*Liste des erreurs*/
    Liste correction = NULL; /*Liste des propositions de corrections*/

    temps_initial = clock(); /*Début de la mesure*/

    /*argv[2] = dictionnaire*/
    dico = fopen(argv[2], "r");

    if(dico == NULL){
        fprintf(stderr,"Erreur d'ouverture du fichier 1.\n");
        exit(-1);
    }

    /*Création du dictionnaire*/
    a = creer_ArbreBK(dico);
    fclose(dico);

    /*argv[1] = texte à corriger*/
    a_corriger = fopen(argv[1], "r");

    if(a_corriger == NULL){
        fprintf(stderr,"Erreur d'ouverture du fichier 2.\n");
        exit(-1);
    }

    /*Création de la liste des erreurs*/
    while(fscanf(a_corriger, "%s", m) != EOF) {
        int i;
        for(i = 0; i < strlen(m); i++) {
            m[i] = tolower(m[i]);
        }
        if (est_dans_Arbre_BK(a, m) == 0) {
            inserer_en_tete(&erreurs, m);
        }
    }
    fclose(a_corriger);

    for(; erreurs != NULL; erreurs = erreurs->suivant) { /*Parcours de la liste des erreurs*/

        correction = rechercher_dans_ArbreBK(a, erreurs->m); /*recherche des corrections*/

        /*Affichage des propositions de correction*/
        printf("Mot mal orthographié : %s\n", erreurs->m);
        printf("Proposition(s) : ");
        afficher_Liste(correction);

        /*Libération de la liste*/
        liberer_Liste(&correction);
    }

    /*Libération de l'arbre*/
    liberer_ArbreBK(&a);

    temps_final = clock(); /*Fin de la mesure*/

    temps = (temps_final - temps_initial); /*Calcul du temps*/

    printf("Temps d'éxécution : %f\n", temps);

    return 0;
}