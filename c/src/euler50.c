//prepare: -lm
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "number_theory.c"

/* The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes? */

typedef struct partial_sum {
	size_t start;
	size_t end;
	size_t sum;
} partial_sum;

size_t prime_longest_consecutive_prime_sum_below(size_t limit){
	barray* sieve = sieve_of_erastosthenes(limit);
	size_t* primes = gather_sieve(sieve);
	bfree(sieve);
	
	// start by computing the entire sum of these primes.
	size_t sum = 0;
	size_t index;
	for (index = 0; primes[index] != 0; index++){
		sum += primes[index];
	}
	size_t num_primes = index;
	partial_sum* state = malloc(sizeof(partial_sum));
	state->start = 0;
	state->end = num_primes - 1;
	state->sum = sum;
	
	free(state);
	
	

	return -1;
}

int main(){
	assert(prime_longest_consecutive_prime_sum_below(100) == 41);
	assert(prime_longest_consecutive_prime_sum_below(1000) == 953);
	printf("%zu\n", prime_longest_consecutive_prime_sum_below(1000000));
	return 0;
}