#include <stdio.h>
#include <stdlib.h>
#include "array_util.h"

Array_util create(int type_size, int length) {
	Array_util array;
	array.base = (void *)calloc(length,type_size);
	array.type_size = type_size;
	array.length = length;
	return array;
};

int are_equal(Array_util a, Array_util b) {
	int *num1 = (int *)a.base;
	int *num2 = (int *)b.base;
	if(a.length != b.length || a.type_size != b.type_size) return 0;
	for(int i=0; i<a.length; i++){
		if(num1[i] != num2[i]) return 0;	
	};
	return 1;
};

Array_util resize(Array_util array, int length) {
	Array_util new_array;
	new_array.length = length;
	new_array.type_size = array.type_size;
	int *arr1 = array.base;
	int *arr2 = (void *)realloc(array.base, length);
	for(int i=0; i<length; i++) {
		arr2[i] = arr1[i];
	};
	free(array.base);
	new_array.base = arr2;
	return new_array;
};

int find_index(Array_util array, void *element) {
	int x = * (int *)element;
	int *base = array.base;
	for(int i=0; i<array.length; i++) {
		if(base[i] == x) return i;
	};
	return -1;
};

void dispose(Array_util util) {
	free(util.base);
};

void *find_first(Array_util array, MatchFunc *match, void *hint) {
  	int *numbers = array.base;
  	for (int i = 0; i < array.length; i++){
  		if(match(hint, &numbers[i]))
  			return &numbers[i];
  	}
  	return NULL;
};

void *find_last(Array_util array, MatchFunc *match, void *hint) {
  	int *numbers = array.base;
  	for (int i = array.length-1; i >= 0; i--){
  		if(match(hint, &numbers[i]))
  			return &numbers[i];
  	}
  	return NULL;
};


int count(Array_util util, MatchFunc* match, void* hint) {
	int count = 0;
	int *numbers = util.base;
  	for (int i = 0; i < util.length; i++){
  		if(match(hint, &numbers[i]))
  			count++;
  	};
  	return count;
};