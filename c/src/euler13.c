//prepare: -lgmp -lm
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

/*
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
*/

#define DIGITS 50
#define NUMBERS 100
#define NUM_CHARS ((DIGITS + 1) * NUMBERS)

size_t decimal_digits(size_t x){
	return ceil(log(x)/log(10));
}

char* read_digits(char const* filepath){
	char* nums = malloc( sizeof(char) * NUM_CHARS);
	FILE* data = fopen(filepath, "r");
	
	char* loc;
	char* lim;
	for (loc=nums, lim=loc + NUM_CHARS; loc < lim; loc += DIGITS + 1){
		fscanf(data, "%s\n", loc);
	}
	fclose(data);
	return nums;
}

void sum_digits(mpz_t* sum, char* nums){
	mpz_t summand;
	mpz_init(summand);
	
	char* loc;
	char* lim;
	for (loc=nums, lim=loc + NUM_CHARS; loc < lim; loc += DIGITS + 1){
		mpz_set_str(summand, loc, 10);
		mpz_add(*sum, *sum, summand);
	}
}

int main(){
	char* numbers = read_digits("../resource/problem13.numbers");
	mpz_t sum;
	mpz_init(sum);
	sum_digits(&sum, numbers);
	free(numbers);
	
	const size_t sum_digits = DIGITS + decimal_digits(NUMBERS);
	char* buffer = malloc(sizeof (char) * (sum_digits + 1));
	gmp_sprintf(buffer, "%Zd", sum);
	printf("%.10s\n", buffer);
	mpz_clear(sum);
	
	return 0;
}