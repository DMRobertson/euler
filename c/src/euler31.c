#include <stdio.h>
#include <stdlib.h>

/* In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins? */

typedef struct state state;
struct state {
	unsigned remaining;       // How many pence to we have to find?
	size_t largest_avail_idx; // What's the index of the largest denomination we're allowed to use to make up the remaining change? 
	state* previous;          // Previous stack element
};

state* next(state* current, unsigned* weights){
	// Can we use the largest possible denomination?
	if (current->remaining >= weights[current->largest_avail_idx]){
		state* next_state = malloc(sizeof(state));
		next_state->remaining = current->remaining - weights[current->largest_avail_idx];
		next_state->largest_avail_idx = current->largest_avail_idx;
		next_state->previous = current;
		return next_state;
	}
	
	if (current->remaining == 0){
		//Don't try to make 0p using ...2p, 1p.
		current->largest_avail_idx = 0;
	} else if (current->largest_avail_idx == 0){
		current->remaining = 0;
		return current;
	}
	state* next_state = current;
	// Go up the tree until we find somewhere we can try a smaller denomination
	while ( next_state != NULL && next_state->largest_avail_idx == 0 ){
		state* popped_state = next_state;
		next_state = next_state->previous;
		free(popped_state);
	}
	if (next_state != NULL){
		next_state->largest_avail_idx--;
	}
	return next_state;
}

int main(){
	unsigned weights[8] = {1, 2, 5, 10, 20, 50, 100, 200};
	size_t length = 8;
	state* stack_top = malloc(sizeof(state));
	stack_top->remaining = 200;
	stack_top->largest_avail_idx = length - 1;
	stack_top->previous = NULL;
	
	unsigned count = 0;
	while (stack_top != NULL){
		if (stack_top->remaining == 0){
			count++;
		}
		stack_top = next(stack_top, weights);
	}
	printf("%d\n", count);
	return 0;
}