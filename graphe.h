/*
****************************************************************
*
*   Programme : graphe.h
*
*   ecrit par : Antoine LAVIER & Kevin BOULALA
*
*   resume : fichier d'entete du fichier graphe.h
*
*   date : 02/10/2014
*
****************************************************************
*/

#ifndef GRAPHE_H
#define GRAPHE_H

#include "liste.h"

typedef struct graphe{
    char        estOriente;             /* 'o' si le graphe est oriente, 'n' sinon */
    int         nbMaxSommets;           /* nombre maximum de sommets du graphe */
    TypVoisins  **listesAdjacences;     /* tableau contenant les listes d'adjacences */
}TypGraphe;

TypGraphe *creation(int tailleGraphe, char estOriente);
int taille(TypGraphe *graphe);
int sommetExiste(TypGraphe *graphe, int sommet);
int areteExiste(TypGraphe *graphe, int depart, int arrivee);
void insertionSommet(TypGraphe *graphe);
void insertionArete(TypGraphe *graphe, int depart, int arrivee, int poids);
void suppressionSommet(TypGraphe *graphe, int sommet);
void suppressionArete(TypGraphe *graphe, int depart, int arrivee);
void affichage(TypGraphe *graphe);
void sauvegarde(TypGraphe *graphe, char *nomFichier);
TypGraphe *lecture(char *nomFichier);
void effacerGraphe(TypGraphe *graphe);


#endif
