#include <stdlib.h>
#include <stdio.h>

#define DL_TYPE int
#define DL_NAME my
#include "dl-macro2.h"
#undef DL_TYPE
#undef DL_NAME

int main(void)
{
	int i, N = 5;
	DL_LIST_T(my) *list;
	list = DL_INIT(my)();
	for (i = 0; i < N; ++i)
		DL_PUSH(my)(list, i, 1);
	while (!DL_EMPTY(my)(list)) {
		int data;
		DL_POP(my)(list, &data, 0);
		printf("out: %d\n", data);
	}
	DL_DESTROY(my)(list);
	return 0;
}
