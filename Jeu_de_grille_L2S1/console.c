#include <stdio.h>
#include "my_struct.h"

void print_usage(){
    printf("\nERREUR: Paramétres incomplets ou incorrectes:\n");
    printf("\n  USAGE : ./grille -[(a/g)(c/l)] [nom d'un fichier]\n");
    printf("avec :\n\t\t-a : affichage en ascii\n\tOU\n\t\t-g : affichage graphique\n\n");
    printf("ET\n\n\t\t-c : on crée une nouvelle grille\n\tOU\n\t\t-l : on charge une grille existante\n");
}

int verifie_coordonnee(int *lig_1, int *col_1, int *lig_2, int *col_2, int size_tab){
    /* Verifie la pertinance des coordonnées entrée en console*/
    int coef = 0;
    int nom = (*lig_2 - *lig_1);
    int denom = (*col_2 - *col_1);
    
    if (denom == 0) // pour eviter le x/0 dans le calcul de 'coef'
        return 0;
    
    if ((0 <= *lig_1 && *lig_1 < size_tab)
        && (0 <= *col_1 && *col_1 < size_tab)
        && (0 <= *lig_2 && *lig_2 < size_tab)
        && (0 <= *col_2 && *col_2 < size_tab)) {
        // au dessus: verifie que la coordonnée est dans le tableau
        
        if ((nom % denom) == 0){
            
            coef = nom / denom;
            
            if (coef == 1 || coef == -1 || coef == 0) // coef: = 0 -> ligne, = 1 -> diagonale valide'/', =-1 -> diagonale valide '\'
                return 0;
        }
    }
    printf("Veuillez entrer des coordonnées valides \n");
    return 1;
}

int entree_coordonne(int *lig_1, int *col_1, int *lig_2, int *col_2, int size_tab){
    /* demande des coordonées à l'utilisateur en mode ascii*/
    do {
        printf("coordonnée : ");
        scanf("%d %d", lig_1 , col_1);
        printf("coordonnée : ");
        scanf("%d %d", lig_2, col_2);
        
    } while( (verifie_coordonnee( lig_1, col_1, lig_2 ,col_2 , size_tab )) != 0);
    
    return 0;
}
void affTabConsole(Game *jeu){
    int i = 0;
    int j = 0;
    
    printf("somme %d coups %d\n", (*jeu).somme, (*jeu).coups);
    printf("%9s", "");
    
    /* affiche les coordonnée en haut du tableau 
    nous utilisont ici des esaces plustôt que des 
    '\t' car les '\t' on un comportement moins prédictible */

    for (i = 0; i < (*jeu).size_tab; i++)
        printf("% -8d", i);

    printf("\n%9s","*****");
    
    /* affiche la barre horizontale*/

    for (i = 0; i < (*jeu).size_tab; i++)
        printf("********");
    printf("\n");

    /* affiche les coordonées à gauch + leurs '*' */
    for (i=0;i< (*jeu).size_tab; i++){
        printf("%-4d*    ", i);

        /* affiche les valeurs dans le tableau */

        for (j = 0; j < (*jeu).size_tab; j++)
            printf("% -8d", (*jeu).tab[i][j]);

            /*le ' ' signifie qu'on ajuste grace à des espace,
            	le '-' signifie que l'on veut caller les valeur à gauche
            	le 8 signifie que l'on veut que la valeur et son ajustement en espaces prenne 8 charactères au total*/

        printf("\n");
    }
    printf("\n");
}

int actions(char *next_move){
    /*Permet au joueur de choisir entre S sauvegarder, C continuer a jouer, Q quitter le jeu*/
    do {printf("actions (c/s/q) : ");
        scanf(" %c", next_move);
    }while( *next_move != 'c' && *next_move != 's' && *next_move != 'q');
    
    printf("\n");
    
    return 0;
}

void create_grid_console(Game *jeu){
    /* Permet au joueur d'entrer la taille et le max du tableau en mode ascii
     et de vérifier la validité de ses valeurs*/
	do{
            printf("\nVeuillez entrer une taille valide (comprise entre 0 et %d inclu) : ", N);
            scanf("%d", &((*jeu).size_tab));

            if ((*jeu).size_tab <= 0 || (*jeu).size_tab > N)
                printf("\n LISEZ LA CONSIGNE \n");

        } while ((*jeu).size_tab <= 0 || (*jeu).size_tab > N);

        do {    
            printf("Veuillez entrer la valeur maximale ou la valeur minimale !=0 : ");
            scanf("%d", &((*jeu).max));

            if ((*jeu).max ==0)
                printf("\n LISEZ LA CONSIGNE \n");
            
        } while ((*jeu).max == 0);
            
        if ((*jeu).max < 0)
            (*jeu).max = -1*((*jeu).max);
            
        printf("\n"); 
}
