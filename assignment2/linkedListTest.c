#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedList.h"

void test_for_create_list() {
	LinkedList list = createList();
	assert(list.length == 0);
	assert(list.first == NULL);
	assert(list.last == NULL);
};

void test_for_adding_to_linkedList() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 8;
	assert(add_to_list(&list, &value) == 1);
	assert(add_to_list(&list, &value1) == 2);
	assert(*(int *)list.first->value == 5);
	assert(*(int *)list.last->value == 8);
};

void test_for_get_first_element() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);

	int result = *(int *)get_first_element(list);
	assert(result == 5);
	
	LinkedList list1 = createList();
	char char0 = 'q';
	char char1 = 'w';
	char char2 = 'r';
	add_to_list(&list1, &char0);
	add_to_list(&list1, &char1);
	add_to_list(&list1, &char2);
	char result1 = *(char *)get_first_element(list1);
	assert(result1 == 'q');
};

void test_for_get_last_element() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);
	int result = *(int *)get_last_element(list);
	assert(result == 10);
	
	LinkedList list1 = createList();
	char char0 = 'q';
	char char1 = 'w';
	char char2 = 'r';
	add_to_list(&list1, &char0);
	add_to_list(&list1, &char1);
	add_to_list(&list1, &char2);
	char result1 = *(char *)get_last_element(list1);
	assert(result1 == 'r');
};

void increment(void *value){
	*(int *)value += 1;
};

void test_for_forEach() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);
	forEach(list,&increment);
	assert(*(int *)list.first->value == 6);
	assert(*(int *)list.last->value == 11);
	
	LinkedList list1 = createList();
	char char0 = 'q';
	char char1 = 'w';
	char char2 = 'r';
	add_to_list(&list1, &char0);
	add_to_list(&list1, &char1);
	add_to_list(&list1, &char2);
	forEach(list1,&increment);
	assert(*(char *)list1.first->value == 'r');
	assert(*(char *)list1.last->value == 's');
};

void test_for_get_element() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);
	int *result = (int *) getElementAt(list, 2);
	int *result1 = (int *) getElementAt(list, 1);
	int *result2 = (int *) getElementAt(list, 3);
	int *result3 = (int *) getElementAt(list, 5);
	assert(*result == 6);
	assert(*result1 == 5);
	assert(*result2 == 10);
	assert(result3 == NULL);
};

void test_for_indexOf() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);
	int num = 10;
	assert(indexOf(list, &num) == 3);
	int num1 = 5;
	assert(indexOf(list, &num1) == 1);
	int num2 = 23;
	assert(indexOf(list, &num2) == -1);
};

void test_for_deleteElement() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);
	int *deletedItem = (int *)deleteElementAt(&list, 2);
	assert(*deletedItem == 6);
};

void test_for_asArray_function() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);

	void *dest = (void *)calloc(5,8);
	int result = asArray(list, dest, 5);
	assert(result == 3);
	assert(**(int **)dest == 5);
	dest+=8;
	assert(**(int **)dest == 6);
	dest+=8;
	assert(**(int **)dest == 10);
};

void test_two_for_asArray_function() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);

	void *dest = (void *)calloc(2,8);
	int result = asArray(list, dest, 2);
	assert(result == 2);
	assert(**(int **)dest == 5);
	dest+=8;
	assert(**(int **)dest == 6);
};

void test_for_filter() {
	LinkedList list = createList();
	int value = 5;
	int value1 = 6;
	int value2 = 10;
	add_to_list(&list, &value);
	add_to_list(&list, &value1);
	add_to_list(&list, &value2);

	int hint = 10;
	LinkedList resultList = filter(list, &lessThanHint, &hint);
	assert(resultList.length == 2);
	assert(*(int *)resultList.first->value == 5);
	assert(*(int *)resultList.last->value == 6);
};