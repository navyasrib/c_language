#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

LinkedList createList() {
	LinkedList list;
	list.first = list.last = NULL;
	list.length = 0;
	return list;
};

int add_to_list(LinkedList *list, void *value) {
	Element *ptr = (Element *) malloc(sizeof(Element));
	ptr->value = value;
	ptr->next = NULL;
	if(list->length == 0)
		list->first = list->last = ptr;
	else
		list->last = list->last->next = ptr;
	list->length++;
	return list->length;
};

void *get_first_element(LinkedList list) {
	return list.first->value;
};

void *get_last_element(LinkedList list) {
	return list.last->value;
};

void increment(void *value){
	*(int *)value += 1;
};

void forEach(LinkedList list, ElementProcessor *func) {
	Element *value = list.first;
	while(value != NULL) {
		func(value->value);
		value = value->next;
	};
};

void * getElementAt(LinkedList list, int index) {
	int count = 0;
	Element *value = list.first;
	while(value != NULL) {
		count++;
		if(count == index)
			return value->value;
		value = value->next;
	};
	return NULL;
};

int indexOf(LinkedList list, void *num) {
	int index = 0;
	Element *value = list.first;
	while(value != NULL) {
		index++;
		if(*(int *)value->value == *(int *)num)
			return index;
		value = value->next;
	};
	return -1;
};

void * deleteElementAt(LinkedList *list, int index) {
	int count = 0;
	Element *deletedItem;
	Element *ele = list->first;
	for(int i=1; i<index-1; i++) {
		ele = ele->next;
	}
	deletedItem = ele->next;
	ele->next = deletedItem->next;
	free(deletedItem);
	return deletedItem->value;
};

int asArray(LinkedList list, void **array, int maxElements) {
	Element *value = list.first;
	int count = 0;
	while((value != NULL) && (count < maxElements)){
		array[count] = value->value;
		value = value->next;
		count++;
	}
	return count;
};

int lessThanHint(void* hint, void* item) {
	return (*(int *)item < *(int *)hint)? 1:0;
};

LinkedList filter(LinkedList list, MatchFunc* match, void *hint) {
	LinkedList resultList = createList();
	Element *value = list.first;
	int count = list.length;
	while(count !=0){
		if(match(hint, value->value))
			add_to_list(&resultList, value->value);
		value = value->next;
		count--;
	}
	return resultList;
};

LinkedList reverse(LinkedList list) {
	void *temp = calloc(list.length,8);
	void **array = temp;
	LinkedList resultList = createList();
	asArray(list, array, list.length);
	for(int i=list.length-1; i>=0; i--) 
		add_to_list(&resultList, (int *)array[i]);
	free(temp);
	return resultList;
};

void addHint(void* hint, void* sourceItem, void* destinationItem) {
	*(int *)destinationItem = *(int *)sourceItem + *(int *)hint;
};

LinkedList map(LinkedList list, ConvertFunc *func, void *hint) {
	LinkedList resultList = createList();
	void *temp = calloc(list.length, 8);
	void **allValues = temp;
	Element *value = list.first;
	for(int i=0; i<list.length; i++) {
		func(hint, value->value, &allValues[i]);
		add_to_list(&resultList, temp);
		value = value->next;
		temp+=8;
	}
	return resultList;
};

void* add(void* hint, void* previousItem, void* item) {
	int *previous = (int *) previousItem;
	*previous = *previous + *(int *) item;
	return previous;
};

LinkedList reduce(LinkedList list, Reducer *reducer, void *hint, void *initialValue) {
	LinkedList result = createList();
	Element *ele = list.first;
  	for (int i = 0; i < list.length; i++){
  		initialValue = reducer(hint, initialValue, ele->value);
  		ele = ele->next;
  	}
  	add_to_list(&result, initialValue);
  	return result;
};
