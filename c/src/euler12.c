//prepare: -lm
#include <stdio.h>
#include <math.h>
#include "number_theory.c"

/*
The sequence of triangle numbers is generated by adding the natural numbers.
So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28.
The first ten terms would be:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

Let us list the factors of the first seven triangle numbers:

 1: 1
 3: 1,3
 6: 1,2,3,6
10: 1,2,5,10
15: 1,3,5,15
21: 1,3,7,21
28: 1,2,4,7,14,28
We can see that 28 is the first triangle number to have over five divisors.

What is the value of the first triangle number to have over five hundred divisors?
*/


int main(){
	unsigned n = 0;
	unsigned divisors = 0;
	while (divisors <= 500){
		n++;
		//tau is multiplicative and n, n+1 are coprime.
		//if n is even then n/2 and n+1 are also coprime;
		//if n is odd then (n+1)/2 and n are coprime.
		if (n % 2 == 0){
			divisors = num_divisors(n / 2) * num_divisors(n + 1);
		} else {
			divisors = num_divisors(n) * num_divisors((n + 1)/2);
		}
		
		
	}
	printf("%u\n", n * (n + 1) / 2);
	return 0;
}