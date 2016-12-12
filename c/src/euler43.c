//prepare: -lm

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "integer_maths.c"
#include "permute_digits.c"

/* The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property. */

static int primes[7] = {2, 3, 5, 7, 11, 13, 17};

bool prime_divisible_substrings(long unsigned n){
	for (size_t i = 6; i != (size_t) -1; i--){
		unsigned dividend = n % 1000;
		n /= 10;
		if (dividend % primes[i] != 0){
			return false;
		}
	}
	return true;
}

long unsigned sum_prime_divisible_subtrings_and_pandigital (unsigned max_digit){
	char* digits = calloc(max_digit + 1, sizeof(char));
	for (size_t i = 0; i <= max_digit; i++){
		digits[i] = i;
	}
	pstate* state = pnew(max_digit + 1, digits);
	free(digits);
	long unsigned sum = 0;
	while (!state->finished){
		long unsigned number = interpret(state);
		// discard the permutations which leave 0 as the first digit
		if (number > 1000000000 && prime_divisible_substrings(number)){
			long unsigned old_sum = sum;
			sum += number;
			assert(sum > old_sum);
		}
		pnext(state);
	}
	pfree(state);
	return sum;
}

int main(){
	assert(is_pandigital_zero_to(1406357289, 10, 9));
	assert(prime_divisible_substrings(1406357289));
	printf("%lu\n", sum_prime_divisible_subtrings_and_pandigital(9));
	return 0;
}