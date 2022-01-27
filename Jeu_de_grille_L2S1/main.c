#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

#include "my_struct.h"
#include "graphique.h"
#include "console.h"

int get_rand(int max){
    
    /*Fonction qui génere un entier entre max and -max*/
    return (random() % (2* max)) - max;
}

void quickFill(Game* jeu){
    // Fonction qui remplit le tableau de jeu avec des entiers
    int i = 0;
    int j = 0;

    for (i = 0; i < (*jeu).size_tab; i++)
        for (j = 0; j < (*jeu).size_tab; j++)
            (*jeu).tab[i][j] = get_rand((*jeu).max);
    return;
}

int remplissage(int *lig, int *col, Game *jeu){
    
    /*fonction qui ajoute la valeur de la case à traiter au score du joueur
     elle traite une seule colonne (décalage des valeurs de bas en haut jusqu'a
     la case a la ligne 0 qui est remplacée par un entier aléatoire)*/
     
     
    int i;

    (*jeu).somme = (*jeu).somme + (*jeu).tab[*lig][*col];
    
    for (i = *lig; i >= 0; i--){
        
        if (i == 0)
            (*jeu).tab[i][*col] = get_rand((*jeu).max);
        
        else 
            (*jeu).tab[i][*col] = (*jeu).tab[i-1][*col];
    }
    return 0;
}

int modifie_tab(int *lig_1, int *col_1, int *lig_2, int *col_2, Game *jeu){

    /* Cette fonction commence par déterminer le segment à modifier dans le tableau.
    Puis en fonction du type de segment, elle parcourt le tableau pour  passer case
     par case le segment à traiter à la fontion 'remplissage'*/

    int i, max_l, max_c, min_c, min_l, col_co;

    (*jeu).coups += 1;
    
    /*On ordonne les valleur afin de determiner que est le point le plus en haut à gauche et le quel est le plus en bas à droite*/
    
    // les noms des variables indiquent ce que fait le calcul 
    max_l = (*lig_1 >= *lig_2) ? *lig_1 : *lig_2;
    min_l = (*lig_1 <= *lig_2) ? *lig_1 : *lig_2;
    max_c = (*col_1 >= *col_2) ? *col_1 : *col_2;
    min_c = (*col_1 <= *col_2) ? *col_1 : *col_2;
    //selectionne la colonne du point correspondant à min_l
    col_co = (min_l == *lig_1) ? *col_1 : *col_2;
    /* SEGMENTS HORISONTAUX:*/
    if (*col_1 == *col_2)

        for (i = max_l - min_l; i >= 0; i--)
            remplissage(&max_l, col_2, jeu);
    /*SEGMENTS VERTICAUX:*/
    else if (*lig_1 == *lig_2)

        for (i = min_c; i <= max_c; i++)
            remplissage(lig_1, &i, jeu);
    /*SEGMENTS DIAGAUNAUX:*/
    else if (((*lig_2 - *lig_1)/(*col_2 - *col_1))== -1 )

        for (i = min_l; i <= max_l; i++){
            remplissage(&i, &col_co, jeu);
            col_co --;
        } 
    
    else if ( ((*lig_2 - *lig_1) / (*col_2 - *col_1)) == 1 )

        for (i = min_l; i <= max_l; i++){
            remplissage(&i, &col_co, jeu);
            col_co ++;
        }
    return 0;
}

int save(Game *jeu, const char *filename, int isgrapth, Win *win_info){
    int i = 0;
    int j = 0;
    
    FILE *fichier;
    /* Sauvegarde en elle même*/
    if ((fichier = fopen(filename, "w")) != NULL){

        fprintf(fichier, "%d\n", (*jeu).size_tab);
        fprintf(fichier, "%d %d %d\n", (*jeu).somme, (*jeu).coups, (*jeu).max);

        for (i = 0; i <  (*jeu).size_tab; i++){

            for (j = 0; j < (*jeu).size_tab; ++j){

                fprintf(fichier, "%d", (*jeu).tab[i][j]);

                if ((j + 1) != (*jeu).size_tab)
                    fprintf(fichier, " ");
            }
            fprintf(fichier, "\n");
        }
        fclose(fichier);
        /* confirmation de sauvegarde à l'utilisateur*/
        if (isgrapth){

            MLV_draw_filled_rectangle(
                                (*win_info).menu_x, 0,
                                MENU_WIDTH, (*win_info).height,
                                MLV_COLOR_BLACK
                                );
            MLV_draw_text_box(
                                (*win_info).menu_x, (*win_info).menu_save_conf_y,
                                MENU_WIDTH, (*win_info).menu_height,
                                "Fichier sauvegardé!", 10,
                                MLV_COLOR_RED,
                                MLV_COLOR_BLACK,
                                MLV_COLOR_WHITE,
                                MLV_TEXT_CENTER,
                                MLV_HORIZONTAL_CENTER,
                                MLV_VERTICAL_CENTER
                            );
            MLV_actualise_window();
            MLV_wait_seconds(1);
            MLV_clear_window(MLV_COLOR_BLACK);
        }
        else
            printf("Le fichier a bien été sauvegardé!\n\n");
        return 1;
    }
    printf("ERREUR : impossible d'ouvir le fichier '%s' pour sauvegarder dendans.\n", filename);
    return 0;
}

int load(Game *jeu, const char *filename){
    int i = 0;
    int j = 0;

    FILE *fichier;

     if ((fichier = fopen(filename, "r")) != NULL){
        fscanf(fichier, "%d\n", &((*jeu).size_tab));
        fscanf(fichier, "%d %d %d\n", &((*jeu).somme), &((*jeu).coups), &((*jeu).max));

        for (i = 0; i< (*jeu).size_tab; i++){
            for (j = 0; j < (*jeu).size_tab; j++){
                if ((j+1) != (*jeu).size_tab)
                    fscanf(fichier, " %d", &((*jeu).tab[i][j]));
                else
                    fscanf(fichier, " %d\n", &((*jeu).tab[i][j]));
            }
        }
        fclose(fichier);
        return 1;
    }

    printf("ERREUR : impossible de charger le fichier '%s'.\n", filename);
    return 0;
}

void create_grid (Game *jeu, const char* para ){
    if (strchr(para, 'a'))
        create_grid_console(jeu);

    else if (strchr(para, 'g')){
        create_grid_graphique(jeu);
    }
    quickFill(jeu);
}

int main(int argc, const char * argv[]) {
    
    srandom(time(NULL));
    
    int i;
    int res_coord;
    int lig_1,col_1, lig_2, col_2;

    char next_move = 'c';

    Win win_info; /* cf graphique.h*/
    Game jeu; /* cf my_struct.h*/

    jeu.somme = 0;
    jeu.coups = 0;

    if (argc == 3){

        for (i=0; i<argc; i++){
            /* Verification de la pertinance de parametres passé au programe */
            if ( (strchr(argv[1], 'c') == NULL &&strchr(argv[1], 'l') == NULL ) 
                || (strchr(argv[1], 'g') == NULL && strchr(argv[1], 'a') == NULL ) )  {
                print_usage();
                break;
            }

            if (strchr(argv[1], 'c') && strchr(argv[1], 'l')== NULL)
                create_grid(&jeu, argv[1]);

            if (strchr(argv[1], 'l')&& strchr(argv[1], 'c')== NULL)
                if( !(load(&jeu, argv[2])))
                    return 1;

            if (strchr(argv[1], 'a')&& strchr(argv[1], 'g')== NULL ){

                affTabConsole(&jeu);
                
                while (1){
                    actions(&next_move);

                    if (next_move == 'c'){
                        
                    /* La boucle principle du jeu en ASCII*/
                
                        entree_coordonne(&lig_1, &col_1, &lig_2, &col_2, jeu.size_tab);  
                        modifie_tab(&lig_1, &col_1, &lig_2, &col_2, &jeu);
                        affTabConsole(&jeu);
                        
                        if (jeu.somme >= 100){

                            printf("Félicitation ! Que voulez- vous faire?\n(rejouer/q) \n");
                            scanf(" %c", &next_move);

                            if (next_move == 'r'){
                                jeu.somme = 0;
                               break;
                            }
                        }
                    }                    
                    if (next_move == 'q')
                        return 0;

                    if (next_move == 's'){
                        if( !save(&jeu, argv[2], 0, &win_info))
                            return 1;
                    }
                }
            }
            if (strchr(argv[1], 'g')&& strchr(argv[1], 'a')== NULL){
                /*Boucle principale du jeu en GRAPHIQUE*/
                make_window(jeu.size_tab);
        
                while (1){
                    graphique(&jeu, &win_info);
                    res_coord = coordonnee_graphique(&lig_1, &col_1, &lig_2, &col_2, &win_info);

                    if (res_coord == 2)
                        modifie_tab(&lig_1, &col_1, &lig_2, &col_2, &jeu);

                    else if (res_coord == 3){
                        if( !save(&jeu, argv[2], 1, &win_info))
                            return 1;
                    }
                    else{
                        return 0;
                    }
                }
            }
        }
    }
    else
        print_usage();
    return 0;
}
