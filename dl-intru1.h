#ifndef DL_INTRU1_H
#define DL_INTRU1_H

#define DL_HEAD(_type) struct { _type *p[2]; }

#define DL_IMPL(suf, _type, _head) \
	static inline void dl_push_##suf(_type *head[2], _type *p, int dir) { \
		dir = !!dir; /* 0 or 1 */ \
		p->_head.p[0] = p->_head.p[1] = 0; \
		if (head[0] == 0 && head[1] == 0) head[0] = head[1] = p; \
		else head[dir]->_head.p[dir] = p, p->_head.p[!dir] = head[dir], head[dir] = p; \
	} \
	static inline _type *dl_pop_##suf(_type *head[2], int dir) { \
		_type *p; \
		dir = !!dir; \
		if (head[0] == 0 && head[1] == 0) return 0; \
		else if (head[0] == head[1]) p = head[0], head[0] = head[1] = 0; \
		else p = head[dir], head[dir] = p->_head.p[!dir], head[dir]->_head.p[dir] = 0; \
		return p; \
	}

#define dl_push(suf, head, p, dir) dl_push_##suf(head, p, dir)
#define dl_pop(suf, head, dir) dl_pop_##suf(head, dir)

#endif
