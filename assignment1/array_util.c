#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_util.h"

ArrayUtil create(int type_size, int length) {
	ArrayUtil array;
	array.base = (void *)calloc(length,type_size);
	array.type_size = type_size;
	array.length = length;
	return array;
};

int are_equal(ArrayUtil a, ArrayUtil b) {
	if(a.length != b.length || a.type_size != b.type_size) return 0;
	for(int i=0; i<a.length; i++){
		if(memcmp(a.base+(a.type_size*i), b.base+(b.type_size*i), a.type_size )) 
			return 0;	
	};
	return 1;
};

ArrayUtil resize(ArrayUtil array, int length) {
	ArrayUtil new_array;
	new_array.length = length;
	new_array.type_size = array.type_size;
	void *arr1 = array.base;
	void *arr2 = (void *)realloc(array.base, length);
	for(int i=0; i<length; i++) {
		memcpy(arr2+(new_array.type_size*i), arr1+(array.type_size*i), array.type_size);
	};
	free(array.base);
	new_array.base = arr2;
	return new_array;
};

int find_index(ArrayUtil array, void *element) {
	for(int i=0; i<array.length; i++) {
		if(!memcmp(array.base+(array.type_size*i), element, array.type_size )) 
			return i;
	};
	return -1;
};

void dispose(ArrayUtil util) {
	free(util.base);
};

void *find_first(ArrayUtil array, MatchFunc *match, void *hint) {
  	void *numbers = array.base;
  	for (int i = 0; i < array.length; i++){
  		if(match(hint, numbers+(array.type_size*i)))
  			return numbers+(array.type_size*i);
  	}
  	return NULL;
};

void *find_last(ArrayUtil array, MatchFunc *match, void *hint) {
  	void *numbers = array.base;
  	for (int i = array.length-1; i >= 0; i--){
  		if(match(hint, numbers+(array.type_size*i)))
  			return numbers+(array.type_size*i);
  	}
  	return NULL;
};

int count(ArrayUtil util, MatchFunc* match, void* hint) {
	int count = 0;
	void *numbers = util.base;
  	for (int i = 0; i < util.length; i++){
  		if(match(hint, numbers+(util.type_size*i)))
  			count++;
  	};
  	return count;
};

int filter(ArrayUtil array, MatchFunc *match, void *hint, void **destination, int max_items) {
	void *numbers;
	int count = 0;
  	for (int i = 0; i < array.length; i++){
  		numbers = array.base+(array.type_size * i);
  		if(match(hint,numbers)) {
  			destination[count] = numbers;
  			count++;
  		}
  	}
  	return count;
};

void map(ArrayUtil source, ArrayUtil destination, ConvertFunc* convert, void* hint) {
	void *numbers;
	void *result;
  	for (int i = 0; i < source.length; i++){
  		numbers = source.base+(source.type_size * i);
  		result = destination.base+(source.type_size * i);
  			convert(hint, numbers, result);
  	}
};









