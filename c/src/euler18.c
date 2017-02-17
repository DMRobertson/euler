#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

   3
  7 4
 2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
*/

unsigned max(unsigned a, unsigned b){
	return a < b ? b : a;
}

typedef struct triangle {
	size_t depth;
	unsigned** data; 
} triangle;

triangle* load_triangle (char const * filepath){
	FILE* data = fopen(filepath, "r");
	// First count how many lines there are.
	size_t lines = 0;
	char c;
	while ((c = fgetc(data)) != EOF){
		if (c == '\n'){
			lines++;
		}
	}
	fseek(data, 0, SEEK_SET);
	
	triangle* output = calloc(1, sizeof(triangle));
	output->depth = lines;
	
	output->data = calloc(lines, sizeof(unsigned*) );
	for (size_t depth = 0; depth < lines; depth++){
		output->data[depth] = calloc(depth + 1, sizeof(unsigned) );
		for (size_t index = 0; index <= depth; index++){
			fscanf(data, "%02d", output->data[depth] + index);
		}
	}
	fclose(data);
	return output;
}

void free_triangle(triangle* grid){
	for (size_t i = 0; i < grid->depth; i++){
		free(grid->data[i]);
	}
	free(grid);
}

unsigned largest_sum(triangle* grid){
	// start at the penultimate row and move up to the second row
	for (size_t depth = grid->depth - 2; depth != (size_t) -1; depth--){
		unsigned* row_this  = grid->data[depth];
		unsigned* row_below = grid->data[depth + 1];
		// at each entry in this row
		for (size_t index = 0; index <= depth; index++){
			// find the largest of its two children in the row below
			unsigned max_descendant = max(
				row_below[index],
				row_below[index + 1]
			);
			row_this[index] += max_descendant;
		}
	}
	return grid->data[0][0];
}

int main(){
	triangle* numbers1 = load_triangle("../resource/problem18ex.grid");
	assert(largest_sum(numbers1) == 23);
	free_triangle(numbers1);
	
	triangle* numbers2 = load_triangle("../resource/problem18.grid");
	printf("%u\n", largest_sum(numbers2));
	free_triangle(numbers2);
	return 0;
}