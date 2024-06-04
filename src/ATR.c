/* Auteur : LAURENT Maëva, MENLET Enzo
 * Creation : 13-03-2022
 * Modification : 20-03-2022*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "ATR.h"

ATR creer_ATR_vide(){
    Noeud * atr = (Noeud*)malloc(sizeof(Noeud));
    if (atr != NULL){
        atr->gauche = NULL;
        atr->fils = NULL;
        atr->droit = NULL;
    }
    return atr;
}

void liberer_ATR(ATR * A){
    if ((*A)->gauche != NULL)
        liberer_ATR(&((*A)->gauche));
    if ((*A)->fils != NULL)
        liberer_ATR(&((*A)->fils));
    if ((*A)->droit != NULL)
        liberer_ATR(&((*A)->droit));
    free(*A);
    *A = NULL;
}

int inserer_dans_ATR(ATR * A, char * mot){
    if (!(*A)){ /*Si noeud vide*/
        *A = creer_ATR_vide(); /*On crée le noeud*/
        (*A)->lettre = tolower(*mot);
    }
    if ((*A)->lettre == '\0') /*Si on rencontre une fin de mot*/
        inserer_dans_ATR(&((*A)->fils), mot); /*On passe à la suite*/

    else if ((*mot) < (*A)->lettre) /*Si mot avant dans l'alphabet*/
        inserer_dans_ATR(&((*A)->gauche), mot);

    else if ((*mot) > (*A)->lettre) /*Si mot après dans l'alphabet*/
        inserer_dans_ATR(&((*A)->droit), mot);

    else{ /*Si même lettre*/
        if (*(mot+1)) /*Si pas fin de mot*/
            inserer_dans_ATR(&((*A)->fils), mot+1); /*On passe à la suite*/

        else{ /*Si fin de mot, on crée un fils avec '\0'*/
            ATR tmp = (*A)->fils;
            (*A)->fils = creer_ATR_vide();
            (*A)->fils->lettre = '\0';
            (*A)->fils->fils = tmp;
            return 1;
        }
    }
    return 0;
}

void supprimer_dans_ATR(ATR * A, char * mot){
    if (!(*A)) /*Si noeud vide*/
        return;

    if ((*mot) < (*A)->lettre) /*Si mot avant dans l'alphabet*/
        supprimer_dans_ATR(&((*A)->gauche), mot);

    else if ((*mot) > (*A)->lettre) /*Si mot après dans l'alphabet*/
        supprimer_dans_ATR(&((*A)->droit), mot);

    else{
        if (*(mot+1)) /*Si pas fin de mot*/
            if((*A)->fils->lettre == '\0') /*Si on rencontre une fin de mot*/
                supprimer_dans_ATR(&((*A)->fils->fils), mot+1); /*On la saute*/
            else
                supprimer_dans_ATR(&((*A)->fils), mot+1); /*Sinon on passe à la suite*/

        else if ((*A)->fils->lettre == '\0'){ /*On s'assure que le mot est bien dans le dico*/
            ATR tmp;
            tmp = (*A);

            if ((*A)->fils->fils != NULL){ /*Si mot après le '\0'*/
                tmp = (*A)->fils;
                (*A)->fils = (*A)->fils->fils;
                free(tmp);
                tmp = NULL;
            }
            else{
                if ((*A)->gauche != NULL){ /*Si mot à gauche, on chaîne à gauche*/
                    (*A) = (*A)->gauche;
                    (*A)->droit = tmp->droit;
                }
                else if ((*A)->droit != NULL){ /*Si mot à droite, on chaîne à droite*/
                    (*A) = (*A)->droit;
                    (*A)->gauche = tmp->gauche;
                }
                free(tmp->fils);
                free(tmp);
                (*A)->fils = NULL;
                (*A) = NULL;
            }
        }
    }
}

void afficher_ATR_aux(ATR A, char* buffer, int pos){
    if (A){ /*Si noeud != NULL*/
        afficher_ATR_aux(A->gauche, buffer, pos); /*On regarde à gauche*/
        buffer[pos] = A->lettre; /*On prend la lettre la plus à gauche*/

        if (A->lettre == '\0'){ /*Si fin de mot*/
            buffer[pos] = '\0'; /*On marque la fin dans le mot*/
            printf("%s\n", buffer); /*On l'affiche*/
            if(A->fils){ /*Si mot après*/
                buffer[pos] = A->fils->lettre; /*On remplace la fin de mot par la lettre*/
                pos -= 1; /*On se replace dans le mot*/
            }
        }

        afficher_ATR_aux(A->fils, buffer, pos + 1); /*Puis on regarde en dessous*/

        afficher_ATR_aux(A->droit, buffer, pos); /*Puis on regarde à droite*/
    }
}

void afficher_ATR(ATR A){
    char buffer[TAILLE_MAX];
    afficher_ATR_aux(A, buffer, 0);
}

int est_dans_ATR(ATR A, char* mot){
    if (!A)
        return 0;

    if(A->lettre == '\0') /*Si on rencontre une fin de mot*/
        return est_dans_ATR(A->fils, mot); /*On passe à la suite*/
 
    if (tolower(*mot) < A->lettre) /*Si mot avant dans l'alphabet*/
        return est_dans_ATR(A->gauche, mot);
 
    else if (tolower(*mot) > A->lettre) /*Si mot après dans l'alphabet*/
        return est_dans_ATR(A->droit, mot);
 
    else{
        if (tolower(*(mot+1)) == '\0') /*Si fin de mot*/
            return A->fils->lettre == '\0'; /*On regarde si le mot est dans l'arbre*/
 
        return est_dans_ATR(A->fils, mot+1);
    }
}
