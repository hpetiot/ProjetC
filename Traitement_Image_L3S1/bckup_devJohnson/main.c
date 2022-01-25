#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <math.h>

#include "color.h"
#include "decoding.h"
#include "encoding.h"
#include "encoding_graph.h"
#include "decoding_graph.h"
#include "create_quadtree.h"
#include "list_errors.h"
#include "minimisation.h"
#include "quadtree.h"

/* ------------------------------------------------------------------ */

int main(int argc, char const *argv[]) {
	ErrorList_FirstLast list_firstlast;
	MLV_Image *image, *image_tree, *image_decoding;
	Tree *tree = NULL, *tree_decoding = NULL;
	FILE* file = NULL;

	MLV_create_window("Projet", "Projet", SIZE_IMAGE, SIZE_IMAGE);
	
	/* ------------------------------------------------ */
	
	image = MLV_load_image("./img/panda.png");
	initialize_firstlast(&list_firstlast);

	if (!create_quadtree(&tree, image, &list_firstlast)) {
		fprintf(stderr, "Error in image_to_quadtree\n");
		exit(EXIT_FAILURE);
	}

	if (!tree_to_image(&image_tree, tree)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	MLV_draw_image(image_tree, 0, 0);
	MLV_actualise_window();

	MLV_wait_seconds(0); 
	MLV_free_image(image_tree);
	
	/* ------------------------------------------------ */
	/* ------------------------------------------------ */

	printf("Encoding (in color)... ");

	file = fopen("./img/encoding_color.qtc", "wb");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	encoding(tree, file);
	printf("Done.\n");

	fclose(file);

	/* ------------------------------------------------ */
	/* ------------------------------------------------ */

	printf("Decoding (in color)... ");
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
	MLV_wait_seconds(0);

	file = fopen("./img/encoding_color.qtc", "rb");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	if (decoding(&tree_decoding, file) < 0) {
		fprintf(stderr, "Error : decoding\n");
		exit(EXIT_FAILURE);
	}

	printf("Done.\n");
 	
 	if (!tree_to_image(&image_decoding, tree_decoding)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	MLV_draw_image(image_decoding, 0, 0);
	MLV_actualise_window();
	MLV_wait_seconds(0);

	MLV_free_image(image_decoding);
	free_tree(tree_decoding);
	free(tree_decoding);
	tree_decoding = NULL;
	fclose(file);
 	
 	/* ------------------------------------------------ */
	/* ------------------------------------------------ */

	printf("Encoding (black & white)... ");

	file = fopen("./img/encoding_bw.qtn", "wb");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	encoding_bw(tree, file);
	printf("Done.\n");

	fclose(file);

	/* ------------------------------------------------ */
	/* ------------------------------------------------ */

	printf("Decoding (black & white)... ");
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
	MLV_wait_seconds(0);

	file = fopen("./img/encoding_bw.qtn", "rb");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	if (decoding_bw(&tree_decoding, file) < 0) {
		fprintf(stderr, "Error : decoding\n");
		exit(EXIT_FAILURE);
	}

	printf("Done\n");
 	
 	if (!tree_to_image(&image_decoding, tree_decoding)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	MLV_draw_image(image_decoding, 0, 0);
	MLV_actualise_window();
	MLV_wait_seconds(0);

	MLV_free_image(image_decoding);
	free_tree(tree_decoding);
	free(tree_decoding);
	tree_decoding = NULL;
	fclose(file);

	/* ------------------------------------------------ */
	/* ------------------------------------------------ 

	printf("Minimisation (without loss)... ");
	minimize_without_loss(&tree);
	printf("Done\n");
	
	if (!tree_to_image(&image_tree, tree)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	MLV_draw_image(image_tree, 0, 0);
	MLV_actualise_window();

	MLV_wait_seconds(0);
	MLV_free_image(image_tree);

	 ------------------------------------------------ */
	/* ------------------------------------------------ */

	minimize_loss(&tree, image, return_zone(0, 0, SIZE_IMAGE, SIZE_IMAGE));

	if (!tree_to_image(&image_tree, tree)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	MLV_draw_image(image_tree, 0, 0);
	MLV_actualise_window();

    MLV_wait_seconds(0);
    MLV_free_image(image_tree);

    /* ------------------------------------------------ */
    /* ------------------------------------------------ */

    printf("Encoding Minimized Quadtree (in color)... ");

	file = fopen("./img/encoding_graph_color.gmc", "w+");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	encoding_graph(tree, file, 0, 0);
	printf("Done.\n");

	fclose(file);

	/* ------------------------------------------------ */
    /* ------------------------------------------------ */

    printf("Decoding Graph (in color)... ");
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_actualise_window();
	MLV_wait_seconds(0);

	file = fopen("./img/encoding_graph_color.gmc", "r");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	if (decoding_graph(&tree_decoding, file) < 0) {
		fprintf(stderr, "Error : decoding\n");
		exit(EXIT_FAILURE);
	}
 	
 	printf("Done\n");

 	if (!tree_to_image(&image_decoding, tree_decoding)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	MLV_draw_image(image_decoding, 0, 0);
	MLV_actualise_window();
	MLV_wait_seconds(0);

	MLV_free_image(image_decoding);
	free_tree(tree_decoding);
	free(tree_decoding);
	tree_decoding = NULL;
	fclose(file);

	/* ------------------------------------------------ */
    /* ------------------------------------------------ */

	printf("Encoding Minimized Quadtree (black & white)... ");

	file = fopen("./img/encoding_graph_bw.gmn", "w+");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	encoding_graph_bw(tree, file, 0, 0);
	printf("Done.\n");

	fclose(file);

    /* ------------------------------------------------ */
    /* ------------------------------------------------ */

	printf("Decoding Graph (black & white)... ");
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();
	MLV_wait_seconds(0);

	file = fopen("./img/encoding_graph_bw.gmn", "r");
	if (file == NULL) {
		fprintf(stderr, "Error : couldn't open file XXXX \n");
		exit(EXIT_FAILURE);
	}

	if (decoding_graph_bw(&tree_decoding, file) < 0) {
		fprintf(stderr, "Error : decoding\n");
		exit(EXIT_FAILURE);
	}
 	
 	printf("Done\n");

 	if (!tree_to_image(&image_decoding, tree_decoding)) {
		fprintf(stderr, "convention error\n");
		exit(EXIT_FAILURE);
	}

	MLV_draw_image(image_decoding, 0, 0);
	MLV_actualise_window();
	MLV_wait_seconds(0);

	MLV_free_image(image_decoding);
	free_tree(tree_decoding);
	free(tree_decoding);
	tree_decoding = NULL;
	fclose(file);

    /* ------------------------------------------------ */

	free_tree(tree);
	free(tree);
	free_error_list(&list_firstlast.first);
	MLV_free_image(image);
	MLV_free_window();
	
	return 0;
}