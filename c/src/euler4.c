#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "integer_maths.c"
/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

unsigned max(unsigned a, unsigned b){
	return a < b ? b : a;
}

bool is_palindrome(unsigned N){
	unsigned len = digit_length(N, 10);
	unsigned lower = 10;
	unsigned upper = powi(10, len);
	unsigned low_digit, high_digit;
	for (unsigned i = 0; i < len / 2; i += 1){
		low_digit  = (10 * (N % lower)) / lower;
		high_digit = (10 * (N % upper)) / upper;
		if (low_digit != high_digit){
			return false;
		}
		lower *= 10;
		upper /= 10;
	}
	return true;
}

unsigned largest_palindromic_product_upto(unsigned limit){
	unsigned largest_palindrome = 0;
	for (unsigned i = 1; i < limit; i += 1){
		for (unsigned j = 1; j <= i; j += 1){
			unsigned prod = i*j;
			if (is_palindrome(prod)){
				largest_palindrome = max(prod, largest_palindrome);
			}
		}
	}
	return largest_palindrome;
}

int main(){
	assert(largest_palindromic_product_upto(100) == 9009);
	printf("%u\n", largest_palindromic_product_upto(1000));
	return 0;
}