#include <stdio.h>
#include <assert.h>

/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

void swap(long int* a, long int* b){
	long int temp = *b;
	*b = *a;
	*a = temp;
}

long int gcd(long int a, long int b){
	if (b < a){
		swap(&a, &b);
	} else if (a == b){
		return a;
	}
	long int last_rem = a;
	long int rem = a;
	do {
		last_rem = rem;
		rem = b % a;
		b = a;
		a = rem;
	} while (rem > 0);
	return last_rem;
}

long int lcm(long int a, long int b){
	return a * b / gcd(a, b);
}

long int lcm_one_to(int limit){
	long int answer = 1;
	for (int i = 2; i <= limit; i++) {
		answer = lcm(answer, i);
	}
	return answer;
}

int main(){
	assert(lcm_one_to(10) == 2520);
	printf("%li\n", lcm_one_to(20));
	return 0;
}