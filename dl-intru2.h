#ifndef DL_INTRU2_H
#define DL_INTRU2_H

#include <stddef.h>

#define dl_container_of(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

typedef struct dl_head_s {
	struct dl_head_s *p[2];
} dl_head_t;

#ifdef __cplusplus
extern "C" {
#endif

void dl_push(dl_head_t *head[2], dl_head_t *p, int dir);
dl_head_t *dl_pop(dl_head_t *head[2], int dir);

#ifdef __cplusplus
}
#endif

#endif
