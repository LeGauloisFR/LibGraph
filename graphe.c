/*
****************************************************************
*
*   Programme : liste.c
*
*   ecrit par : Antoine LAVIER & Kevin BOULALA
*
*   resume : contient des fonctions necessaires a la manipulation
*            des graphes
*
*   date : 02/10/2014
*
****************************************************************
*/

#include "graphe.h"

    /*
     *  Fonction :      creation
     *
     *  Parametre :     int tailleGraphe (taille du graphe)
     *                  char estOriente ('o' si le graphe est oriente, 'n' sinon)
     *
     *  Retour :        TypGraphe *graphe (pointeur vers un graphe)
     *
     *  Description :   permet d'initialiser un graphe en memoire en fonction de
     *                  sa taille et de son orientation en lui allouant un espace
     *                  en memoire;
     *
     */

TypGraphe *creation(int tailleGraphe, char estOriente) {
    TypGraphe *graphe;
	graphe = (TypGraphe *) malloc(sizeof(TypGraphe));
    graphe->listesAdjacences = (TypVoisins **) calloc(tailleGraphe, sizeof(TypVoisins *));
    
    if (graphe == NULL || graphe->listesAdjacences == NULL) {
        exit(EXIT_FAILURE);
    }

    graphe->nbMaxSommets = tailleGraphe;
    graphe->estOriente = estOriente;
    
    printf("[GRAPHE] L'initialisation du Graphe de taille %d s'est bien passee.\n", graphe->nbMaxSommets);
  
    return (graphe);
}

    /*
     *  Fonction :      taille
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *
     *  Retour :        int taille (nombre de sommets existants dans le graphe)
     *
     *  Description :   permet de retourner la taille du graphe
     *
     */

int taille(TypGraphe *graphe){
	int taille;
	taille = 0;

	while (graphe->listesAdjacences[taille] != NULL) {
		taille++;
	}

	return (taille);
}

    /*
     *  Fonction :      sommetExiste
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *                  int sommet (correspond a l'indice dans le tableau des sommets)
     *
     *  Retour :        TRUE si le sommet existe
     *                  FALSE si le sommet n'existe pas
     *
     *  Description :   permet de connaitre l'existence du sommet passe en parametre
     *
     */

int sommetExiste(TypGraphe *graphe, int sommet){
    if (sommet < taille(graphe)) {
        return (TRUE);
    }
    return (FALSE);
}

    /*
     *  Fonction :      areteExiste
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *                  int depart (sommet de depart)
     *                  int arrivee (sommet d'arrivee)
     *
     *  Retour :        TRUE si l'arete existe
     *                  FALSE si l'arrete n'existe pas
     *
     *  Description :   permet de connaitre l'existence d'une arete entre 2 sommets
     *
     */

int areteExiste(TypGraphe *graphe, int depart, int arrivee){
    if(existeDansListe(graphe->listesAdjacences[depart], arrivee) == TRUE) {
        return (TRUE);
    }
    return (FALSE);
}

    /*
     *  Fonction :      insertionSommet
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *
     *  Retour :        rien
     *
     *  Description :   permet d'inserer un sommet au graphe
     *
     */

void insertionSommet(TypGraphe *graphe){
	int nvSommet;
	nvSommet = taille(graphe);

	if (nvSommet == graphe->nbMaxSommets) {
		printf("[GRAPHE] Insertion d'un sommet : Impossible taille max atteinte\n");
	}
	else {
		graphe->listesAdjacences[nvSommet] = initialiserListe(graphe->nbMaxSommets);
		printf("[GRAPHE] L'ajout du sommet %d s'est bien passe.\n", nvSommet + 1);	
	}
}

    /*
     *  Fonction :      insertionArete
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *                  int depart (sommet de depart)
     *                  int arrivee (sommet d'arrivee)
     *                  int poids (poids de l'arete)
     *
     *  Retour :        rien
     *
     *  Description :   permet d'inserer une arete avec un poids associe
     *
     */

void insertionArete(TypGraphe *graphe, int depart, int arrivee, int poids){
    depart = depart - 1;
    arrivee = arrivee - 1;

    if (sommetExiste(graphe, depart) == TRUE && sommetExiste(graphe, arrivee) == TRUE && areteExiste(graphe, depart, arrivee) == FALSE) {
        if (graphe->estOriente == 'o') {
            ajouterEnTete(graphe->listesAdjacences[depart], arrivee, poids);
        }
        else {
            ajouterEnTete(graphe->listesAdjacences[depart], arrivee, poids);
            ajouterEnTete(graphe->listesAdjacences[arrivee], depart, poids);
        }
        printf("[GRAPHE] Insertion de l'arete entre %d et %d de poids %d s'est bien passee.\n", depart + 1, arrivee + 1, poids);
    }
    else {
        if (sommetExiste(graphe, depart) == TRUE) {
            printf("[GRAPHE] Echec de l'insertion de l'arete : l'arrete existe deja.\n");
        }
        else {
            printf("[GRAPHE] Echec de l'insertion de l'arete.\n");
        }
    }
}

    /*
     *  Fonction :      suppressionSommet
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *                  int sommet (sommet a supprimer)
     *
     *  Retour :        rien
     *
     *  Description :   permet de supprimer un sommet dans un graphe
     *
     */

void suppressionSommet(TypGraphe *graphe, int sommet){
    int tailleGraphe;
    int i;

    tailleGraphe = taille(graphe);
    sommet = sommet - 1;

    if (sommetExiste(graphe, sommet) == TRUE) {

        for (i=0; i<tailleGraphe; i++) {
            supprimeDansListe(graphe->listesAdjacences[i], sommet);

            Element *tmp = graphe->listesAdjacences[i]->debut;

            while (tmp->voisinSuivant != NULL) {
                if (tmp->voisin > sommet) {
                    tmp->voisin = tmp->voisin - 1;
                }
                tmp = tmp->voisinSuivant;
            }
        }

        effacerListe(graphe->listesAdjacences[sommet]);

        for (i=sommet+1; i<tailleGraphe; i++) {  
            graphe->listesAdjacences[i-1] = graphe->listesAdjacences[i];    
        }

        graphe->listesAdjacences[tailleGraphe-1] = NULL;

        printf("[GRAPHE] Le sommet %d a ete supprime.\n", sommet + 1);
    }
    else {
        printf("[GRAPHE] Le sommet %d n'existe pas dans le graphe.\n", sommet+1);
    }
}

    /*
     *  Fonction :      suppressionArete
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *                  int depart (sommet de depart)
     *                  int arrivee (sommet d'arrivee)
     *
     *  Retour :        rien
     *
     *  Description :   permet de supprimer une arete dans un graphe
     *
     */

void suppressionArete(TypGraphe *graphe, int depart, int arrivee){
    depart = depart - 1;
    arrivee = arrivee - 1;
    int retour;
    retour = 0;

    retour = supprimeDansListe(graphe->listesAdjacences[depart], arrivee);
    if (graphe->estOriente == 'n') {
        retour = supprimeDansListe(graphe->listesAdjacences[arrivee], depart);
    }

    if(retour == TRUE) {
        printf("[GRAPHE] L'arete entre %d et %d a ete supprime.\n", depart + 1, arrivee + 1);
    }
    else {
        printf("[GRAPHE] L'arete entre %d et %d n'a pas ete supprime.\n", depart + 1, arrivee + 1);
    }
}

    /*
     *  Fonction :      lecture
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *
     *  Retour :        rien
     *
     *  Description :   permet d'afficher un graphe au format texte.
     *
     */

void affichage(TypGraphe *graphe){
    printf("\n# nombre maximum de sommets\n%d\n", graphe->nbMaxSommets);
    printf("# oriente\n%c\n", graphe->estOriente);
    printf("# sommets : voisins\n");
    int i;
    for (i=0; i<graphe->nbMaxSommets; i++) {
		if (graphe->listesAdjacences[i] == NULL) {
			break;
		}
        printf("%d : ", (i + 1));
        afficherListe(graphe->listesAdjacences[i]);
    }
    printf("\n");
}

    /*
     *  Fonction :      lecture
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *
     *  Retour :        rien
     *
     *  Description :   permet de creer un graphe a partir d'un fichier texte
     *
     */

TypGraphe *lecture(char *nomFichier){
    FILE *fichier;
    TypGraphe *graphe;

    fichier = NULL;
    graphe = NULL;
    fichier = fopen(nomFichier, "r");

    if (fichier != NULL) {
        int nbLignes;
        int tailleGraphe = -1;
        char estOriente = 'z';
        int nbSommets = 0;
        nbLignes = 0;
        char ligne[256];

        while (fgets(ligne, sizeof(ligne), fichier)) {
            if (ligne[0] != '\n') {
                nbSommets = nbSommets + 1;
            }
        }
        nbSommets = nbSommets - 5;

        rewind(fichier);

        printf("Nombre de sommets : %d.\n", nbSommets);
        
        while (fgets(ligne, sizeof(ligne), fichier)) {
            nbLignes++;

            if (nbLignes == 2) {
                sscanf(ligne, "%d", &tailleGraphe);
            }
            if (nbLignes == 4) {
                estOriente = ligne[0];
            }
            if (tailleGraphe > -1 && estOriente != 'z' && nbLignes == 5) {
                graphe = creation(tailleGraphe, estOriente);

                int i;
                for (i=0; i<nbSommets; i++) {
                    insertionSommet(graphe);
                }
            }
            if (nbLignes > 5) {
                if (ligne[0] != '\n') {
                    char copieLigne[strlen(ligne)];
                    strcpy(copieLigne, ligne);

                    char *s = (char *) strtok(copieLigne, ":");
                    s = (char *) strtok(0, ", ");

                    while (s) { 
                        int sommet, poids;
                        sscanf(s, "(%d/%d)", &sommet, &poids);
                        insertionArete(graphe, (nbLignes-5), sommet, poids);
                        s = (char *) strtok(0, ", ");
                    }
                }
            }
        }
    
        fclose(fichier);
    }
    else{
        printf("Impossible d'ouvrir le fichier %s.\n", nomFichier);
    }

    return (graphe);
}

    /*
     *  Fonction :      sauvegarde
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *                  char *nomFichier (nom de fichier a ecrire)
     *
     *  Retour :        rien
     *
     *  Description :   permet de sauvegarder un graphe dans un fichier texte
     *
     */

void sauvegarde(TypGraphe *graphe, char *nomFichier){
    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "w");

    if (fichier != NULL) {
        fprintf(fichier, "# nombre maximum de sommets\n%d\n", graphe->nbMaxSommets);
        fprintf(fichier, "# oriente\n%c\n", graphe->estOriente);
        fprintf(fichier, "# sommets : voisins\n");
        int i;
        for (i=0; i<graphe->nbMaxSommets; i++) {
            if (graphe->listesAdjacences[i] == NULL) {
                break;
            }
            char l[128] = "";
            obtenirListe(graphe->listesAdjacences[i], l);
            fprintf(fichier, "%d : %s\n", (i + 1), l);
        }

        fclose(fichier);
    }
    else {
        printf("Impossible de creer le fichier.\n");
    }
}

    /*
     *  Fonction :      effacerGraphe
     *
     *  Parametres :    TypGraphe *graphe (pointeur vers un graphe)
     *
     *  Retour :        rien
     *
     *  Description :   permet d'effacer un graphe.
     *
     */
     
void effacerGraphe(TypGraphe *graphe){
    int i;
    for (i=0; i<graphe->nbMaxSommets; i++) {
		if (graphe->listesAdjacences[i] == NULL) {
			break;
		}
        effacerListe(graphe->listesAdjacences[i]);
    }
  
    free(graphe->listesAdjacences);
    free(graphe);
    
    printf("[GRAPHE] La suppression du graphe s'est bien passee.\n");
}

