//prepare: -lm
#include <stdio.h>
#include <assert.h>
#include "number_theory.c"
#include "permute_digits.c"

/* We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists? */

// sieve of erasthosthenese, then filter downwards for pandigitals -> 33sec
// search for pandigital downwards then test primality -> 50 sec
// time python -c "from itertools import permutations; list(permutations(range(1, 10)))" takes 0.102sec

unsigned largest_n_pandigital_prime(size_t num_digits){
	assert(0 < num_digits && num_digits < 10);
	char* digits = calloc(num_digits, sizeof(char));
	for (size_t i = 0; i < num_digits; i++){
		digits[i] = i + 1;
	}
	
	//what we really want to do is iterate over the permutations of 1....9 in reverse lexicographic order. Would be slightly more efficient!
	
	pstate* state = pnew(num_digits, digits);
	free(digits);
	unsigned max = 0;
	while (!state->finished){
		unsigned number = interpret(state);
		if (number > max && is_prime(number)){
			max = number;
		}
		pnext(state);
	}
	pfree(state);
	return max;
}

int main(){
	assert(is_prime(2143) && is_pandigital(2143, 10));
	unsigned result;
	for (size_t n = 9; n > 1; n--){
		result = largest_n_pandigital_prime(n);
		if (result != 0){
			break;
		}
	}
	printf("%u\n", result);
	return 0;
}