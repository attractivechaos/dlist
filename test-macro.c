#include <stdlib.h>
#include <stdio.h>
#include "dl-macro.h"
DL_IMPL(my, int)

int main(void)
{
	int i, N = 5;
	dl_list_t(my) *list;
	list = dl_init(my);
	for (i = 0; i < N; ++i)
		dl_push(my, list, i, 1);
	while (!dl_empty(my, list)) {
		int data;
		dl_pop(my, list, &data, 0);
		printf("out: %d\n", data);
	}
	dl_destroy(my, list);
	return 0;
}
