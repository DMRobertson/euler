//prepare: -lgmp
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/

unsigned digit_sum_two_power(unsigned power){
	mpz_t result;
	mpz_init(result);
	mpz_ui_pow_ui(result, 2, power);
	char* formatted = mpz_get_str(NULL, 10, result);
	mpz_clear(result);
	
	unsigned digit_sum = 0;
	for (char* location = formatted; *location != '\0'; location++){
		digit_sum += *location - '0';
	}
	
	free(formatted);
	return digit_sum;
}

int main(){
	assert(digit_sum_two_power(15) == 26);
	printf("%u\n", digit_sum_two_power(1000));
	return 0;
}