#ifndef NUMBER_THEORY_
#define NUMBER_THEORY_

#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include "packed_bool_array.c"
#include "integer_maths.c"

// Some of these functions need to compute the (ceiling or floor of) the square root of a natural number.
// We do this by casting the number to a double, computing its sqrt from math.h and then casting the ceil/floor back to an integer.
// It seems to be faster to do this when the numbers involved are signed:
// there's a hardware instruction (x87 CVTSI2SD) which does this for Singed Integers but I don't think there's anything for unsigned

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

unsigned lcm(unsigned a, unsigned b){
	return a * b / gcd(a, b);
}

unsigned long gcdl(unsigned long a, unsigned long b){
	unsigned long temp;
	while (b){
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

long unsigned lcml(long unsigned a, long unsigned b){
	return a * b / gcdl(a, b);
}

// the number theory function tau(n)
int num_divisors(int n){
	int count = 0;
	int rootish = sqrt(n);
	for (int trial = 1; trial < rootish; trial++){
		if (n % trial == 0){
			count += 2;
		}
	}
	if (rootish * rootish == n){
		count += 1;
	}
	return count;
}

// the number theory function sigma(n) - n
unsigned sum_proper_divisors(unsigned n){
	if (n <= 1){
		return 0;
	}
	//Add the 1 manually to avoid adding the pair (1, n) as part of the loop.
	unsigned sum = 1;
	unsigned limit = sqrt(n);
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
	int bound = (int) sqrt(n); //casting to int takes the floor for positive doubles.
	for (int i = 2; i <= bound; i++) {
		if (n % i == 0){
			return false;
		}
	}
	return true;
}

barray* sieve_of_erastosthenes(size_t limit){
	//The limit is inclusive: 0 <= index <= limit
	barray* sieve = bool_array(limit + 1);
	bsetall(sieve, -1); //unsigned -1 has a 1 in every bit
	bset(sieve, 0, false);
	bset(sieve, 1, false);
	//1. Perform the sieve.
	size_t upper_bound = ceil(sqrt(limit));
	for (size_t i = 2; i <= upper_bound; i++){
		if (bget(sieve, i)) {
			for (size_t j = i*i; j <= limit; j += i){
				bset(sieve, j, false);
			}
		}
	}
	return sieve;
};

size_t* gather_sieve(barray* sieve){
	size_t* primes = calloc(sieve->boollength + 1, sizeof(size_t));
	size_t count = 0;
	for (size_t candidate = 2; candidate < sieve->boollength; candidate++){
		if (bget(sieve, candidate)){
			primes[count] = candidate;
			count++;
		}
	}
	count++;
	// should be already zero thanks to calloc
	primes[count] = 0;
	primes = realloc(primes, count * sizeof(size_t));
	return primes;
}

unsigned num_distinct_primes_dividing(unsigned n, size_t* small_primes){
	unsigned count = 0;	
	size_t* divisor = small_primes;
	while (n > 1 && *divisor != 0){
		
		bool divided = false;
		while (n % *divisor == 0){
			n /= *divisor;
			divided = true;
		}
		count += divided;
		divisor++;
	}
	
	return count;
}

#endif //NUMBER_THEORY_