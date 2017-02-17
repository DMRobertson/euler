//prepare: -lgmp -lm
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include "integer_maths.c"
/*
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
*/

#define DIGITS 50
#define NUMBERS 100

char** read_digits(char const* filepath){
	char** nums = calloc(NUMBERS, sizeof(char*));
	for (size_t i = 0; i < NUMBERS; i++){
		nums[i] = calloc(DIGITS + 1, sizeof(char));
	}
	FILE* data = fopen(filepath, "r");
	for (size_t i = 0; i < NUMBERS; i++){
		fscanf(data, "%s\n", nums[i]);
	}
	fclose(data);
	return nums;
}

void sum_digits(mpz_t sum, char** nums){
	mpz_t summand;
	mpz_init(summand);
	
	for (size_t index = 0; index < NUMBERS; index++){
		mpz_set_str(summand, nums[index], 10);
		mpz_add(sum, sum, summand);
	}
	mpz_clear(summand);
}

int main(){
	char** numbers = read_digits("../resource/problem13.numbers");
	mpz_t sum;
	mpz_init(sum);
	sum_digits(sum, numbers);
	for (size_t index = 0; index < NUMBERS; index++){ 
		free(numbers[index]);
	}
	free(numbers);
	
	//This doesn't feel like the cleanest way of getting the top ten numbers.
	const size_t sum_digits = DIGITS + digit_length(NUMBERS, 10);
	char* buffer = calloc(sum_digits + 1, sizeof(char));
	gmp_snprintf(buffer, 11, "%Zd", sum);
	mpz_clear(sum);
	
	buffer[10] = '\0';
	printf("%s\n", buffer);
	return 0;
}