//prepare: -lm

#include <stdio.h>
#include <assert.h>
#include "number_theory.c"

/*
Euler discovered the remarkable quadratic formula:
	n^2 + n + 41
It turns out that the formula will produce 40 primes for the consecutive integer values 0 ≤ n ≤ 39. However, when n=40,
	40^2 + 40 + 41 = 40(40 + 1) + 41n
is divisible by 41, and certainly when n = 41,
	41^2 + 41 +41
is clearly divisible by 41.

The incredible formula
	n^22 −79n + 1601
was discovered, which produces 80 primes for the consecutive values 0 ≤ n ≤ 79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:
	n^2 + an + b
where |a| < 1000 and |b| ≤ 1000, find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n=0.
*/

unsigned count_primes_quadratic(int linear, int constant){
	unsigned n = -1;
	int result;
	do {
		n++;
		result = n*n + linear*n + constant;
	} while (is_prime(result));
	return n;
}

int main(){
	assert(count_primes_quadratic(1, 41) == 40);
	assert(count_primes_quadratic(-79, 1601) == 80);
	assert(count_primes_quadratic(0, 0) == 0);
	
	unsigned max_primes_produced = 0;
	int max_producing_a = -2000;
	int max_producing_b = -2000;
	for (int a = -999; a <= 999; a++){
		for (int b = -1000; b <= 1000; b++){
			if (!is_prime(b)){
				//first term (n=0) will be just b
				continue;
			}
			unsigned primes_produced = count_primes_quadratic(a, b);
			if (primes_produced > max_primes_produced){
				max_primes_produced = primes_produced;
				max_producing_a = a;
				max_producing_b = b;
			}
		}
	}
	printf("%d\n", max_producing_a * max_producing_b);
	return 0;
}