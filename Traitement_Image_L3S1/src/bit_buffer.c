#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bit_buffer.h"


/* ------------------------------------------------------------------ */

void init_bit_buffer(Bit_buffer *bit_buffer) {
	bit_buffer->c = 0;
	bit_buffer->current_bit = 7;
}

/* ------------------------------------------------------------------ */

void padding_last_oct(Bit_buffer *bit_buffer, FILE *file) {
	while (bit_buffer->current_bit != 0) {
		write_bit(bit_buffer, 0, file);
	}
}

/* ------------------------------------------------------------------ */

void write_bit(Bit_buffer *bit_buffer, int val, FILE *file) {
	bit_buffer->c |= (val != 0) << bit_buffer->current_bit;
	bit_buffer->current_bit--;

	if (bit_buffer->current_bit == -1) {
		fputc(bit_buffer->c, file);
		bit_buffer->c = 0;
		bit_buffer->current_bit = 7;
	}
}

/* ------------------------------------------------------------------ */

void write_bit_color(Bit_buffer *bit_buffer, unsigned char color, FILE *file) {
	int i;

	for (i = 7 ; i >= 0 ; i--) {
		write_bit(bit_buffer, color & (1 << i), file);
	}
}

/* ------------------------------------------------------------------ */

int read_bit(Bit_buffer *bit_buffer, FILE *file) {
	int res;

	res = bit_buffer->c & 1 << (bit_buffer->current_bit);

	res = (res != 0);
	bit_buffer->current_bit--;

	if (bit_buffer->current_bit == -1) {
		bit_buffer->c = fgetc(file);

		if (bit_buffer->c == EOF) {
			return -1;
		}

		bit_buffer->current_bit = 7;
	}

	return res;
}

/* ------------------------------------------------------------------ */
