//prepare: -lm
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "vector.c"
#include "number_theory.c"

/* By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family. */

unsigned int count_primes_after_digit_replacement(
	size_t candidate, unsigned char pattern
){
	// 1. Compute the base value: as if all stars were set equal to zero.
	//    Compute the delta value: as if all stars were set to one, and all non-stars to zero.
	
	unsigned int length = digit_length(candidate, 10);
	unsigned char mask = 1;
	unsigned int base = 0;
	unsigned int delta = 0;
	unsigned int position = 1;
	bool replaceable;
	for (size_t i = 0; i < length; i++){
		replaceable = pattern & mask;
		if (!replaceable){
			unsigned int digit = candidate % 10;
			base += position * digit;
		} else {
			delta += position;
		}
		mask *= 2;
		position *= 10;
		candidate /= 10;
	}
	
	//is the leftmost digit replaceable?
	unsigned int digit;
	if (!replaceable){
		candidate = base;
		digit = 0;
	} else {
		candidate = base + delta;
		digit = 1;
	}
	
	unsigned int primes_found = 0;
	do {
		if (is_prime(candidate)){
			primes_found++;
		}
		candidate += delta;
		digit++;
	} while (digit <= 9);
	
	return primes_found;
}

bool has_same_digits_at(size_t prime, unsigned char pattern){
	unsigned char length = digit_length(prime, 10);
	unsigned char digit = 10;
	for (unsigned char i = 0; i < length; i++){
		if (pattern % 2){
			unsigned char next = prime % 10;
			if (digit == 10){
				digit = next;
			} else if (digit != next) {
				return false;
			}
		}
		prime /= 10;
		pattern >>= 1;
	}
	
	return digit != 10;
}

size_t smallest_prime_digit_replacement_family(
	const unsigned int family_size, vector* primes
){
	size_t index = 0;
	while (true){
		// Ensure we have the next prime
		while (!(index < primes->length)){
			next_prime(primes);
		}
		size_t prime = vget(primes, index);
		unsigned char length = digit_length(prime, 10);
		unsigned char max_pattern = 1 << length;
		for (unsigned char pattern = 1; pattern != max_pattern; pattern++){
			// TODO: looking for a prime which is part of the family, so only select patterns where the digits are the same
			if (!has_same_digits_at(prime, pattern)){
				continue;
			}
			unsigned int found = count_primes_after_digit_replacement(prime, pattern);
			if (found >= family_size){
				return prime;
			}
		}
		index++;
	}
}


int main(){
	vector* primes = vnew(10);
	assert(count_primes_after_digit_replacement(13,
		                                      0b10) == 6);
	assert(count_primes_after_digit_replacement(56003,
		                                      0b00110) == 7);
	assert(smallest_prime_digit_replacement_family(6, primes) == 13);
	assert(smallest_prime_digit_replacement_family(7, primes) == 56003);
	// Slower than I would like
	printf("%zu\n", smallest_prime_digit_replacement_family(8, primes));
	vfree(primes);
	return 0;
}