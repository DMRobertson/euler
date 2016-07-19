//prepare: -lm
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
What is the 10 001st prime number?
*/

bool is_prime(int n){
	int bound = (int) sqrt( (double) n ); //casting to int takes the floor for positive doubles.
	for (int i = 2; i <= bound; i++) {
		if (n % i == 0){
			return false;
		}
	}
	return true;
}

int nth_prime(int n){
	if (n == 1){
		return 2;
	}
	int candidate = 3;
	int primes_found = 2;
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
	printf("%i\n", nth_prime(10001));
	return 0;
}