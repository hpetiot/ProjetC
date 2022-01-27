#define BOX_SIZE 50 
#define SIZE_MENU 250
#define MENU_WIDTH 200

typedef struct {

    int width;
    int height;
    int menu_x;
    int menu_height;
    int menu_coups_y;
    int menu_quit_y;
    int menu_score_y;
    int menu_save_y;
    int menu_save_conf_y;
} Win ;

void graphique(Game *jeu, Win* win_info);
int verifie_coordonnee_graphique(int x, int y, Win* win_info);
int coordonnee_graphique (int *lig_1, int *col_1, int *lig_2, int *col_2, Win* win_info);
void make_window(int size_tab);
void create_grid_graphique(Game *jeu);