// no "#ifndef" guard as this header may be included multiple times

// see dl-intru2.* for details on the methodology

#define DL_CALLOC(type, len) (type*)calloc((len), sizeof(type))

#define DL_TOKCAT(pre, suf) pre ##_## suf

#define DL_NODE_S(suf) DL_TOKCAT(dl_node_s, suf)
#define DL_NODE_T(suf) DL_TOKCAT(dl_node_t, suf)
#define DL_LIST_T(suf) DL_TOKCAT(dl_list_t, suf)

#define DL_INIT(suf) DL_TOKCAT(dl_init, suf)
#define DL_PUSH(suf) DL_TOKCAT(dl_push, suf)
#define DL_POP(suf) DL_TOKCAT(dl_pop, suf)
#define DL_EMPTY(suf) DL_TOKCAT(dl_empty, suf)
#define DL_DESTROY(suf) DL_TOKCAT(dl_destroy, suf)

typedef struct DL_NODE_S(DL_NAME) {
	DL_TYPE data;
	struct DL_NODE_S(DL_NAME) *p[2];
} DL_NODE_T(DL_NAME);

typedef struct {
	DL_NODE_T(DL_NAME) *head[2];
} DL_LIST_T(DL_NAME);

DL_LIST_T(DL_NAME) *DL_INIT(DL_NAME)(void)
{
	return DL_CALLOC(DL_LIST_T(DL_NAME), 1);
}

void DL_PUSH(DL_NAME)(DL_LIST_T(DL_NAME) *list, DL_TYPE data, int dir)
{
	DL_NODE_T(DL_NAME) *p = DL_CALLOC(DL_NODE_T(DL_NAME), 1);
	dir = !!dir;
	p->data = data;
	if (list->head[0] == 0 && list->head[1] == 0) list->head[0] = list->head[1] = p;
	else list->head[dir]->p[dir] = p, p->p[!dir] = list->head[dir], list->head[dir] = p;
}

int DL_POP(DL_NAME)(DL_LIST_T(DL_NAME) *list, DL_TYPE *data, int dir)
{
	DL_NODE_T(DL_NAME) *p;
	dir = !!dir;
	if (list->head[0] == 0 && list->head[1] == 0) return 0;
	else if (list->head[0] == list->head[1]) p = list->head[0], list->head[0] = list->head[1] = 0;
	else p = list->head[dir], list->head[dir] = p->p[!dir], list->head[dir]->p[dir] = 0;
	*data = p->data;
	free(p);
	return 1;
}

int DL_EMPTY(DL_NAME)(const DL_LIST_T(DL_NAME) *list)
{
	return (list == 0 || list->head[0] == 0);
}

void DL_DESTROY(DL_NAME)(DL_LIST_T(DL_NAME) *list)
{
	DL_NODE_T(DL_NAME) *q, *p = list->head[0];
	while (p) { q = p->p[1]; free(p); p = q; }
	free(list);
}
