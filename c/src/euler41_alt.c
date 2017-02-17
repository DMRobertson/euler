//prepare: -lm
#include <stdio.h>
#include <assert.h>
#include "number_theory.c"

/* We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists? */

unsigned largest_pandigital_prime(){
	size_t candidate;
	barray* sieve = sieve_of_erastosthenes(999999999);
	// printf("computed sieve\n");
	for (candidate = 999999999; !(is_pandigital(candidate, 10) && is_prime(candidate)); candidate -= 2);
	// really want a way of enumerating S_9 here (362880 = 0.36 million as opposed to all numbers between 123456789 and 987654321 = 864197533 options
	bfree(sieve);
	return candidate;
}

// sieve then filter for pandigitals -> 33sec
// search for pandigital then test primality -> 50 sec
// time python -c "from itertools import permutations; list(permutations(range(1, 10)))" tales 0.102sec

int main(){
	assert(is_prime(2143) && is_pandigital(2143, 10));
	printf("%u\n", largest_pandigital_prime());
	return 0;
}