#include "graphe.h"

TypGraphe *g;

    /*
     *  Fonction :      viderTampon
     *
     *  Parametres :
     *
     *  Retour :        rien
     *
     *  Description :   vider le tampon pour eviter les problemes de saisies
     *
     */

void viderTampon(){
    int c;
    while ((c = getchar ()) != '\n' && c != EOF);
}

    /*
     *  Fonction :      affichageMenu
     *
     *  Parametres :
     *
     *  Retour :        rien
     *
     *  Description :   Affichage toutes les possibilites du menu
     *
     */

void affichageMenu(){
    printf("\tMenu\n"
           "1 - Creer un graphe\n"
           "2 - Lire un graphe\n"
           "3 - Inserer un sommet\n"
           "4 - Inserer une arete\n"
           "5 - Supprimer un sommet\n"
           "6 - Supprimer une arete\n"
           "7 - Afficher le graphe\n"
           "8 - Sauvegarder le graphe\n"
           "0 - Quitter\n");
}

    /*
     *  Fonction :      affichageMenu
     *
     *  Parametres :    int c (correspond a la fonctionnalite du menu)
     *
     *  Retour :        rien
     *
     *  Description :   Affichage toutes les possibilites du menu
     *
     */

void choixFonction(int c){
    switch (c) {
        case 0:
            if (g != NULL) {
                effacerGraphe(g);
            }
            exit(EXIT_SUCCESS);
            break;

        case 1:
            if (g != NULL) {
                effacerGraphe(g);
            }

            int tailleGraphe = 0;
            char estOriente = 'z';
            printf("Saisir si le graphe est oriente (o ou n) et sa taille : ");
            scanf("%1s %d", &estOriente, &tailleGraphe);
            viderTampon();

            g = creation(tailleGraphe, estOriente);

            break;

        case 2:
            if (g != NULL) {
                effacerGraphe(g);
            }

            char fichier[256];
            printf("Saisir le nom du fichier a charger : ");
            scanf("%256s", &fichier);
            viderTampon();

            g = lecture(fichier);

            break;

        case 3:
            if(g == NULL) {
                printf("Aucun graphe en memoire.\n");
                break;
            }

            insertionSommet(g);

            break;

        case 4:
            if(g == NULL) {
                printf("Aucun graphe en memoire.\n");
                break;
            }

            int depart = -1, arrivee = -1, poids = -1;
            printf("Saisir le sommet de depart, d'arrivee, et son poids : ");
            scanf("%d %d %d", &depart, &arrivee, &poids);
            viderTampon();

            insertionArete(g, depart, arrivee, poids);

            break;

        case 5:
            if(g == NULL) {
                printf("Aucun graphe en memoire.\n");
                break;
            }

            int sommet = -1;
            printf("Saisir le sommet a supprimer : ");
            scanf("%d", &sommet);
            viderTampon();

            suppressionSommet(g, sommet);

            break;

        case 6:
            if(g == NULL) {
                printf("Aucun graphe en memoire.\n");
                break;
            }

            printf("Saisir le sommet de depart et d'arrivee : ");
            scanf("%d %d", &depart, &arrivee);
            viderTampon();

            suppressionArete(g, depart, arrivee);

            break;

        case 7:
            if (g == NULL) {
                printf("Aucun graphe a afficher.\n");
                break;
            }
            else {
                affichage(g);
            }
            break;

        case 8:
            if(g == NULL) {
                printf("Aucun graphe en memoire.\n");
                break;
            }

            printf("Saisir le nom du fichier de sauvegarde : ");
            scanf("%s", fichier);
            viderTampon();
            sauvegarde(g, fichier);

            break;

        default:
            printf("Aucun choix correspondant.\n");
            break;
    }
}

int main(int argc, char **argv){
    while (1) {
        affichageMenu();

        int c;
        scanf("%1d", &c);
        viderTampon();

        choixFonction(c);
    }
}
