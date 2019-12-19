#include <stdlib.h>
#include <stdio.h>
#include "dl-intru2.h"

#define MALLOC(type, len) (type*)malloc((len) * sizeof(type))

typedef struct {
	int x;
	dl_head_t head; // this field forms a double-linked list
} my_elem_t;

int main(void)
{
	int i, N = 5;
	dl_head_t *head[2] = {0, 0};
	for (i = 0; i < N; ++i) {
		my_elem_t *p = MALLOC(my_elem_t, 1); // caller controls all memory allocations
		p->x = i;
		dl_push(head, &p->head, 1); // push_back()
	}
	while (head[0]) {
		dl_head_t *p = dl_pop(head, 0); // pop_front()
		my_elem_t *q = dl_container_of(p, my_elem_t, head); // pointer to the parent struct
		printf("out: %d\n", q->x);
		free(q); // again, caller controls memory
	}
	return 0;
}
