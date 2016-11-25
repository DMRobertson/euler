//prepare: -lm

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "integer_maths.c"

/* The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.) */

bool is_palindrome_in_base(unsigned number, unsigned base){
	assert(base > 1);
	unsigned length = digit_length(number, base);
	unsigned char* digits = malloc(sizeof(unsigned char) * length);
	for (size_t index = 0; index < length; index++){
		digits[index] = number % base;
		number /= base;
	}
	
	for (size_t index = 0; index < length / 2; index++){
		if (digits[index] != digits[length - index - 1]){
			return false;
		}
	}
	return true;
}

unsigned sum_double_palindromes_under(unsigned limit){
	unsigned sum = 0;
	for (unsigned number = 1; number < limit; number++){
		if (is_palindrome_in_base(number, 10) && is_palindrome_in_base(number, 2)){
			sum += number;
		}
	}
	return sum;
}

int main(){
	assert(is_palindrome_in_base(585, 10));
	assert(is_palindrome_in_base(585, 2));
	printf("%u\n",sum_double_palindromes_under(1000000));
	return 0;
}