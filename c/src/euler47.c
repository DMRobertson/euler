//prepare: -lm
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "number_theory.c"

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
	barray* sieve = sieve_of_erastosthenes(sqrt(UINT_MAX));
	vector* small_primes = bgather(sieve);
	vpush(small_primes, 0);
	
	assert(first_number_conseq_number_primes_dividing(2, small_primes->data) == 14);
	assert(first_number_conseq_number_primes_dividing(3, small_primes->data) == 644);
	printf("%u\n", first_number_conseq_number_primes_dividing(4, small_primes->data));
	
	bfree(sieve);
	vfree(small_primes);
	return 0;
}