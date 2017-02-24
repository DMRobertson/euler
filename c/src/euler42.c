#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "compare.c"

/* The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words? */

//CF problem 22
unsigned* first_n_triangle_numbers(const size_t count){
	unsigned sum = 0;
	unsigned diff = 1;
	unsigned* out = calloc(count, sizeof(unsigned));
	for (size_t i = 0; i < count; i++){
		sum += diff;
		out[i] = sum;
		diff++;
	}
	return out;
}

unsigned count_triangle_words_in(char* filepath){
	FILE* file = fopen(filepath, "r");	
	unsigned* triangle_numbers = first_n_triangle_numbers(26);
	unsigned count = 0;
	unsigned score = 0;
	int c;
	while (true){
		c = fgetc(file);
		if (c == '"'){
			continue;
		}
		if (c == ',' || c == EOF){
			//Don't count the quote characters
			void* pointer = bsearch(&score, triangle_numbers, 26, sizeof(unsigned), cmp_unsigned);
			if (pointer != NULL){
				// we have a triangle number
				count++;
			}
			score = 0;
		} else {
			int index = c - ('A' - 1);
			assert(1 <= index && index <= 26);
			score += index;
		}
		if (c == EOF){
			break;
		}
	}
	free(triangle_numbers);
	fclose(file);
	return count;
}

int main(){
	printf("%u\n", count_triangle_words_in("../resource/problem42.words"));
	return 0;
}