typedef struct list {
	struct element * first;
	struct element * last;
	int length;
} LinkedList;

typedef struct element {
	void *value;
	struct element * next;	
} Element;

LinkedList createList(void);

int add_to_list(LinkedList *, void *);

void *get_first_element(LinkedList);

void *get_last_element(LinkedList);

typedef void (ElementProcessor)(void *);

void forEach(LinkedList, ElementProcessor *);

void * getElementAt(LinkedList, int );

int indexOf(LinkedList, void *);

void * deleteElementAt(LinkedList *, int);

int asArray(LinkedList, void **, int);