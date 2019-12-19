#include <stdlib.h>
#include <stdio.h>
#include "dl-intru1.h"

typedef struct my_dlist_s {
	int x;
	DL_HEAD(struct my_dlist_s) head;
} my_dlist_t;

DL_IMPL(my, my_dlist_t, head)

int main(void)
{
	int i;
	my_dlist_t *head[2] = {0, 0}, data[10];
	for (i = 0; i < 10; ++i) {
		data[i].x = i;
		dl_push(my, head, &data[i], 1); // push back
	}
	while (head[0]) {
		my_dlist_t *p;
		p = dl_pop(my, head, 0); // pop front
		printf("out: %d\n", p->x);
	}
	return 0;
}
