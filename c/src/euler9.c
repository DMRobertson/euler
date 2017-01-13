#include <stdio.h>
#include <stdlib.h>

/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
	a² + b² = c²
For example, 3² + 4² = 9 + 16 = 25 = 5².

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/
unsigned* special_pythag_triple(){
	unsigned* output = malloc( 3 * sizeof(unsigned) );
	for (unsigned c = 1; c < 1000; c++){
		for (unsigned b = 1; b < c; b++){
			for (unsigned a = 1; a < b; a++){
				if (a*a + b*b == c*c && a + b + c == 1000){
					output[0] = a;
					output[1] = b;
					output[2] = c;
					break;
				}
			}
		}
	}
	return output;
}

int main(){
	unsigned* triple = special_pythag_triple();
	printf( "%u\n", triple[0] * triple[1] * triple[2] );
	free(triple);
	return 0;
}