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

size_t prime_longest_consecutive_prime_sum_below(size_t limit){
	barray* sieve = sieve_of_erastosthenes(limit);
	size_t* primes = gather_sieve(sieve);
	bfree(sieve);
	
	// 1. Compute the largest sum p_1 + p_2 + ... + p_n which is below the limit.
	size_t initial_sum = 0;
	size_t index;
	for (index = 0; primes[index] != 0; index++){
		if (initial_sum + primes[index] >= limit){
			break;
		};
		initial_sum += primes[index];
	}
	// If we add in another prime we'll bust the limit.
	size_t max_summands = index;
	// Keep going to count the numbre of primes in total.
	while (primes[index] != 0){
		index++;
	}
	size_t num_primes = index;
	
	// 2. We're going to loop over the possible consecutive sums with num_summands terms in increasing order.
	size_t output = 0;
	for (size_t num_summands = max_summands; num_summands > 0; num_summands--){
		// Start with p_1 + ... + p_{num_summands}
		size_t sum = initial_sum;
		for (size_t start = 0; start <= num_primes - num_summands; start++){
			size_t end = start + num_summands;
			// Is sum a prime?
			if ( bsearch(&sum, primes, num_primes, sizeof(size_t), cmp_size_t ) != NULL) {
				output = sum;
				goto end;
			}
			// If not, swap out the first prime and add on the next prime to the end.
			sum -= primes[start];
			// primes is null-terminated, so no problem when end == num_primes.
			sum += primes[end];
			// This will only increase the sum. If we've breached the limit, try fewer summands.
			if (sum >= limit){
				break;
			}
		}
		initial_sum -= primes[num_summands - 1];
	}
	end:
	free(primes);
	return output;
}

int main(){
	assert(prime_longest_consecutive_prime_sum_below(100) == 41);
	assert(prime_longest_consecutive_prime_sum_below(1000) == 953);
	printf("%zu\n", prime_longest_consecutive_prime_sum_below(1000000));
	return 0;
}