//prepare: -lm
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "number_theory.c"

/* It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×12
15 = 7 + 2×22
21 = 3 + 2×32
25 = 7 + 2×32
27 = 19 + 2×22
33 = 31 + 2×12

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square? */

bool satisfies_conjecture(const unsigned n){
	if (is_prime(n)){
		return true;
	}
	for (unsigned root = 1; root < (unsigned) sqrt(n); root++){
		if (is_prime(n - 2 * root * root)){
			return true;
		}
	}
	return false;
}

int main(){
	assert(satisfies_conjecture(9));
	assert(satisfies_conjecture(15));
	assert(satisfies_conjecture(21));
	assert(satisfies_conjecture(25));
	assert(satisfies_conjecture(27));
	assert(satisfies_conjecture(33));
	unsigned candidate = 9;
	while (true){
		if (!satisfies_conjecture(candidate)){
			break;
		}
		candidate += 2;
	}
	printf("%u\n", candidate);
	return 0;
}