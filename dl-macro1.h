#ifndef DL_MACRO1_H
#define DL_MACRO1_H

// see dl-intru2.* for details on the methodology

#define DL_CALLOC(type, len) (type*)calloc((len), sizeof(type))

#define DL_IMPL(name, SCOPE, _type) /* name creates a name space for a specific data type to avoid naming clash */ \
	typedef struct dl_node_##name##_s { /* ##name## for token concatenation */ \
		_type data; \
		struct dl_node_##name##_s *p[2]; \
	} dl_node_##name##_t; \
	typedef struct { dl_node_##name##_t *head[2]; } dl_list_##name##_t; \
	SCOPE dl_list_##name##_t *dl_init_##name(void) { return DL_CALLOC(dl_list_##name##_t, 1); } \
	SCOPE void dl_push_##name(dl_list_##name##_t *list, _type data, int dir) { \
		dl_node_##name##_t *p = DL_CALLOC(dl_node_##name##_t, 1); \
		dir = !!dir; \
		p->data = data; \
		if (list->head[0] == 0 && list->head[1] == 0) list->head[0] = list->head[1] = p; \
		else list->head[dir]->p[dir] = p, p->p[!dir] = list->head[dir], list->head[dir] = p; \
	} \
	SCOPE int dl_pop_##name(dl_list_##name##_t *list, _type *data, int dir) { /* *data is only set if 1 is returned */ \
		dl_node_##name##_t *p; \
		dir = !!dir; \
		if (list->head[0] == 0 && list->head[1] == 0) return 0; \
		else if (list->head[0] == list->head[1]) p = list->head[0], list->head[0] = list->head[1] = 0; \
		else p = list->head[dir], list->head[dir] = p->p[!dir], list->head[dir]->p[dir] = 0; \
		*data = p->data; \
		free(p); \
		return 1; \
	} \
	SCOPE void dl_destroy_##name(dl_list_##name##_t *list) { /* TODO: is this right? */ \
		dl_node_##name##_t *q, *p = list->head[0]; \
		while (p) { q = p->p[1]; free(p); p = q; } \
		free(list); \
	} \
	SCOPE int dl_empty_##name(const dl_list_##name##_t *list) { return (list == 0 || list->head[0] == 0); }

#define dl_list_t(name) dl_list_##name##_t

#define dl_init(name) dl_init_##name()
#define dl_destroy(name, list) dl_destroy_##name(list)
#define dl_push(name, list, data, dir) dl_push_##name(list, data, dir)
#define dl_pop(name, list, data, dir) dl_pop_##name(list, data, dir)
#define dl_empty(name, list) dl_empty_##name(list)

#endif
