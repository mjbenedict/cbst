#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

struct CBST {
	uint32_t length;
	uint32_t capacity;
	uint8_t  data[0];
};

extern struct CBST *_add_data(struct CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b));
#define add_data(a, b, c) _add_data(a, b, sizeof(*b), c)
extern int _delete_data(struct CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b));
#define delete_data(a, b, c) _delete_data(a, b, sizeof(*b), c)
extern void *_find_data(struct CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b));
#define find_data(a, b, c) _find_data(a, b, sizeof(*b), c)
extern void print_data(const struct CBST *root, size_t datalen, void (*print)(const void *data));

