/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 30-03-2022
 * Modification : 24-04-2022*/

/*Algorithme de la partie 2*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ATR.h"
#include "Listes.h"
#include "Levenshtein.h"

int main(int argc, char * argv[]){

    /*Mesure du temps du programme*/
    clock_t temps_initial, temps_final;
    float temps;

    FILE* dico; /*Dictionnaire*/
    FILE* a_corriger; /*Texte à corriger*/
    char m[TAILLE_MAX]; /*Pour lire les fichiers mot par mot*/
    ATR a = NULL; /*Arbre du dictionnaire*/
    Liste erreurs = NULL; /*Liste des erreurs*/
    Liste correction = NULL; /*Liste des propositions de corrections*/
    int dmin; /*Distance de Levenshtein minimale*/

    temps_initial = clock(); /*Début de la mesure*/

    /*argv[2] = dictionnaire*/
    dico = fopen(argv[2], "r");

    if(dico == NULL){
        fprintf(stderr,"Erreur d'ouverture du fichier 1.\n");
        exit(-1);
    }

    while(fscanf(dico, "%s", m) != EOF)
        inserer_dans_ATR(&a, m);
    fclose(dico);

    /*argv[1] = texte à corriger*/
    a_corriger = fopen(argv[1], "r");

    if(a_corriger == NULL){
        fprintf(stderr,"Erreur d'ouverture du fichier 2.\n");
        exit(-1);
    }

    /*For chaque mot m présent dans a_corriger do*/
    while(fscanf(a_corriger, "%s", m) != EOF){
        /*si m n'est pas dans dico*/
        if (est_dans_ATR(a, m) == 0){
            /*insérer m en tête de la liste chainée erreurs*/
            inserer_en_tete(&erreurs, m);
        }
        /*end if*/
    }
    /*end for*/
    fclose(a_corriger);

    for(; erreurs != NULL; erreurs = erreurs->suivant){ /*Parcours de la liste des erreurs*/

        /*Définition du minimum à la valeur maximum*/
        dmin = TAILLE_MAX; 

        /*Calcul des mots avec la distance de Lev min et insertion dans la liste correction*/
        lev_dico(a, erreurs->m, &correction, &dmin);

        /*Affichage des propositions de correction*/
        printf("Mot mal orthographié : %s\n", erreurs->m);
        printf("Proposition(s) :");
        afficher_Liste(correction);

        /*Libération de la liste*/
        liberer_Liste(&correction);
    }

    /*Libération de l'arbre*/
    liberer_ATR(&a);

    temps_final = clock(); /*Fin de la mesure*/

    temps = (temps_final - temps_initial); /*Calcul du temps*/

    printf("Temps d'éxécution : %f\n", temps);

    return 0;
}
