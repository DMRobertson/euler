#include <stdio.h>
#include <stdlib.h>

/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
	a² + b² = c²
For example, 3² + 4² = 9 + 16 = 25 = 5².

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.

See also euler39.
*/
unsigned* special_pythag_triple(){
	unsigned* output = calloc( 3, sizeof(unsigned) );
	for (unsigned c = 335; c < 1000; c++){
		for (unsigned b = 2; b < c; b++){
			unsigned a = 1000 - b - c;
			if (a >= b){
				continue;
			}
			if (a*a + b*b == c*c){
				output[0] = a;
				output[1] = b;
				output[2] = c;
				break;
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