//prepare: -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "number_theory.c"

/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

size_t sum_sieve_of_erastosthenes(size_t limit){
	barray* primes = sieve_of_erastosthenes(limit);
	//2. Add up the primes we found.
	size_t sum = 0;
	for (size_t i = 2; i <= limit; i++){
		if (bget(primes, i)) {
			sum += i;
		}
	}
	bfree(primes);
	return sum;
}

int main(){
	assert(sum_sieve_of_erastosthenes(10) == 17);
	printf("%li\n", sum_sieve_of_erastosthenes(2000000));
	return 0;
}
