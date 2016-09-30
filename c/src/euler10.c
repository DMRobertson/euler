//prepare: -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "packed_bool_array.c"

/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

size_t sum_sieve_of_erastosthenes(size_t limit){
	barray* sieve = bool_array(limit);
	bsetall(sieve, -1); //unsigned -1 has a 1 in every bit
	//1. Perform the sieve.
	size_t upper_bound = ceil( sqrt( (double) limit ));
	for (size_t i = 2; i <= upper_bound; i++){
		if (bget(sieve, i - 2)) {
			for (size_t j = i*i; j <= limit; j += i){
				bset(sieve, j - 2, false);
			}
		}
	}
	//2. Add up the primes we found.
	size_t sum = 0;
	for (size_t i = 2; i <= limit; i++){
		if (bget(sieve, i - 2)) {
			sum += i;
		}
	}
	
	free(sieve->array);
	free(sieve);
	return sum;
}

int main(){
	assert(sum_sieve_of_erastosthenes(10) == 17);
	printf("%li\n", sum_sieve_of_erastosthenes(2000000));
	return 0;
}
