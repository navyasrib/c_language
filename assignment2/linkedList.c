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
	void *deletedItem;
	Element *ele = list->first;
	while(ele != NULL) {
		count++;
		if(count == index){
			deletedItem = ele->value;
			free(ele);
		}
		ele = ele->next;
	};
	return deletedItem;
};

