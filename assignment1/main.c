#include <stdio.h>
#include <assert.h>
#include "array_util.h"

void test_to_create_array() {
	ArrayUtil array = create(4, 3);
	int *num;
	num = (int *) array.base;
	num[0] = 1;
	assert(array.length == 3);
	assert(array.type_size == 4);
	dispose(array);
};

void test_to_compare_two_arrays() {
	ArrayUtil a = create(4, 3);
	ArrayUtil b = create(4, 3);
	assert(are_equal(a ,b) == 1);
	dispose(b);
	dispose(a);
};

void test_to_compare_two_arrays_of_different_length() {
	ArrayUtil a = create(4, 2);
	ArrayUtil b = create(4, 3);
	assert(are_equal(a ,b) == 0);
	dispose(a);
	dispose(b);
};

void test_to_compare_two_arrays_of_different_types() {
	ArrayUtil a = create(1, 2);
	ArrayUtil b = create(4, 2);
	assert(are_equal(a ,b) == 0);
	dispose(a);
	dispose(b);
};

void test_to_compare_elements_of_two_arrays() {
	ArrayUtil a = create(1, 5);
	ArrayUtil b = create(4, 5);
	int *array = a.base;
	array[0] = 2;
	a.base = array;
	assert(are_equal(a ,b) == 0);
	dispose(a);
	dispose(b);
};

void test_resize_array_should_give_new_array_of_given_length() {
	ArrayUtil array = create(4, 4);
	int *arr = array.base;
	arr[0] = 2;
	array.base = arr;
	ArrayUtil new_array = resize(array, 3);
	assert(new_array.length == 3);
};

void test_resize_array_should_give_new_array_of_same_elements() {
	ArrayUtil array = create(4, 4);
	int *arr1 = array.base;
	arr1[0] = 2;
	array.base = arr1;
	ArrayUtil new_array = resize(array, 3);
	int *arr2 = new_array.base;
	assert(arr2[0] == 2);
};

void test_resize_array_should_give_new_array_of_same_elements_as_reference_array() {
	ArrayUtil array = create(4, 4);
	int *arr1 = array.base;
	arr1[0] = 2;
	array.base = arr1;
	ArrayUtil new_array = resize(array, 6);
	int *arr2 = new_array.base;
	assert(arr2[0] == 2);
	assert(arr2[5] == 0);
};

void test_find_index_should_give_the_index_of_an_element_in_array() {
	ArrayUtil array = create(4, 4);
	int *arr1 = array.base;
	for(int i=0; i<4; i++) {
		arr1[i] = i+1;
	};
	int x = 3;
	assert(find_index(array, &x) == 2);
	dispose(array);
};

void test_find_index_should_give_1_if_the_element_is_not_present_in_array() {
	ArrayUtil array = create(4, 4);
	int *arr1 = array.base;
	for(int i=0; i<4; i++) {
		arr1[i] = i+1;
	};
	int x = 6;
	assert(find_index(array, &x) == -1);
	dispose(array);
};

void test_for_dispose_array() {
	ArrayUtil array = create(4, 4);
	int *arr1 = array.base;
	for(int i=0; i<4; i++) {
		arr1[i] = i+1;
	};
	dispose(array);
};

int is_even(void *hint, void *item) {
	int num = *(int *)item;
	return !(num%2);
};

int is_divisible(void *hint, void *item) {
	int denominator = *(int *)hint;
	int numerator = *(int *)item;
	return (numerator % denominator)? 0:1;
};

void test_find_first_should_give_the_element_that_matched_with_criteria() {
	ArrayUtil array = create(4,4);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	void *even_hint = NULL;
	int *even_check = (int *)find_first(array, &is_even, even_hint);
	assert(*even_check == 24);
	int divide_hint = 3;
	int *divide_check = (int *)find_first(array, &is_divisible, &divide_hint);
	assert(*divide_check == 24);
	dispose(array);
};

void test_find_last_should_give_the_last_element_that_matched_with_criteria() {
	ArrayUtil array = create(4,4);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 15;
	void *even_hint = NULL;
	int *even_check = (int *)find_last(array, &is_even, even_hint);
	assert(*even_check == 24);
	int divide_hint = 3;
	int *divide_check = (int *)find_last(array, &is_divisible, &divide_hint);
	assert(*divide_check == 15);
	dispose(array);
};

void test_for_count_of_elements_that_matches_with_criteria() {
	ArrayUtil array = create(4,5);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	num[4] = 100;
	void *even_hint = NULL;
	assert(count(array, &is_even, even_hint) == 3);
	int divide_hint = 3;
	assert(count(array, &is_divisible, &divide_hint) == 2);
	dispose(array);
};

void test_for_filter_should_give_the_count_of_matching_elements() {
	ArrayUtil array = create(4,5);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	num[4] = 100;
	void *even_hint = NULL;
	void *destination;
	int answer1 = filter(array, &is_even, &even_hint, &destination, 2);
	assert(answer1 == 2);

	int divide_hint = 3;
	int answer2 = filter(array, &is_divisible, &divide_hint, &destination, 4);
	assert(answer2 == 2);
	dispose(array);
};

void test_for_filter_should_give_the_matching_elements() {
	ArrayUtil array = create(4,5);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 2;
	num[3] = 2023;
	num[4] = 100;
	void *even_hint = NULL;
	void *destination1;
	int answer1 = filter(array, &is_even, &even_hint, &destination1, 2);
	int *result1 = (int *) destination1;
	assert(result1[0] == 24);
	assert(result1[1] == 2);

	int divide_hint = 3;
	void *destination2;
	int answer2 = filter(array, &is_divisible, &divide_hint, &destination2, 4);
	int *result2 = (int *) destination2;
	assert(result2[0] == 24);

};

void add(void *hint, void *sourceItem, void *destinationItem) {
	int source = *(int *) sourceItem;
	int *destination = (int *) destinationItem;
	int number = *(int *) hint;
	*destination = source + number;
};


void test_for_map() {
	ArrayUtil source = create(4,5);
	int *num = (int *) source.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	num[4] = 100;
	ArrayUtil destination = create(4,5);
	int hint = 2;
	map(source, destination, &add, &hint);
	int *result = (int *) destination.base;
	assert(result[0] == 7);
	assert(result[1] == 26);
	assert(result[2] == 11);
	assert(result[3] == 22);
	assert(result[4] == 102);
};

void multiply(void* hint, void* item) {
	int *source = (int *) item;
	int number = *(int *) hint;
	*source = *source * number;
};

void test_for_forEach() {
	ArrayUtil array = create(4,5);
	int *num = (int *) array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	num[4] = 100;
	int hint = 2;
	forEach(array, &multiply, &hint);
	int *result = (int *) array.base;
	assert(result[0] == 10);
	assert(result[1] == 48);
	assert(result[2] == 18);
	assert(result[3] == 40);
	assert(result[4] == 200);
};

void* adder(void* hint, void* previousItem, void* item) {
	int *previous = (int *) previousItem;
	int *present = (int *) item;
	*previous = *previous + *present;
	return previous;
};

void test_for_reduce() {
	ArrayUtil array = create(4,5);
	int *num = (int *) array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	num[4] = 100;
	void *hint = NULL;
	int initial_value = 0;
	int result = *(int *) reduce(array, &adder, &hint, &initial_value);
	assert(result == 158);
};

