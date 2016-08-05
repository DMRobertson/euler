#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/* Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file? */

typedef struct names_array {
	size_t stride;
	size_t count;
	char* data;
	char* data_end;
} names_array;

names_array* new_names_array (size_t longest, size_t count){
	// Each entry requires an extra char for the null
	size_t chars_required = (longest + 1) * count;
	char* data = malloc(sizeof(char) * chars_required);
	names_array* names = malloc(sizeof(names_array));
	names->stride   = longest + 1;
	names->count    = count;
	names->data     = data;
	names->data_end = data + chars_required;
	return names;
}

char* naddr(names_array* names, size_t index){
	return names->data + index * names->stride;
}

size_t max (size_t a, size_t b){
	return a < b ? b : a;
}

names_array* read_names (char const* filepath){
	FILE* data = fopen(filepath, "rt");
	int c = 0;
	size_t num_names = 0;
	size_t longest = 0;
	size_t length = 0;
	while (true){
		c = fgetc(data);
		if (c == ',' || c == EOF){
			//Don't count the quote characters
			length -= 2;
			num_names++;
			longest = max(length, longest);
			length = 0;
		} else {
			length++;
		}
		if (c == EOF){
			break;
		}
	}
	names_array* names = new_names_array(longest, num_names);
	fseek(data, 0, SEEK_SET);
	for (char* location = names->data; location < names->data_end; location += names->stride){
		fscanf(data, "\"%[^\"]\"", location);
		fseek(data, 1, SEEK_CUR);
	}
	fclose(data);
	return names;
}

int strcmp_wrapper(const void* a, const void* b){
	return strcmp(a, b);
}

void sort_names(names_array* names){
	qsort(names->data, names->count, sizeof(char) * names->stride, strcmp_wrapper);
}

unsigned word_score(char const* name){
	unsigned score = 0;
	for (; *name != '\0'; name++){
		score += *name - ('A' - 1);
	}
	return score;
}

unsigned names_score(names_array* names){
	unsigned score = 0;
	char* location = names->data;
	for (size_t i = 1; i <= names->count; i++){
		score += i * word_score(location);
		location += names -> stride;
	}
	return score;
}

int main(){
	names_array* names = read_names("../resource/problem22.names");
	sort_names(names);
	assert(strcmp(naddr(names, 938-1), "COLIN") == 0);
	assert(word_score("COLIN") == 53);
	printf("%d\n", names_score(names));
	free(names->data);
	free(names);
	return 0;
}