#ifndef NUMBER_THEORY_
#define NUMBER_THEORY_

#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include "packed_bool_array.c"

bool equal_fractions(unsigned num_a, unsigned den_a, unsigned num_b, unsigned den_b){
	return num_a * den_b == num_b * den_a;
}

unsigned gcd(unsigned a, unsigned b){
	unsigned temp;
	while (b){
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

unsigned sum_proper_divisors(unsigned n){
	if (n <= 1){
		return 0;
	}
	//Add the 1 manually to avoid adding the pair (1, n) as part of the loop.
	unsigned sum = 1;
	unsigned limit = (unsigned) sqrt(n);
	//Only count exact sqrts once
	if (limit * limit == n){
		sum += limit;
		limit--;
	}
	
	for (unsigned i = 2; i <= limit; i++){
		if (n % i == 0){
			sum += i;
			sum += n/i;
		}
	}
	return sum;
}

bool is_prime(int n){
	if (n < 2){
		return false;
	}
	int bound = (int) sqrt( (double) n ); //casting to int takes the floor for positive doubles.
	for (int i = 2; i <= bound; i++) {
		if (n % i == 0){
			return false;
		}
	}
	return true;
}

barray* sieve_of_erastosthenes(size_t limit){
	barray* sieve = bool_array(limit);
	bsetall(sieve, -1); //unsigned -1 has a 1 in every bit
	bset(sieve, 0, false);
	bset(sieve, 1, false);
	//1. Perform the sieve.
	size_t upper_bound = ceil( sqrt( (double) limit ));
	for (size_t i = 2; i <= upper_bound; i++){
		if (bget(sieve, i)) {
			for (size_t j = i*i; j <= limit; j += i){
				bset(sieve, j, false);
			}
		}
	}
	return sieve;
};

unsigned num_distinct_primes_dividing(unsigned n){
	unsigned count = 0;
	bool divided = false;
	while (n % 2 == 0){
		n >>= 1;
		divided = true;
	}
	count += divided;
	
	unsigned divisor = 3;
	while (n > 1){
		divided = false;
		while (n % divisor == 0){
			n /= divisor;
			divided = true;
		}
		count += divided;
		divisor += 2;
	}
	
	return count;
}

#endif //NUMBER_THEORY_