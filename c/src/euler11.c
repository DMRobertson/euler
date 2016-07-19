#include <stdio.h>
#include <stdlib.h>

#define GRID_WIDTH 20
#define GRID_HEIGHT 20

/*
In the 20×20 grid below, four numbers along a diagonal line have been marked in red.

The product of these numbers is 26 × 63 × 78 × 14 = 1788696.

What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?
*/

int max(int a, int b){
	return a < b ? b : a;
}

typedef struct imatrix {
	size_t width;
	size_t height;
	int* data;
} matrix;

matrix* mnew(size_t width, size_t height){
	matrix* m = (matrix*) malloc(sizeof(matrix));
	m->width = width;
	m->height = height;
	m->data = (int*) malloc(width * height * sizeof(int));
	return m;
}

int* maddr(matrix* m, size_t x, size_t y){
	return (m->data) + x + (m->width)*y;
}

int mget(matrix* m, size_t x, size_t y){
	return m->data[x + (m->width)*y];
}

void load_grid(char const* filepath, matrix* grid){
	FILE* data = fopen(filepath, "r");
	for (size_t i = 0; i < GRID_WIDTH; i++){
			for (size_t j = 0; j < GRID_HEIGHT; j++){
				fscanf(data, "%02d", maddr(grid, i, j));
			}
		}
	fclose(data);
}

int horiz_prod(size_t length, matrix* grid, size_t x, size_t y){
	int prod = 1;
	for (size_t i = 0; i < length; i++){
		prod *= mget(grid, x + i, y);
	}
	return prod;
}

int vert_prod(size_t length, matrix* grid, size_t x, size_t y){
	int prod = 1;
	for (size_t i = 0; i < length; i++){
		prod *= mget(grid, x, y + i);
	}
	return prod;
}

int diag_se_prod(size_t length, matrix* grid, size_t x, size_t y){
	int prod = 1;
	for (size_t i = 0; i < length; i++){
		prod *= mget(grid, x + i, y + i);
	}
	return prod;
}

int diag_sw_prod(size_t length, matrix* grid, size_t x, size_t y){
	int prod = 1;
	for (size_t i = 0; i < length; i++){
		prod *= mget(grid, x - i, y + i);
	}
	return prod;
}

int max_line_product(size_t length, matrix* grid){
	int max_product = 0;
	//1. Horizontal lines
	for (size_t x = 0; x + length < grid->width; x++){
		for (size_t y = 0; y < grid->height; y++){
			max_product = max(max_product, horiz_prod(length, grid, x, y));
		}
	}
	//2. Vertical lines
	for (size_t x = 0; x < grid->width; x++){
		for (size_t y = 0; y + length < grid->height; y++){
			max_product = max(max_product, vert_prod(length, grid, x, y));
		}
	}
	//3. Diagonal lines South-East
	for (size_t x = 0; x + length < grid->width; x++){
		for (size_t y = 0; y + length < grid->height; y++){
			max_product = max(max_product, diag_se_prod(length, grid, x, y));
		}
	}
	int xmax, ymax;
	//4. Diagonal lines South-West
	for (size_t x = length; x < grid->width; x++){
		for (size_t y = 0; y + length < grid->height; y++){
			max_product = max(max_product, diag_sw_prod(length, grid, x, y));
		}
	}
	return max_product;
}

int main(){
	matrix* grid = mnew(GRID_WIDTH, GRID_HEIGHT);
	load_grid("../resource/problem11.grid", grid);
	printf("%d\n", max_line_product(4, grid));
	return EXIT_SUCCESS;
}