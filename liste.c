/*
****************************************************************
*
*   Programme : liste.c
*
*   ecrit par : BOULALA LAVIER
*
*   resume : contient des fonctions necessaires a la manipulation
*            des listes chainees.
*
*   date : 02/10/2014
*
****************************************************************
*/

#include "liste.h"

    /*
     *  Fonction :      initialiserListe
     *
     *  Parametre :     int tailleListe (taille de la liste)
     *
     *  Retour :        TypVoisins *liste (pointeur sur le debut de la liste)
     *
     *  Description :   permet d'initialiser une liste chainee en lui allouant
     *                  un espace en memoire.
     *
     */
    
TypVoisins *initialiserListe(int tailleListe){
    TypVoisins *liste = (TypVoisins *) malloc(sizeof(TypVoisins));
    liste->debut = (Element *) malloc(sizeof(Element));

    if (liste == NULL || liste->debut == NULL) {
        exit(EXIT_FAILURE);
    }

    liste->debut->voisinSuivant = NULL;
    liste->debut->voisin = -1;
    liste->debut->poids = -1;
    liste->taille = tailleListe;

    printf("[LISTE] L'initialisation de la liste s'est bien passee.\n");

    return (liste);
}

    /*
     *  Fonction :      ajouterEnTete
     *
     *  Parametres :    TypVoisins *liste (pointeur sur le debut de la liste)
     *                  int val (numero du somment a ajouter)
     *                  int poids (poids de l'arrete pour aller au sommet)
     *
     *  Retour :        rien
     *
     *  Description :   permet d'ajouter un element au debut d'une liste chainee.
     *
     */

void ajouterEnTete(TypVoisins *liste, int val, int poids){
    if (existeDansListe(liste, val) == FALSE) {
        Element *nouveau = (Element *) malloc(sizeof(Element));

        nouveau->voisinSuivant = liste->debut;
        nouveau->voisin = val;
        nouveau->poids = poids;
        liste->debut = nouveau;

        printf("[LISTE] L'ajout dans la liste s'est bien passe.\n");
    }
    else {
    printf("[LISTE] Erreur lors de l'ajout : l'element existe deja.\n");
    }
}

    /*
     *  Fonction :      afficherListe
     *
     *  Parametres :    TypVoisins *liste (pointeur sur le debut de la liste)
     *
     *  Retour :        rien
     *
     *  Description :   permet d'afficher une liste chainee.
     *
     */

void afficherListe(TypVoisins *liste){
    Element *tmp = liste->debut;

    while (tmp->voisinSuivant != NULL) {
        printf("(%d/%d)", tmp->voisin + 1, tmp->poids);
        tmp = tmp->voisinSuivant;
        if (tmp->voisinSuivant != NULL) {
            printf(", ");
        }
    }
    printf("\n");
}

    /*
     *  Fonction :      effacerListe
     *
     *  Parametres :    TypVoisins *liste (pointeur sur le debut de la liste)
     *
     *  Retour :        rien
     *
     *  Description :   permet d'effacer une liste chainee.
     *
     */
     
void effacerListe(TypVoisins *liste){
    Element *tmp = liste->debut;
    Element *tmpSuivant;

    while (tmp != NULL) {
        tmpSuivant = tmp->voisinSuivant;
        free(tmp);
        tmp = tmpSuivant;
    }

    free(liste);
  
    printf("[LISTE] La suppression de la liste s'est bien passee.\n");
}

    /*
     *  Fonction :      existeDansListe
     *
     *  Parametres :    TypVoisins *liste (pointeur sur le debut de la liste)
     *                  int val (valeur d'un element)
     *
     *  Retour :        TRUE si l'element existe dans la liste
     *                  FALSE s'il n'existe pas
     *
     *  Description :   permet de tester l'existence d'un element dans une liste chainee.
     *
     */
     
int existeDansListe(TypVoisins *liste, int val){
    Element *tmp = liste->debut;

    while (tmp != NULL) {
        if (tmp->voisin == val) {
            return (TRUE);
        }
    tmp = tmp->voisinSuivant;
    }

    return (FALSE);
}

    /*
     *  Fonction :      supprimerDansListe
     *
     *  Parametres :    TypVoisins *liste (pointeur sur le debut de la liste)
     *                  int val (valeur d'un sommet)
     *
     *  Retour :        rien
     *
     *  Description :   permet de supprimer un element dans une liste chainee.
     *
     */

int supprimeDansListe(TypVoisins *liste, int val){
    if (existeDansListe(liste, val) == TRUE) {
        Element *tmp = liste->debut;

        while (tmp->voisinSuivant != NULL) {
            if (liste->debut->voisin == val) {
	            liste->debut = liste->debut->voisinSuivant;
	            free(tmp);

	            printf("[LISTE] L'element a bien ete supprime.\n");

                return TRUE;
            }
            else {
	            if (tmp->voisinSuivant->voisin == val) {
	                Element *del = tmp->voisinSuivant;
	                tmp->voisinSuivant = del->voisinSuivant;
	                free(del);

	                printf("[LISTE] L'element a bien ete supprime.\n");

                    return TRUE;
	            }
	            else {
	                tmp = tmp->voisinSuivant;
	            }
            }
        }
    }
    printf("[LISTE] Suppression de %d impossible, il n'est pas dans la liste.\n", val);
    return FALSE;
}

    /*
     *  Fonction :      obtenirListe
     *
     *  Parametres :    TypVoisins *liste (pointeur sur le debut de la liste)
     *                  char *l (chaine de caractere representant la liste)
     *
     *  Retour :        rien
     *
     *  Description :   permet de remplir une chaine de caractere representant la liste chainee.
     *
     */

void obtenirListe(TypVoisins *liste, char *l){
    char temp[2] = "";
    Element *tmp = liste->debut;

    while (tmp->voisinSuivant != NULL) {
        if(l == NULL) {
            strcpy(l, "(");
        }
        else {
            strcat(l, "(");
        }
        sprintf(temp, "%d", tmp->voisin + 1);
        strcat(l, temp);
        strcat(l, "/");
        sprintf(temp, "%d", tmp->poids);
        strcat(l, temp);
        strcat(l, ")");

        tmp = tmp->voisinSuivant;
        if (tmp->voisinSuivant != NULL) {
            strcat(l, ", ");
        }
    }
}

