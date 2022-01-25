#ifndef __BIT_BUFFER_H__
#define __BIT_BUFFER_H__

/* ------------------------------------------------------------------ */

	#include <stdio.h>
	#include <stdint.h>

/* ------------------------------------------------------------------ */

	typedef struct {
		uint8_t c;
		int current_bit;
	} Bit_buffer;

/* ------------------------------------------------------------------ */

	/* Init a bit_buffer */
	void init_bit_buffer(Bit_buffer *bit_buffer);

	/* Add '0' to the last octet in order to complete it */
	void padding_last_oct(Bit_buffer *bit_buffer, FILE *file);

	/* If val == 1, add 1 to bit buffer.
	   If val == 0, add 0 to bit buffer.
	   If bit_buffer is full, write it in file and reset the bit_buffer */
	void write_bit(Bit_buffer *bit_buffer, int val, FILE *file);

	/* Convert color into byte, and write it in file */
	void write_bit_color(Bit_buffer *bit_buffer, int color, FILE *file);

	/* Read the current bit in bit_buffer
	   If we have read all the bit, fgetc the next byte in file */
	int read_bit(Bit_buffer *bit_buffer, FILE *file);

/* ------------------------------------------------------------------ */

#endif