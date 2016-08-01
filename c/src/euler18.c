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

int max(int* a, int* b){
	return *a < *b ? *b : *a;
}

size_t triangle(size_t n){
	return (n * (n + 1))/ 2;
}

typedef struct tri_array {
	size_t width;
	size_t count;
	int* data;
} tri_array;

tri_array* new_tri_array (size_t n){
	tri_array* array = malloc(sizeof(tri_array));
	array->width = n;
	array->count = triangle(n);
	array->data  = malloc(sizeof(int) * array->count);
	return array;
}

void tprint(tri_array* numbers){
	size_t line_length = 1;
	size_t line_end = 1;
	size_t i = 0;
	while (i < numbers->count){
		printf("%02d ", numbers->data[i]);
		i++;
		if (i == line_end){
			line_length += 1;
			line_end += line_length;
			printf("\n");
		}
	}
}

int* taddr(tri_array* numbers, size_t depth, size_t index){
	// Get the number at position *index* in row number *depth*.
	// 0 <= depth < numbers->width;
	// 0 <= index <= depth
	return numbers->data + triangle(depth) + index;
}

tri_array* load_triangle (char const * filepath){
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
	
	tri_array* numbers = new_tri_array(lines);
	int* max = numbers->data + numbers->count;
	for (int* addr = numbers->data; addr < max; addr++){
		fscanf(data, "%02d", addr);
	}
	
	fclose(data);
	return numbers;
}

int largest_sum(tri_array* numbers){
	for (size_t depth = numbers->width - 1; depth > 0; depth--){
		for (size_t index = 0; index <= depth; index++){
			int max_descendant = max(
				taddr(numbers, depth, index),
				taddr(numbers, depth, index + 1)
			);
			*taddr(numbers, depth - 1, index) += max_descendant;
		}
	}
	return numbers->data[0];
}

int main(){
	tri_array* numbers1 = load_triangle("../resource/problem18ex.grid");
	assert(largest_sum(numbers1) == 23);
	free(numbers1->data);
	free(numbers1);
	
	tri_array* numbers2 = load_triangle("../resource/problem18.grid");
	printf("%d\n", largest_sum(numbers2));
	free(numbers2->data);
	free(numbers2);
	return 0;
}