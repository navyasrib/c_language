typedef struct array_util {
	void *base;
	int type_size;
	int length;
} ArrayUtil;

ArrayUtil create(int, int);

int are_equal(ArrayUtil, ArrayUtil);

ArrayUtil resize(ArrayUtil, int);

int find_index(ArrayUtil, void *);

void dispose(ArrayUtil);

typedef int MatchFunc (void *, void *);

void *find_first(ArrayUtil, MatchFunc *, void *);

void *find_last(ArrayUtil, MatchFunc *, void *);

int count(ArrayUtil, MatchFunc *, void *);

int filter(ArrayUtil, MatchFunc *, void *, void **, int);

typedef void ConvertFunc(void *, void *, void *);

void map(ArrayUtil, ArrayUtil, ConvertFunc *, void *);
