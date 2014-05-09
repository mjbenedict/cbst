#include <stdint.h>

struct CBST {
	uint32_t length;
	uint32_t capacity;
	uint8_t  data[0];
};

struct CBST *add_data(CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b));
#define add_data(a, b, c) add_data(a, b, sizeof(*b), c)
void *delete_data(CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b));
#define delete_data(a, b, c) delete_data(a, b, sizeof(*b), c)
void *find_data(CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b));
#define find_data(a, b, c) delete_data(a, b, sizeof(*b), c)
