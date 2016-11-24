//prepare: -lm
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "number_theory.c"

/*
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#define MAX_NOT_SUM_TWO_ABUNDANTS 28123

typedef struct sized_array {
	size_t length;
	unsigned* data;
} sized_array;

sized_array* compute_small_abundants(){
	// It would be better to use a dynamically sized array that lengthens as needed, rather than do all the work twice.
	size_t count = 0;
	for (unsigned i=1; i < MAX_NOT_SUM_TWO_ABUNDANTS; i++){
		if (sum_proper_divisors(i) > i){
			count++;
		}
	}
	sized_array* output = malloc(sizeof(sized_array));
	output->length = count;
	output->data = malloc(sizeof(unsigned) * count);
	
	count = 0;
	for (unsigned i=1; i < MAX_NOT_SUM_TWO_ABUNDANTS; i++){
		if (sum_proper_divisors(i) > i){
			output->data[count] = i;
			count++;
		}
	}
	return output;
}

barray* compute_small_abundant_sums(){
	sized_array* small_abundants = compute_small_abundants();
	barray* output = bool_array(MAX_NOT_SUM_TWO_ABUNDANTS);
	bsetall(output, 0);
	
	unsigned* end = small_abundants->data + small_abundants->length;
	for (unsigned* summand1 = small_abundants->data; summand1 < end; summand1++){
		for (unsigned* summand2 = summand1; summand2 < end; summand2++){
			size_t sum = *summand1 + *summand2;
			if (sum > MAX_NOT_SUM_TWO_ABUNDANTS){
				break;
			} else {
				bset(output, sum - 1, true);
			}
		}
	}
	
	free(small_abundants->data);
	free(small_abundants);
	return output;
}

unsigned sum_not_two_abundant_sum(){
	barray* small_abundant_sums = compute_small_abundant_sums();
	unsigned total = 0;
	for (size_t i = 1; i <= MAX_NOT_SUM_TWO_ABUNDANTS; i++){
		if (!bget(small_abundant_sums, i - 1)){
			total += i;
		}
	}
	bfree(small_abundant_sums);
	return total;
}

int main(){
	assert(sum_proper_divisors(28) == 28);
	assert(sum_proper_divisors(12) == 16);
	printf("%d\n", sum_not_two_abundant_sum());
	return 0;
}