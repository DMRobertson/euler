#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/* 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included. */

const unsigned factorial[10] = {
	1,
	1,
	1 * 2,
	1 * 2 * 3,
	1 * 2 * 3 * 4,
	1 * 2 * 3 * 4 * 5,
	1 * 2 * 3 * 4 * 5 * 6,
	1 * 2 * 3 * 4 * 5 * 6 * 7,
	1 * 2 * 3 * 4 * 5 * 6 * 7 * 8,
	1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9
};

//cf euler30.c
unsigned compute_bound(){
	/* Let f(a_1...a_n) = a_1! + ... + a_n!.
	This is at most n * 9! = 362880 * n.
	But a_1...a_n >= 10 ^ (n - 1), and eventually this will become larger than 362880 * n >= f(a_1...a_n).
	We have 10 ^ (n - 1) > 362880 * n
		iff n - 1 > log_10(362880) + log_10(n)
		iff n - log_10(n) > 1 + log_10(362880)
	
	Actually why bother with logs---we can just do it directly!
	*/
	unsigned LHS = 1;
	unsigned RHS = 0;
	do {
		LHS *= 10;
		RHS += factorial[9];
	} while (LHS <= RHS);
	return LHS;
}

bool is_digit_factorial_sum(unsigned n){
	unsigned n_original = n;
	unsigned sum = 0;
	while (n && sum <= n_original){
		unsigned digit = n % 10;
		n /= 10;
		sum += factorial[digit];
	}
	return sum == n_original;
}

unsigned sum_digit_factorial_sum(){
	unsigned sum = 0;
	unsigned end = compute_bound();
	for (unsigned n = 3; n < end; n++){
		if (is_digit_factorial_sum(n)){
			sum += n;
		}
	}
	return sum;
}


int main(){
	assert(is_digit_factorial_sum(145));
	printf("%u\n", sum_digit_factorial_sum());
	return 0;
}