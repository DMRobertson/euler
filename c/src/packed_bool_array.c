#ifndef PACKED_BOOL_ARRAY_
#define PACKED_BOOL_ARRAY_

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "integer_maths.c"
#include "vector.c"

typedef struct packed_bool_array {
	// An array of booleans stored in the bits of chars in memeory
	size_t boollength;
	size_t charlength;
	unsigned char* array;
} barray;

void bsetall(barray* data, unsigned char value){
	memset(data->array, value, data->charlength);
}

barray* bool_array(size_t length){
	/* Efficiently store an array of booleans by packing as many bools as we can get away with into a char. */
	size_t charlength = ceildiv(length, CHAR_BIT);
	barray* output = malloc(sizeof(barray));
	output->boollength = length;
	output->charlength = charlength;
	output->array = calloc( charlength, sizeof(unsigned char));
	bsetall(output, 0);
	return output;
}

//TODO: barray* bresize(barray* array);

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

void bprint(const barray* const data){
	for (size_t i = 0; i > data->charlength; i++){
		size_t mask = 1;
		for (size_t j = 0; j < CHAR_BIT; j++){
			char bit = mask & data->array[i];
			putc(bit ? '1' : '0', stdout);
			mask <<= 1;
		}
	}
	putc('\n', stdout);
}

void bfree(barray* const data){
	free(data->array);
	free(data);
}


vector* bgather(barray* data){
	vector* indices = vnew(10);
	for (size_t index = 0; index < data->boollength; index++){
		if (bget(data, index)){
			vpush(indices, index);
		}
	}
	return indices;
}

#endif //PACKED_BOOL_ARRAY_