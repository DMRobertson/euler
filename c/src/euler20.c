//prepare: -lgmp
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>

/* n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100! */

unsigned digit_sum_fact(unsigned long n){
	mpz_t result;
	mpz_init(result);
	mpz_fac_ui(result, n);
	char* formatted = mpz_get_str(NULL, 10, result);
	mpz_clear(result);
	
	unsigned sum = 0;
	for (char* digit = formatted; *digit != '\0'; digit++){
		sum += *digit - '0';
	}
	free(formatted);
	return sum;
}

int main(){
	assert(digit_sum_fact(10) == 27);
	printf("%u\n", digit_sum_fact(100));
}