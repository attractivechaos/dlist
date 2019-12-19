#include "dl-intru2.h"

void dl_push(dl_head_t *head[2], dl_head_t *p, int dir)
{
	dir = !!dir; // make sure dir is either 0 or 1
	p->p[0] = p->p[1] = 0;
	if (head[0] == 0 && head[1] == 0) head[0] = head[1] = p; // an empty list; then just add
	else head[dir]->p[dir] = p, p->p[!dir] = head[dir], head[dir] = p; // push
}

dl_head_t *dl_pop(dl_head_t *head[2], int dir)
{
	dl_head_t *p;
	dir = !!dir;
	if (head[0] == 0 && head[1] == 0) return 0; // an empty list; return a NULL pointer
	else if (head[0] == head[1]) p = head[0], head[0] = head[1] = 0; // only one element; clear the list
	else p = head[dir], head[dir] = p->p[!dir], head[dir]->p[dir] = 0; // more than one elements
	return p;
}
