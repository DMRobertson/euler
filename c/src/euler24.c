#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* 
A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*/

unsigned factorial (unsigned n){
	unsigned output = 1;
	for (unsigned i = 2; i <= n; i++){
		output *= i;
	}
	return output;
}

typedef struct alphabet {
	size_t size;
	char* letters;
} alphabet;

void discard_letter(char* letters, size_t discard, size_t size){
	// turn an array A1, ..., A_{discard}, ..., A_{size} into
	// A1, ..., A_{discard - 1}, A_{discard+1} ..., A_{size}, A_{size}
	for (size_t index = discard; index < size; index++){
		letters[index] = letters[index+1];
	}
}

alphabet* zero_to(size_t num){
	assert( 0 < num && num < 10);
	alphabet* out = malloc(sizeof(alphabet));
	out->size = num + 1;
	out->letters = malloc(sizeof(char) * num);
	for (size_t i=0; i <= num; i++){
		out->letters[i] = '0' + i;
	}
	return out;
}

char* nth_permutation(alphabet* alphabet, unsigned number){
	//first perm has index zero
	//local copy of alphabet data
	size_t size = alphabet->size;
	char* letters = malloc(sizeof(char) * (alphabet->size));
	memcpy(letters, alphabet->letters, alphabet->size);
	
	char* output = malloc(sizeof(char) * (alphabet->size + 1));
	
	unsigned fact = factorial(size);
	for (size_t i = size; i > 0; i--){
		fact /= i;
		size_t index = number / fact;
		output[size - i] = letters[index];
		discard_letter(letters, index, size);
		number %= fact;
	}
	
	//null-terminate
	output[size] = 0;
	return output;
}

char expected[6][4] = {
	"012",
	"021",
	"102",
	"120",
	"201",
	"210",
};

int main(){
	alphabet* alpha1 = zero_to(2);
	for (unsigned i = 0; i < 6; i++){
		char* perm = nth_permutation(alpha1, i);
		assert(strcmp(perm, expected[i]) == 0);
		free(perm);
	}
	free(alpha1->letters);
	free(alpha1);
	
	alphabet* alphabet = zero_to(9);
	char* perm = nth_permutation(alphabet, 999999);
	printf("%s\n", perm);
	free(perm);
	free(alphabet->letters);
	free(alphabet);
	return 0;
}