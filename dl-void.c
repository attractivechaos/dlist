#include <stdlib.h>
#include "dl-void.h"

// see dl-intru2.* for the algorithm

#define CALLOC(type, len) (type*)calloc((len), sizeof(type))

typedef struct dl_node_s {
	void *data;
	struct dl_node_s *p[2];
} dl_node_t;

struct dl_list_s {
	dl_node_t *head[2];
};

dl_list_t *dl_init(void) { return CALLOC(dl_list_t, 1); }

void dl_push(dl_list_t *list, void *data, int dir)
{
	dl_node_t *p = CALLOC(dl_node_t, 1);
	dir = !!dir;
	p->data = data;
	if (list->head[0] == 0 && list->head[1] == 0) list->head[0] = list->head[1] = p;
	else list->head[dir]->p[dir] = p, p->p[!dir] = list->head[dir], list->head[dir] = p;
}

void *dl_pop(dl_list_t *list, int dir)
{
	dl_node_t *p;
	void *data = 0;
	dir = !!dir;
	if (list->head[0] == 0 && list->head[1] == 0) return 0;
	else if (list->head[0] == list->head[1]) p = list->head[0], list->head[0] = list->head[1] = 0;
	else p = list->head[dir], list->head[dir] = p->p[!dir], list->head[dir]->p[dir] = 0;
	data = p->data;
	free(p);
	return data;
}

void dl_destroy(dl_list_t *list)
{
	while (list->head[0]) {
		dl_node_t *p = dl_pop(list, 1);
		free(p);
	}
	free(list);
}

int dl_empty(const dl_list_t *list)
{
	return (list == 0 || list->head[0] == 0);
}
