#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

size_t ceildiv(size_t num, int div){
	// return the ceiling of (num/div) == floor ((num + div - 1)/div)
	return (num + div - 1) / div;
}

typedef struct packed_bool_array {
	// An array of booleans stored in the bits of chars in memeory
	size_t boollength;
	size_t charlength;
	unsigned char* array;
} barray;


barray* bool_array(size_t length){
	/* Efficiently store an array of booleans by packing as many bools as we can get away with into a char. */
	size_t charlength = ceildiv(length, CHAR_BIT);
	barray* output = malloc(sizeof(barray));
	output->boollength = length;
	output->charlength = charlength;
	output->array = malloc( sizeof(unsigned char) * charlength );
	return output;
}

void bsetall(barray* data, unsigned char value){
	memset(data->array, value, data->charlength);
}

bool bget(barray* data, size_t index){
	size_t bitnum = index % CHAR_BIT;
	index /= CHAR_BIT;
	unsigned char mask = (1 << bitnum);
	bool bit = (data->array[index] & mask) != 0;
	return bit;
}

void bset(barray* data, size_t index, bool value){
	unsigned char bitnum = index % CHAR_BIT;
	index /= CHAR_BIT;
	unsigned char mask = (1 << bitnum);
	if (value) {
		data->array[index] |= mask;
	} else {
		data->array[index] &= (mask ^ -1); //I thought this would be -mask but apparently not!
	}
}