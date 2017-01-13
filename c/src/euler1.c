#include <stdio.h>
#include <assert.h>

/* If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9.
The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/

unsigned sum_of_multiples_upto(unsigned max){
	unsigned sum = 0;
	for (unsigned i = 1; i < max; i++) {
		if (i % 3 == 0 || i % 5 == 0){
			sum += i;
		}
	}
	return sum;
}

int main(){
	assert( sum_of_multiples_upto(10) == 23 );
	printf( "%u\n", sum_of_multiples_upto(1000) );
	return 0;
}