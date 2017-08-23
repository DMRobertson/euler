//prepare: -lm
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "integer_maths.c"

/* It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits. */

unsigned int highest_multiple_same_digits(unsigned int x){
	unsigned int orig_digits = 0;
	record_digits(x, 10, &orig_digits);
	unsigned int candidate = x;
	unsigned int digits;
	unsigned int i;
	for (i = 1; i < 9; i++){
		candidate += x;
		digits = 0;
		record_digits(candidate, 10, &digits);
		if (digits != orig_digits){
			break;
		}
	}
	return i;
}



int main(){
	assert(highest_multiple_same_digits(125874) >= 2);
	unsigned int x = 1;
	while (true){
		if (highest_multiple_same_digits(x) >= 6){
			printf("%u\n", x);
			break;
		}
		x++;
	}
}