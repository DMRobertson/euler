//prepare: -lm
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "vector.c"
#include "number_theory.c"

/*
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#define MAX_NOT_SUM_TWO_ABUNDANTS 28123

vector* compute_small_abundants(){
	vector* output = vnew(10);
	for (size_t i=1; i < MAX_NOT_SUM_TWO_ABUNDANTS; i++){
		if (sum_proper_divisors(i) > i){
			vpush(output, i);
		}
	}
	return output;
}

barray* compute_small_abundant_sums(){
	vector* small_abundants = compute_small_abundants();
	barray* output = bool_array(MAX_NOT_SUM_TWO_ABUNDANTS);
	bsetall(output, 0);
	
	const size_t end = small_abundants->length;
	for (size_t index1 = 0; index1 < end; index1++){
		size_t summand1 = vget(small_abundants, index1);
		for (size_t index2 = index1; index2 < end; index2++){
			size_t sum = summand1 + vget(small_abundants, index2);
			if (sum > MAX_NOT_SUM_TWO_ABUNDANTS){
				break;
			} else {
				bset(output, sum, true);
			}
		}
	}
	vfree(small_abundants);
	return output;
}

size_t sum_not_two_abundant_sum(){
	barray* small_abundant_sums = compute_small_abundant_sums();
	size_t total = 0;
	for (size_t i = 1; i <= MAX_NOT_SUM_TWO_ABUNDANTS; i++){
		if (!bget(small_abundant_sums, i)){
			total += i;
		}
	}
	bfree(small_abundant_sums);
	return total;
}

int main(){
	assert(sum_proper_divisors(28) == 28);
	assert(sum_proper_divisors(12) == 16);
	printf("%lu\n", sum_not_two_abundant_sum());
	return 0;
}