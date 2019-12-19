#ifndef DL_INTRU2_H
#define DL_INTRU2_H

#include <stddef.h> // for offsetof()

typedef struct dl_head_s { // this struct can't be hidden
	struct dl_head_s *p[2]; // p[0] points the previous record; p[1] points to the next
} dl_head_t;

/**
 * Given a pointer to a struct member, get the pointer to the struct
 *
 * @param ptr     pointer to a struct member
 * @param type    type of the struct
 * @param member  name of the member in the struct
 *
 * @return pointer to the struct
 */
#define dl_container_of(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Push a record to the list
 *
 * A double-linked list is represented by two pointers: a head and a tail. For
 * an empty list, both of them are set to NULL pointers. As such, head[0] and
 * head[1] shall be set to NULL on the first call to this function. dl_push()
 * implements C++'s push_back() and push_front() at the same time.
 *
 * @param head    head and tail of the list
 * @param p       pointer to the element to add
 * @param dir     direction: 0 for pushing from the front; 1 from the back
 */
void dl_push(dl_head_t *head[2], dl_head_t *p, int dir);

/**
 * Pop a record from the list
 *
 * @param head    head and tail of the list
 * @param dir     direction
 *
 * @return pointer to the record, which is removed from the list. If the list
 * is empty, NULL is returned. If the list only has one record, head[0] and
 * head[1] are set to NULL, indicating an empty list.
 */
dl_head_t *dl_pop(dl_head_t *head[2], int dir);

#ifdef __cplusplus
}
#endif

#endif
