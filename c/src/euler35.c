//prepare: -lm

#include <stdio.h>
#include "number_theory.c"
#include "integer_maths.c"

/* The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million? */

bool is_circular_prime(unsigned number){
	// assume given argument is prime
	// printf("%u, ", number);
	unsigned length = digit_length(number, 10);
	unsigned coefficient = powi(10, length - 1);
	for (unsigned i = 1; i < length; i++){
		unsigned digit = number % 10;
		number /= 10;
		number += digit * coefficient;
		// printf("%u, ", number);
		if (!is_prime(number)){
			return false;
		}
	}
	return true;
}

size_t circlular_primes_under(size_t limit){
	if (limit < 2){
		return 0;
	}
	barray* primes = sieve_of_erastosthenes(limit);
	size_t count = 1; // 2 is a circular prime
	for (size_t index = 3; index <= limit; index += 2){
		// todo: if index is a circular prime then we can add it, and all of its cyclic permutations to the sum
		// then bset(primes, permutation, false) to skip over them later)
		// warning: may be repeats e.g. with 11
		if (bget(primes, index) && is_circular_prime(index)){
			count++;
		}
	}
	bfree(primes);
	return count;
}

int main(){
	assert(digit_length(197, 10) == 3);
	assert(is_circular_prime(197));
	assert(circlular_primes_under(100) == 13);
	printf("\n%lu\n", circlular_primes_under(1000000));
	return 0;
}