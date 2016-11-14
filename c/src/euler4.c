#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "integer_powers.c"
/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

int max(int a, int b){
	return a < b ? b : a;
}

int num_digits(int N){
	int digits = 1;
	int comparison = 10;
	while (N >= comparison){
		digits += 1;
		comparison *= 10;
	}
	return digits;
}

bool is_palindrome(int N){
	int len = num_digits(N);
	int lower = 10;
	int upper = ipow(10, len);
	int low_digit, high_digit;
	for (int i = 0; i < len / 2; i += 1){
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

int largest_palindromic_product_upto(int limit){
	int prod;
	int largest_palindrome = 0;
	for (int i = 1; i < limit; i += 1){
		for (int j = 1; j <= i; j += 1){
			prod = i*j;
			if (is_palindrome(prod)){
				largest_palindrome = max(prod, largest_palindrome);
			}
		}
	}
	return largest_palindrome;
}

int main(){
	assert(largest_palindromic_product_upto(100) == 9009);
	printf("%i\n", largest_palindromic_product_upto(1000));
	return 0;
}