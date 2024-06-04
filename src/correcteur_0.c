/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 19-03-2022
 * Modification : 20-03-2022*/

/*Algorithme de la partie 1*/

#include <stdlib.h>
#include <stdio.h>
#include "ATR.h"
#include "Listes.h"

#define TAILLE_MAX 50

int main(int argc, char * argv[]){
    FILE* dico;
    FILE* a_corriger;
    char m_dico[TAILLE_MAX];
    char m[TAILLE_MAX];
    ATR a = NULL;
    Liste erreurs = NULL;

    /*argv[2] = dictionnaire*/
    dico = fopen(argv[2], "r");

    if(dico == NULL){
        fprintf(stderr,"Erreur d'ouverture du fichier 1.\n");
        exit(-1);
    }

    while(fscanf(dico, "%s", m_dico) != EOF){
        inserer_dans_ATR(&a, m_dico);
    }

    fclose(dico);

    /*argv[1] = texte à corriger*/
    a_corriger = fopen(argv[1], "r");

    if(a_corriger == NULL){
        fprintf(stderr,"Erreur d'ouverture du fichier 2.\n");
        exit(-1);
    }

    /*for chaque mot m présent dans a_corriger do*/
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

    /*return erreurs*/
    printf("Mot(s) mal orthographié(s) :\n");
    afficher_Liste(erreurs);

    /*libération de l'arbre*/
    liberer_ATR(&a);

    return 0;
}