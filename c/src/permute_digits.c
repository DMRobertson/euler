#ifndef PERMUTE_DIGITS_
#define PERMUTE_DIGITS_

#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//Steinhaus–Johnson–Trotter algorithm
//Algorithm 3 of https://doi.org/10.1145/356689.356692
typedef struct permutation_state {
	size_t length;           // N: How many things are we permuting?
	char* digits;            // P: Current permutation of the digits
	unsigned char* counters; // c: keeping track of which indices are exhausted
	bool* direction;         // d: Which direction are we moving each index in?
	bool finished;
} pstate;

// Since we're using C-style indexing (from zero) we make the transformations i -> i -1, c[i] -> c[i] - 1

pstate* pnew(const size_t length, const char* const digits){
	assert(length < UCHAR_MAX);
	pstate* state = malloc(sizeof(pstate));
	state->length = length;
	state->digits = calloc(length, sizeof(char));
	memcpy(state->digits, digits, length);
	
	state->counters = calloc(length, sizeof(unsigned char));
	state->counters[0] = (unsigned char) -1;
	for (size_t i = 1; i < length; i++){
		state->counters[i] = 0;
	}
	
	state->direction = calloc(length, sizeof(bool));
	for (size_t i = 0; i < length; i++){
		state->direction[i] = true;
	}
	state->finished = false;
	return state;
}

long unsigned interpret(pstate* state){
	long unsigned sum = 0;
	for (size_t i = 0; i < state->length; i++){
		sum *= 10;
		sum += state->digits[i];
	}
	return sum;
}

size_t largest_nonexhausted_index(pstate* state, unsigned* num_direction_switches){
	*num_direction_switches = 0; // x
	unsigned index = state->length - 1; // i
	while (state->counters[index] == index){
		if(!state->direction[index]){
			(*num_direction_switches)++;
		}
		state->direction[index] = !state->direction[index];
		state->counters[index] = 0;
		index--;
	}
	return index;
}

void pnext(pstate* state){
	// Find rightmost counter which isn't exhausted
	unsigned x;
	size_t index = largest_nonexhausted_index(state, &x);
	if (index == 0){
		state->finished = true;
		return;
	}
	
	unsigned swap_index;
	if (state->direction[index]){
		swap_index = state->counters[index] + x;
	} else {
		swap_index = index - (state->counters[index] + 1) + x;
	}
	
	// printf("swap indices %u and %u\n", swap_index, swap_index + 1);
	unsigned char temp = state->digits[swap_index];
	state->digits[swap_index] = state->digits[swap_index + 1];
	state->digits[swap_index + 1] = temp;
	
	state->counters[index]++;
}

void pdebug(pstate* state){
	printf(  "Digits:     ");
	for( size_t i = 0; i < state->length; i++){
		printf("%c", state->digits[i]);
	}
	printf("\nCounters:   ");
	for( size_t i = 0; i < state->length; i++){
		printf("%u", state->counters[i]);
	}
	printf("\nDirections: ");
	for( size_t i = 0; i < state->length; i++){
		printf("%u", state->direction[i]);
	}
	printf("\nFinished:   %s\n", state->finished ? "yes" : "no");
}

void pfree(pstate* state){
	free(state->digits);
	free(state->counters);
	free(state->direction);
	free(state);
}

#endif //PERMUTE_DIGITS_