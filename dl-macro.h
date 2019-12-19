#ifndef DL_MACRO_H
#define DL_MACRO_H

#define DL_CALLOC(type, len) (type*)calloc((len), sizeof(type))

#define DL_IMPL(name, _type) \
	typedef struct dl_node_##name##_s { \
		_type data; \
		struct dl_node_##name##_s *p[2]; \
	} dl_node_##name##_t; \
	typedef struct { dl_node_##name##_t *head[2]; } dl_list_##name##_t; \
	static inline dl_list_##name##_t *dl_init_##name(void) { return DL_CALLOC(dl_list_##name##_t, 1); } \
	static inline void dl_push_##name(dl_list_##name##_t *list, _type data, int dir) { \
		dl_node_##name##_t *p = DL_CALLOC(dl_node_##name##_t, 1); \
		dir = !!dir; \
		p->data = data; \
		if (list->head[0] == 0 && list->head[1] == 0) list->head[0] = list->head[1] = p; \
		else list->head[dir]->p[dir] = p, p->p[!dir] = list->head[dir], list->head[dir] = p; \
	} \
	static inline int dl_pop_##name(dl_list_##name##_t *list, _type *data, int dir) { \
		dl_node_##name##_t *p; \
		dir = !!dir; \
		if (list->head[0] == 0 && list->head[1] == 0) return 0; \
		else if (list->head[0] == list->head[1]) p = list->head[0], list->head[0] = list->head[1] = 0; \
		else p = list->head[dir], list->head[dir] = p->p[!dir], list->head[dir]->p[dir] = 0; \
		*data = p->data; \
		free(p); \
		return 1; \
	} \
	static inline void dl_destroy_##name(dl_list_##name##_t *list) { /* TODO: is this right? */ \
		dl_node_##name##_t *q, *p = list->head[0]; \
		while (p) { q = p->p[1]; free(p); p = q; } \
		free(list); \
	} \
	static inline int dl_empty_##name(const dl_list_##name##_t *list) { return (list == 0 || list->head[0] == 0); }

#define dl_list_t(name) dl_list_##name##_t

#define dl_init(name) dl_init_##name()
#define dl_destroy(name, list) dl_destroy_##name(list)
#define dl_push(name, list, data, dir) dl_push_##name(list, data, dir)
#define dl_pop(name, list, data, dir) dl_pop_##name(list, data, dir)
#define dl_empty(name, list) dl_empty_##name(list)

#endif
