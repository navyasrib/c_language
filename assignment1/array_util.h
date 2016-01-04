typedef struct array_util {
	void *base;
	int type_size;
	int length;
} Array_util;

Array_util create(int, int);

int are_equal(Array_util, Array_util);

Array_util resize(Array_util, int);