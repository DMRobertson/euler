#ifndef VECTOR_
#define VECTOR_

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// an automatically extendable array of size_t

typedef struct vector {
	size_t length;
	size_t capacity;
	size_t* data;
} vector;

vector* vnew(size_t initial_length){
	assert(initial_length > 0);
	vector* output = malloc(sizeof(vector));
	output->length = 0;
	output->capacity = initial_length;
	output-> data = malloc(output->capacity * sizeof(size_t));
	return output;
}

size_t vget(vector* vector, size_t index){
	assert(index < vector->length);
	return vector->data[index];
}

bool vpush(vector* vector, size_t value){
	while (vector->length >= vector->capacity){
		vector->capacity *= 2;
		vector->data = realloc(vector->data, vector->capacity * sizeof(size_t));
		if (vector->data == NULL){
			return false;
		}
	}
	vector->data[vector->length] = value;
	vector->length++;
	return true;
}

size_t vpeek(vector* vector){
	return vector->data[vector->length - 1];
}

void vfree(vector* vector){
	free(vector->data);
	free(vector);
}

int cmp_size_t(const void* a, const void* b){
	size_t A = *(size_t*) a;
	size_t B = *(size_t*) b;
	return (A > B) - (B > A) ;
}

bool vcontains_sorted(vector* table, size_t value){
	void* pointer = bsearch(&value, table->data, table->length, sizeof(size_t), cmp_size_t);
	return pointer != NULL;
}

#endif //VECTOR_