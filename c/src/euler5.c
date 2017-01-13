//prepare: -lm
#include <stdio.h>
#include <assert.h>
#include "number_theory.c"

/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

void swap(long unsigned* a, long unsigned* b){
	long unsigned temp = *b;
	*b = *a;
	*a = temp;
}

long unsigned lcm_one_to(unsigned limit){
	long unsigned answer = 1;
	for (unsigned i = 2; i <= limit; i++) {
		answer = lcml(answer, i);
	}
	return answer;
}

int main(){
	assert(lcm_one_to(10) == 2520);
	printf("%lu\n", lcm_one_to(20));
	return 0;
}