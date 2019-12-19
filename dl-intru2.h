#ifndef DL_INTRU2_H
#define DL_INTRU2_H

#include <stddef.h>

#define dl_container_of(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct dl_head_s {
	struct dl_head_s *p[2];
} dl_head_t;

static inline void dl_push(dl_head_t *head[2], dl_head_t *p, int dir)
{
	dir = !!dir;
	p->p[0] = p->p[1] = 0;
	if (head[0] == 0 && head[1] == 0) head[0] = head[1] = p;
	else head[dir]->p[dir] = p, p->p[!dir] = head[dir], head[dir] = p;
}

static inline dl_head_t *dl_pop(dl_head_t *head[2], int dir)
{
	dl_head_t *p;
	dir = !!dir;
	if (head[0] == 0 && head[1] == 0) return 0;
	else if (head[0] == head[1]) p = head[0], head[0] = head[1] = 0;
	else p = head[dir], head[dir] = p->p[!dir], head[dir]->p[dir] = 0;
	return p;
}

#endif
