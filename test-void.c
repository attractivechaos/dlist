#include <stdlib.h>
#include <stdio.h>
#include "dl-void.h"

#define MALLOC(type, len) (type*)malloc((len) * sizeof(type))

int main(void)
{
	int i, N = 5;
	dl_list_t *list;
	list = dl_init();
	for (i = 0; i < N; ++i) {
		int *x = MALLOC(int, 1);
		*x = i;
		dl_push(list, x, 1);
	}
	while (!dl_empty(list)) {
		void *p = dl_pop(list, 0);
		printf("out: %d\n", *(int*)p);
		free(p);
	}
	dl_destroy(list);
	return 0;
}
