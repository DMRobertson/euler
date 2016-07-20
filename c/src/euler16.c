//prepare: -lgmp
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gmp.h>

/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/

int digit_sum_two_power(unsigned long int power){
	mpz_t result;
	mpz_init(result);
	mpz_ui_pow_ui(result, 2, power);
	
	size_t length = mpz_sizeinbase(result, 2);
	char* formatted = malloc(sizeof(char) * (length + 1));
	gmp_sprintf(formatted, "%Zd", result);
	
	int digit_sum = 0;
	char c = 1;
	char* location = formatted;
	while (*location != '\0'){
		c = *location - '0';
		digit_sum += c;
		location++;
	}
	
	free(formatted);
	return digit_sum;
}

int main(){
	assert(digit_sum_two_power(15) == 26);
	printf("%d\n", digit_sum_two_power(1000));
	return 0;
}