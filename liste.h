/*
****************************************************************
*
*   Programme : liste.h
*
*   ecrit par : BOULALA LAVIER
*
*   resume : fichier d'entete du fichier liste.c
*
*   date : 02/10/2014
*
****************************************************************
*/

#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0

typedef struct element {
    int             voisin;         /* valeur du sommet */
	int				poids;			/* Poids de l'arete */
    struct element  *voisinSuivant;     /* pointeur vers le prochain sommet */
}Element;

typedef struct liste{
    int         taille;     /* taille de la liste */
    Element     *debut;     /* pointeur vers le premier element de la liste */
}TypVoisins;

TypVoisins *initialiserListe(int tailleListe);
void ajouterEnTete(TypVoisins *liste, int val, int poids);
void afficherListe(TypVoisins *liste);
void effacerListe(TypVoisins *liste);
int existeDansListe(TypVoisins *liste, int val);
int supprimeDansListe(TypVoisins *liste, int val);
void obtenirListe(TypVoisins *liste, char *l);

#endif
