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
	return (numerator%denominator)? 0:1;
};

void find_first_should_give_the_element_that_matched_with_criteria() {
	Array_util array = create(4,4);
	int *num = (int *)array.base;
	num[0] = 5;
	num[1] = 24;
	num[2] = 9;
	num[3] = 15;
	void *even_hint = NULL;
	int *even_check = (int *)find_first(array, &is_even, even_hint);
	assert(*even_check == 24);
	int divide_hint = 3;
	int *divide_check = (int *)find_first(array, &is_divisible, &divide_hint);
	assert(*divide_check == 24);
	dispose(array);
};

int main(void) {
	test_to_create_array();
	test_to_compare_two_arrays();
	test_to_compare_two_arrays_of_different_length();
	test_to_compare_two_arrays_of_different_types();
	test_to_compare_elements_of_two_arrays();
	resize_array_should_give_new_array_of_given_length();
	resize_array_should_give_new_array_of_same_elements();
	resize_array_should_give_new_array_of_same_elements_as_reference_array();
	find_index_should_give_the_index_of_an_element_in_array();
	find_index_should_give_1_if_the_element_is_not_present_in_array();
	test_for_dispose_array();
	find_first_should_give_the_element_that_matched_with_criteria();

  return 0;
};
