//prepare: -lm
#include <stdio.h>
#include <stdbool.h>
#include "integer_maths.c"
#include "number_theory.c"

/* The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes. */

bool is_bitruncatable_prime(unsigned number){
	for (unsigned right_truncated = number; right_truncated > 0; right_truncated /= 10){
		if (!is_prime(right_truncated)){
			return false;
		}
	}
	
	unsigned left_truncated = number;
	unsigned modulus = largest_power_below(number, 10);
	while (modulus > 0){
		if (!is_prime(left_truncated)){
			return false;
		}
		left_truncated %= modulus;
		modulus /= 10;
	}
	return true;
}

unsigned sum_bitruncatable_primes(){
	unsigned sum = 0;
	unsigned matches = 0;
	for (unsigned candidate = 11; matches < 11; candidate += 2){
		if (is_bitruncatable_prime(candidate)){
			matches++;
			sum += candidate;
		}
	} 
	return sum;
}

int main(){
	assert(is_bitruncatable_prime(3797));
	assert(!is_bitruncatable_prime(29));
	printf("%u\n", sum_bitruncatable_primes());
	return 0;
}
