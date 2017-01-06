//prepare: -lm
#include <stdio.h>
#include <stdlib.h>
#include "number_theory.c"
#include "integer_maths.c"

/* The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways:
	(i) each of the three terms are prime, and,
	(ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence? */

int main(){
	barray* sieve = sieve_of_erastosthenes(9999);
	size_t base, next, last;
	for (base = 1489; base < 9999; base++){
		if (!bget(sieve, base)){
			continue;
		}
		for (size_t step = 2; base + 2*step <= 9999; step += 2){
			next = base + step;
			last = next + step;
			if ( !bget(sieve, next) || !bget(sieve, last) ){
				continue;
			}
			unsigned char* base_digits = count_digits(base, 10);
			unsigned char* next_digits = count_digits(next, 10);
			if ( !equal_digit_counts(base_digits, next_digits, 10) ){
				continue;
			}
			unsigned char* last_digits = count_digits(last, 10);
			if ( !equal_digit_counts(base_digits, last_digits, 10) ){
				continue;
			}
			goto end;
		}
	}
	end:
	printf("%zu%zu%zu\n", base, next, last);
	free(sieve);
	return 0;
}