//prepare: -lm

#include <stdio.h>
#include <assert.h>
#include "number_theory.c"
/*
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

bool is_falsely_cancellable(unsigned numerator, unsigned denominator){
	unsigned char n[2] = {numerator / 10, numerator % 10};
	unsigned char d[2] = {denominator / 10, denominator % 10};
	
	if (n[1] == 0 && d[1] == 0){
		return false;
	}
	
	for (size_t i = 0; i < 4; i++){
		size_t n_index = i % 2;
		size_t d_index = i / 2;
		if (n[n_index] == d[d_index] && equal_fractions(numerator, denominator, n[1 - n_index], d[1 - d_index])){
			return true;
		}
	}
	return false;
}

unsigned denom_prod_fc_fractions() {
	unsigned num_prod = 1;
	unsigned den_prod = 1;
	for (unsigned denominator = 10; denominator < 100; denominator++){
		for (unsigned numerator = 10; numerator < denominator; numerator++){
			if (is_falsely_cancellable(numerator, denominator)){
				num_prod *= numerator;
				den_prod *= denominator;
				
				unsigned divisor = gcd(num_prod, den_prod);
				num_prod /= divisor;
				den_prod /= divisor;
			}
		}
	}
	return den_prod;
}

int main(){
	assert(is_falsely_cancellable(49, 98));
	assert(!is_falsely_cancellable(30, 50));
	printf("%d\n", denom_prod_fc_fractions());
	return 0;
}