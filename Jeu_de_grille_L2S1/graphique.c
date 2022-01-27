#include <MLV/MLV_all.h>
#include "my_struct.h"
#include "graphique.h"

void graphique(Game *jeu, Win* win_info){

    int i,j;
    int x_box = 0;
    int y_box = 0;
    char inter[12];
    char interb[12];
    char score[20] = "Score : ";
    char coups_c[20] = "Coups : ";
    /* calcule de la hauteur et largeur necessaire au tableau de jeu et a son menu*/
    (*win_info).width = (*jeu).size_tab * BOX_SIZE + SIZE_MENU;
    (*win_info).height = (*jeu).size_tab * BOX_SIZE;

    /*calcul de l'alignement en x des boutons du menu*/
    (*win_info).menu_x = (*win_info).width-SIZE_MENU +25;
    /*calcul de la hauteur des boutons du menu*/
    (*win_info).menu_height = (*win_info).height/6;

    /* calcule de l'alignement vertical des bontons du menu*/
    (*win_info).menu_coups_y = 10;
    (*win_info).menu_quit_y = (*win_info).height - ((*win_info).height / 6 + 10);
    (*win_info).menu_score_y = (*win_info).menu_coups_y + (*win_info).menu_height + 10 ;
    (*win_info).menu_save_y = (*win_info).menu_quit_y - ((*win_info).menu_height + 10);
    (*win_info).menu_save_conf_y = (*win_info).menu_save_y - ((*win_info).menu_height + 10);
    /*affichage du tableau de jeu*/
    for (i=0; i< (*jeu).size_tab; i ++){

        for (j=0; j< (*jeu).size_tab; j++){

            sprintf(inter, "%d", (*jeu).tab[i][j]);

            MLV_draw_text_box(
                x_box, y_box,
                BOX_SIZE, BOX_SIZE,
                inter,1,
                MLV_COLOR_SLATE_GRAY, 
                MLV_COLOR_GRAY, 
                MLV_COLOR_BLACK,
                MLV_TEXT_CENTER,
                MLV_HORIZONTAL_CENTER,
                MLV_VERTICAL_CENTER
            );
            x_box += BOX_SIZE;
        }

        y_box += BOX_SIZE;
        x_box = 0;
    }
    /* affichage des bontons du menu*/
    sprintf(interb, "%d", (*jeu).coups);
    strcat(coups_c, interb);

    sprintf(inter, "%d", (*jeu).somme);
    strcat(score, inter);


    MLV_draw_text_box(
        (*win_info).menu_x, (*win_info).menu_coups_y,
        MENU_WIDTH, (*win_info).menu_height,
        coups_c, 1,
        MLV_COLOR_RED,
        MLV_COLOR_RED,
        MLV_COLOR_BLACK,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER
    );
    MLV_draw_text_box(
        (*win_info).menu_x, (*win_info).menu_score_y,
        MENU_WIDTH, (*win_info).menu_height,
        score, 1,
        MLV_COLOR_RED,
        MLV_COLOR_RED,
        MLV_COLOR_BLACK,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER
    );
    MLV_draw_text_box(
        (*win_info).menu_x, (*win_info).menu_save_y ,
        MENU_WIDTH, (*win_info).menu_height,
        "save", 1,
        MLV_COLOR_RED,
        MLV_COLOR_RED,
        MLV_COLOR_BLACK,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER
    );
    MLV_draw_text_box(
        (*win_info).menu_x, (*win_info).menu_quit_y,
        MENU_WIDTH, (*win_info).menu_height,
        "quit", 1,
        MLV_COLOR_RED,
        MLV_COLOR_RED,
        MLV_COLOR_BLACK,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER,
        MLV_VERTICAL_CENTER
    );
    /*message de victoire*/
    if ((*jeu).somme >= 100){

        MLV_wait_seconds(2); 
        
        MLV_clear_window(MLV_COLOR_BLACK);

        MLV_draw_adapted_text_box(
            (*win_info).width/2 - 100, (*win_info).height/2 - 100,
            " \n Félicitation vous avez gagné ! \n", 10,
            MLV_COLOR_RED,
            MLV_COLOR_BLACK,
            MLV_COLOR_WHITE,
            MLV_TEXT_CENTER
        );
    }

    MLV_actualise_window();
}

int verifie_coordonnee_graphique(int x, int y, Win* win_info){
    /* fonction renvoyant 0, 1, 2, 3 selon que l'on ait cliqué
    sur le vide, une case, le bouton 'quit', et le 'save' respectivement*/

    if ( (0 <= x && x <= (*win_info).height) 
        && (0 <= y && y <= (*win_info).height) )
        return 1;

    else if ( ((*win_info).menu_x <= x && x <= (*win_info).menu_x + MENU_WIDTH) 
        && ((*win_info).menu_save_y <= y && y <= (*win_info).menu_save_y +  (*win_info).menu_height ))

        return 2;

    else if ( ((*win_info).menu_x <= x && x <= (*win_info).menu_x + MENU_WIDTH) 
        && ((*win_info).menu_quit_y <= y && y <= (*win_info).menu_quit_y +  (*win_info).menu_height ))

        return 3;        

    return 0;
}

int coordonnee_graphique (int *lig_1, int *col_1, int *lig_2, int *col_2, Win* win_info){
    /* recupére 2 clics valides ou un clic sur un bouton*/
    int var = 0;
    int x_mouse, y_mouse;
    int num_click = 1;

    do{
        MLV_wait_mouse(&x_mouse, &y_mouse);

        var = verifie_coordonnee_graphique(x_mouse, y_mouse, win_info);

        if (var == 1){ 
            /* num_click permet ici de savoir si l'on doit remplir le premier clic sur le deuxieme
            sans pour autant bloquer les boutons*/
            if (num_click == 1){
                *col_1 = x_mouse / BOX_SIZE;
                *lig_1 = y_mouse / BOX_SIZE;
                MLV_draw_rectangle(
                    *col_1 * BOX_SIZE,
                    *lig_1 * BOX_SIZE,
                    BOX_SIZE, BOX_SIZE,
                    MLV_COLOR_BLUE
                    );
                MLV_actualise_window();
            }
            else{
                *col_2 = x_mouse / BOX_SIZE;
                *lig_2 = y_mouse / BOX_SIZE;
                MLV_draw_rectangle(
                    *col_2 * BOX_SIZE,
                    *lig_2 * BOX_SIZE,
                    BOX_SIZE, BOX_SIZE,
                    MLV_COLOR_BLUE
                    );
                MLV_actualise_window();
                MLV_wait_milliseconds(300);
                return 2;
            }

            if (num_click == 1)
                num_click = 2;
            else
                num_click  = 1; 
        }
         
        else if (var == 2)
            return 3;

        else if (var == 3)
            return 1;

     } while((var == 1 && num_click != 2) || (var !=2 && var != 3));

     return 0;
}

void make_window(int size_tab){

    int width = size_tab * BOX_SIZE + SIZE_MENU;
    int height = size_tab * BOX_SIZE;

    MLV_create_window( "grille", "grille", width, height);
}

void create_grid_graphique(Game *jeu){
    char* text;
    int tmp;
    /* Même chose que create_grid_console mais avec affichage dans une fenêtre*/
    MLV_create_window( "saisie de paramétres", "grille", 800, 200);

    do{

        MLV_wait_input_box(
            50,50,
            700,100,
            MLV_COLOR_RED,
            MLV_COLOR_WHITE,
            MLV_COLOR_BLACK,
            "      Veuillez entrer une taille valide (comprise entre 0 et 20 inclu) : ",
            &text
        );

        (*jeu).size_tab= atoi(text);

        if ((*jeu).size_tab <=0 || (*jeu).size_tab > N)
            MLV_draw_adapted_text_box(
                250,25,
                "      ! LISEZ LA CONSIGNE !      " , 2, 
                MLV_COLOR_GREEN,
                MLV_COLOR_WHITE,
                MLV_COLOR_BLACK,
                MLV_TEXT_CENTER
            );
    } while ((*jeu).size_tab <= 0 || (*jeu).size_tab > N);

     MLV_clear_window(MLV_COLOR_BLACK);   

    do{
        MLV_wait_input_box(
            150,50,
            450,100,
            MLV_COLOR_RED,
            MLV_COLOR_WHITE,
            MLV_COLOR_BLACK,
            "     Veuillez entrer la valeur maximale != 0 : ",
            &text
        );
        tmp = atoi(text);
        if (tmp < 0)
            tmp = -1 * tmp;
        (*jeu).max = tmp;

        if ((*jeu).max ==0)
            MLV_draw_adapted_text_box(
                250,25,
                "      ! LISEZ LA CONSIGNE !     " , 2,
                MLV_COLOR_GREEN,
                MLV_COLOR_WHITE,
                MLV_COLOR_BLACK,
                MLV_TEXT_CENTER
            );
    } while ((*jeu).max == 0);

    MLV_free_window();
}
