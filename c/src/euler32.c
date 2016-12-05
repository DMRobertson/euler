#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "integer_maths.c"

/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
*/

/* If a k-digit number is a product of an n-digit and m-digit number, then n+m-1 <= k <= n+m.
We have the constraint n+m+k = 9.
If n+m=k then n + m + k = 2k = 9, which has no integer solution.
So n+m-1=k; then n + m + k = 2k + 1 = 9, which means that k = 4 and n+m = 5.
We only need to look at 4-digit numbers 1000...9999 (of which there are 9000) and try to factorise them as 1 digit * 4-digit or 2-digit * 3-digit.
*/

bool has_pandigital_factorisation(unsigned target){
	for (unsigned smaller = 1; smaller < 100; smaller++){
		unsigned remainder = target % smaller;
		if (remainder != 0){
			continue;
		}
		unsigned quotient = target / smaller;
		if (quotient < 100 || quotient >= 10000){
			continue;
		}
		
		// ten bits for digits 9...0
		unsigned digits = 0b0000000000;
		record_digits(target,   10, &digits);
		record_digits(smaller,  10, &digits);
		record_digits(quotient, 10, &digits);
		// all digits except 0
		if (digits == 0b1111111110){
			return true;
		}
	}
	return false;
}

unsigned sum_9_pandigital_products(){
	unsigned sum = 0;
	for (unsigned target = 1000; target < 10000; target++){
		if (has_pandigital_factorisation(target)){
			sum += target;
		}
	}
	return sum;
}

int main(){
	assert(has_pandigital_factorisation(7254));
	printf("%d\n", sum_9_pandigital_products());
	return 0;
}