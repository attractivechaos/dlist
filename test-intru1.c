#include <stdlib.h>
#include <stdio.h>
#include "dl-intru1.h"

#define MALLOC(type, len) (type*)malloc((len) * sizeof(type))

typedef struct my_dlist_s {
	int x;
	DL_HEAD(struct my_dlist_s) head;
} my_elem_t;

DL_IMPL(my, my_elem_t, head)

int main(void)
{
	int i, N = 5;
	my_elem_t *head[2] = {0, 0};
	for (i = 0; i < N; ++i) {
		my_elem_t *p = MALLOC(my_elem_t, 1);
		p->x = i;
		dl_push(my, head, p, 1); // push back
	}
	while (head[0]) {
		my_elem_t *p;
		p = dl_pop(my, head, 0); // pop front
		printf("out: %d\n", p->x);
		free(p);
	}
	return 0;
}
