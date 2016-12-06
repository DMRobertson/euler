#include <stdio.h>
#include <stdio.h>
#include <assert.h>
#include "integer_maths.c"

/* If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised? */



unsigned pythagorean_triples_with_sum(const unsigned target){
	unsigned count = 0;
	// 0 < a < b < c < p and a + b + c = p
	// Smallest c can be is when c = b + 1 and b = a + 1,
	// in which case a + b + c = (c - 2) + (c - 1) + c = 3c - 3 = p; so c >= (p + 3) / 3
	// Largest c can be is when a = 1 and b = 2, so c = p - 3
	for (unsigned c = ceildiv(target + 3, 3); c <= target - 3; c++){
		const unsigned c_squared = c * c;
		// 0 < a < b and a + b = p - c
		// Smallest b can be is when b = a + 1,
		// in which case a + b = 2b - 1 = p - c; so b >= (p - c + 1) / 2
		// Largest b can be is when a = 1, so b = p - c - 1.
		for (unsigned b = ceildiv(target - c + 1, 2); b < target - c - 1; b++){
			unsigned a = target - b - c;
			if (a*a + b*b == c_squared){
				count++;
			}
		}
	}
	return count;
}

unsigned most_common_pythag_triple_sum_upto(unsigned limit){
	unsigned max_num_triples = 0;
	unsigned index;
	for (unsigned p = 6; p <= limit; p++){
		unsigned count = pythagorean_triples_with_sum(p);
		if (count > max_num_triples){
			max_num_triples = count;
			index = p;
		}
	}
	return index;
}

int main(){
	assert(pythagorean_triples_with_sum(120) == 3);
	printf("%u\n", most_common_pythag_triple_sum_upto(1000));
	return 0;
}