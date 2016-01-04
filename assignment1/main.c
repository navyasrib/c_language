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

int main(void) {
	test_to_create_array();
	test_to_compare_two_arrays();
	test_to_compare_two_arrays_of_different_length();
	test_to_compare_two_arrays_of_different_types();
	test_to_compare_elements_of_two_arrays();
	resize_array_should_give_new_array_of_given_length();
	resize_array_should_give_new_array_of_same_elements();
	resize_array_should_give_new_array_of_same_elements_as_reference_array();

	return 0;
};