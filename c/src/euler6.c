#include <stdio.h>
#include <assert.h>

/*
The sum of the squares of the first ten natural numbers is
	1² + 2² + ... + 10² = 385
The square of the sum of the first ten natural numbers is,
	(1 + 2 + ... + 10)² = 55² = 3025
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

unsigned square_sum_one_upto(unsigned limit){
	unsigned sum = 0;
	for (unsigned i = 1; i <= limit; i++){
		sum += i;
	}
	return sum * sum;
}

int sum_squares_upto(unsigned limit){
	unsigned sum = 0;
	for (unsigned i = 1; i <= limit; i++){
		sum += i * i;
	}
	return sum;
}

int main(){
	assert(sum_squares_upto(10) == 385);
	assert(square_sum_one_upto(10) == 3025);
	unsigned answer = square_sum_one_upto(100) - sum_squares_upto(100);
	printf("%u\n", answer);
	return 0;
}