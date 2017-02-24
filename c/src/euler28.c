#include <assert.h>
#include <stdio.h>

/* Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way? */

unsigned spiral_diagonal_sum(unsigned length){
	assert(length % 2 == 1);
	unsigned sum = 1;
	unsigned summand = 1;
	for (unsigned size = 2; size < length; size += 2){
		for (unsigned i = 1; i <= 4; i++){
			summand += size;
			sum += summand;
		}
	}
	return sum;
}

int main(){
	assert(spiral_diagonal_sum(5) == 101);
	printf("%u\n", spiral_diagonal_sum(1001));
	return 0;
}