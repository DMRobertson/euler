#include <math.h>
#include <stdbool.h>

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
