#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

bool divide_out(long int *N, long int divisor){
	bool reduced = false;
	while (*N % divisor == 0){
		*N /= divisor;
		reduced = true;
	}
	return reduced;
}

long int largest_prime_factor(long int N){
	long int largest_prime;
	long int divisor = 3;
	bool reduced;
	assert(N > 1);
	
	reduced = divide_out(&N, 2);
	if (reduced){ largest_prime = 2; }
	
	while (N > 1){
		reduced = divide_out(&N, divisor);
		if (reduced){ largest_prime = divisor; }
		divisor += 2;
	}
	
	return largest_prime;
}

int main(){
	assert( largest_prime_factor(13195) == 29 );
	printf( "%li\n", largest_prime_factor(600851475143) );
	return 0;
}