#ifndef DL_VOID_H
#define DL_VOID_H

struct dl_list_s; // opaque struct
typedef struct dl_list_s dl_list_t;

#ifdef __cplusplus
extern "C" {
#endif

dl_list_t *dl_init(void);
void dl_destroy(dl_list_t *list);
int dl_empty(const dl_list_t *list);
void dl_push(dl_list_t *list, void *data, int dir);
void *dl_pop(dl_list_t *list, int dir);

#ifdef __cplusplus
}
#endif

#endif
