//prepare: -lm

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "number_theory.c"

/* The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?

*/

unsigned first_number_conseq_number_primes_dividing(
	unsigned n, size_t* small_primes
){
	unsigned candidate = 2;
	unsigned i;
	while (true){
		for (i = 0; i < n; i++){
			if (num_distinct_primes_dividing(candidate + i, small_primes) != n){
				break;
			}
		}
		if (i == n){
			return candidate;
		} else {
			candidate += i + 1;
		}
	}
}

int main(){
	barray* sieve = sieve_of_erastosthenes(1000);
	size_t* small_primes = gather_sieve(sieve);
	bfree(sieve);
	
	assert(first_number_conseq_number_primes_dividing(2, small_primes) == 14);
	assert(first_number_conseq_number_primes_dividing(3, small_primes) == 644);
	printf("%u\n", first_number_conseq_number_primes_dividing(4, small_primes));
	
	free(small_primes);
	return 0;
}