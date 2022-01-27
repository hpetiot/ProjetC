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

	/**
	* Initialize a bit_buffer
	* @param bit_buffer The bit_buffer we are initializing
	*/
	void init_bit_buffer(Bit_buffer *bit_buffer);

	/**
	* Add '0' to bit_buffer in order to complete the byte
	* @param bit_buffer The bit_buffer we are "padding"
	* @param file The file we are writing in
	*/
	void padding_last_oct(Bit_buffer *bit_buffer, FILE *file);

	/* If val == 1, add 1 to bit buffer.
	   If val == 0, add 0 to bit buffer.
	   If bit_buffer is full, write it in file and reset the bit_buffer */

	/**
	* Fill a bit_buffer depending of the value of "val"
	* If val != 0, add 1 to bit_buffer
	* If val == 0, add 0 to bit_buffer
	* @param bit_buffer The bit_buffer we are filling
	* @param val The value 
	* @param file The file we are writing in if bit_buffer is full (byte completed)
	*/
	void write_bit(Bit_buffer *bit_buffer, int val, FILE *file);


	/**
	* Convert color into a byte, and write it in file 
	* @param bit_buffer The bit_buffer we are filling in order to write color in the file
	* @param color The color we want to add in file
	* @param file The file we are writing the color in
	*/
	void write_bit_color(Bit_buffer *bit_buffer, unsigned char color, FILE *file);

	/**
	* Read the current bit in bit_buffer
	* If we have read all the bit, fgetc in order to get the file next byte 
	* @param bit_buffer The bit_buffer we get the byte from, and read from 
	* @param file The file we are reading
	* @return Current value of bit_buffer (0 or 1)
	*/
	int read_bit(Bit_buffer *bit_buffer, FILE *file);

/* ------------------------------------------------------------------ */

#endif