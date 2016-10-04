//prepare: -lm -lgmp
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <gmp.h>
/*
The Fibonacci sequence is defined by the recurrence relation:

Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
Hence the first 12 terms will be:
	1 1 2 3 5 8 13 21 34 55 89 144
The 12th term, F12, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
*/

unsigned index_first_fib_with_digits(unsigned digits){
	mpz_t next, previous, current, target;
	// first n-digit int in base 10 is 10**(n-1)
	// worst case scenario: fib sequence generates 10**(n-1) - 1, 
	// the largest (n-1) digit number in base 10.
	// then the next term sequence is at most twice this, requiring one extra bit. 
	mp_bitcnt_t required_bits = ceil(digits * log2(10));
	mpz_init2(next,     required_bits);
	mpz_init2(previous, required_bits);
	mpz_init2(current,  required_bits);
	mpz_init2(target,   required_bits);
	
	mpz_set_ui(previous, 1);
	mpz_set_ui(current, 1);
	mpz_ui_pow_ui(target, 10, digits - 1);
	
	unsigned index;
	for (index = 2; mpz_cmp(current, target) < 0; index++ ){
		mpz_add(next, previous, current);
		mpz_swap(previous, current);
		mpz_swap(current, next);
	}
	return index;
}

int main(){
	assert( index_first_fib_with_digits(3) == 12 );
	printf("%u\n", index_first_fib_with_digits(1000));
	return 0;
}