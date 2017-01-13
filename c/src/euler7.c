//prepare: -lm
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "number_theory.c"

/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
What is the 10 001st prime number?
*/

unsigned nth_prime(unsigned n){
	if (n == 1){
		return 2;
	}
	unsigned candidate = 3;
	unsigned primes_found = 2;
	while (primes_found < n){
		candidate += 2;
		if (is_prime(candidate)){
			primes_found += 1;
		}
	}
	return candidate;
}

int main(){
	assert(nth_prime(6) == 13);
	printf("%u\n", nth_prime(10001));
	return 0;
}