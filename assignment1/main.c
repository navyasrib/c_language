#include <stdio.h>
#include <assert.h>
#include "array_util.h"

void test_to_create_array() {
	Array_util array = create(4, 3);
	int *num;
	num = (int *) array.base;
	num[0] = 1;
	assert(array.length == 3);
	assert(array.type_size == 4);
};

void test_to_compare_two_arrays() {
	Array_util a = create(4, 3);
	Array_util b = create(4, 3);
	assert(are_equal(a ,b) == 1);
};

void test_to_compare_two_arrays_of_different_length() {
	Array_util a = create(4, 2);
	Array_util b = create(4, 3);
	assert(are_equal(a ,b) == 0);
};

void test_to_compare_two_arrays_of_different_types() {
	Array_util a = create(1, 2);
	Array_util b = create(4, 2);
	assert(are_equal(a ,b) == 0);
};

void test_to_compare_elements_of_two_arrays() {
	Array_util a = create(1, 5);
	Array_util b = create(4, 5);
	int *array = a.base;
	array[0] = 2;
	a.base = array;
	assert(are_equal(a ,b) == 0);
};

void resize_array_should_give_new_array_of_given_length() {
	Array_util array = create(4, 4);
	int *arr = array.base;
	arr[0] = 2;
	array.base = arr;
	Array_util new_array = resize(array, 3);
	assert(new_array.length == 3);
};

void resize_array_should_give_new_array_of_same_elements() {
	Array_util array = create(4, 4);
	int *arr1 = array.base;
	arr1[0] = 2;
	array.base = arr1;
	Array_util new_array = resize(array, 3);
	int *arr2 = new_array.base;
	assert(arr2[0] == 2);
};

void resize_array_should_give_new_array_of_same_elements_as_reference_array() {
	Array_util array = create(4, 4);
	int *arr1 = array.base;
	arr1[0] = 2;
	array.base = arr1;
	Array_util new_array = resize(array, 6);
	int *arr2 = new_array.base;
	assert(arr2[0] == 2);
	assert(arr2[5] == 0);
};

void find_index_should_give_the_index_of_an_element_in_array() {
	Array_util array = create(4, 4);
	int *arr1 = array.base;
	for(int i=0; i<4; i++) {
		arr1[i] = i+1;
	};
	int x = 3;
	assert(find_index(array, &x) == 2);
};

void find_index_should_give_1_if_the_element_is_not_present_in_array() {
	Array_util array = create(4, 4);
	int *arr1 = array.base;
	for(int i=0; i<4; i++) {
		arr1[i] = i+1;
	};
	int x = 6;
	assert(find_index(array, &x) == -1);
};

void test_for_dispose_array() {
	Array_util array = create(4, 4);
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

void find_first_should_give_the_element_that_matched_with_criteria() {
	Array_util array = create(4,4);
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

void find_last_should_give_the_last_element_that_matched_with_criteria() {
	Array_util array = create(4,4);
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
	Array_util array = create(4,5);
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
	Array_util array = create(4,5);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	num[4] = 100;
	void *even_hint = NULL;
	void *destination;
	assert(filter(array, &is_even, &even_hint, &destination, 0) == 3);
	int divide_hint = 5;
	assert(filter(array, &is_divisible, &divide_hint, &destination, 0) == 3);
};

void test_for_filter_should_give_the_matching_elements() {
	Array_util array = create(4,5);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 20;
	num[4] = 100;
	void *even_hint = NULL;
	void *destination1;
	filter(array, &is_even, &even_hint, &destination1, 0);
	int *result1 = (int *) destination1;
	assert(24 == result1[0]);
	assert(100 == result1[3]);
	int divide_hint = 3;
	void *destination2;
	filter(array, &is_divisible, &divide_hint, &destination2, 0);
	int *result2 = (int *) destination2;
	assert(24 == result2[0]);
	assert(9 == result2[1]);
};

// int main() {
// 	test_for_filter_should_give_the_matching_elements();
// 	return 0;
// };
