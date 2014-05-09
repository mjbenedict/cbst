#include <string.h>
#include "cbst.h"

static const MIN_ELEMENTS = 8;
static void *scratch = NULL;
static size_t scratch_len = 0;

static void flatten(CBST *root, void *and, void *except, size_t datalen,
		int (*compare)(const void *a, const void *b))
{
	void *dest, *src;

	if (root->length > scratch_len)
	{
		scratch_len = 1<<(ffs(root->length)+1);
		scratch = realloc(stratch, scratch_len);
	}

	src = &root->data;
	dest = scratch + datalen * root->length/2;
	memcpy(dest, src, datalen);

}
data:
             14
         /         \
        6                  20
       /  \               /    \
     4      9           16        25
   /  \    /  \        /  \       / 
  2    5  7     11   15     18   22  

tree_index:
             0 
         /         \
        1                  2
       /  \               /    \
     3      4           5        6
   /  \    /  \        /  \       / 
  7    8  9     10   11     12   13 

sorted_array_index:
             7 
         /         \
        3                  11
       /  \               /    \
     1      5            9       13
   /  \    /  \        /  \       / 
  0    2  4     6   8    10   12 

  0 -> 7   0000b -> 0111b
  1 -> 3   0001b -> 0011b
  2 -> 11  0010b -> 1011b
  3 -> 1   0011b -> 0001b
  4 -> 5   0100b -> 0101b
  5 -> 9   0101b -> 1001b
  6 -> 13  0110b -> 1101b
  7 -> 0   0111b -> 0000b
  8 -> 2   1000b -> 0010b
  9 -> 4   1001b -> 0100b
 10 -> 6   1010b -> 0110b
 11 -> 8   1011b -> 1000b
 12 -> 10  1100b -> 1010b
 13 -> 12  1101b -> 1100b


  3,1,5,0,2,4
 [6,4,9,2,5,7]

  3,1,4,0,5,2
 [2,4,5,6,7,9]


flatten (int index, int *bst, int *a, size_t len)
{
	bst[index];
}

{
	
	out[0]  = cbst[1<<ffs(cbst[length])];
}

print_bst_in_order(int *buf, int start, size_t count)
{
	if (start < count)
	{
		print_bst_in_order(buf, start*2, count);
		printf("%d, ", buf[start]);
		print_bst_in_order(buf, start*2+1, count);
	}
}

print_bst_in_order(int *buf, size_t count)
{
	start = fss(count);
	for(;;)
	{
		printf("%d, ", buf[start]);
		printf("%d, ", buf[start/2]);
		if (count >= start+1) {
			printf("%d, ", buf[++start]);
		}
		start = start/2+1;
	}
}

void flatten (void *in, void *out, size_t datalen, size_t count)
{
   size_t span = count/2;
   size_t node = 0;
   size_t out_index = 0;

   while (span > 0)
   {
      memcpy(out+out_index*datalen, in+span*
      out_index
      span /= 2;
      node = 0;
   }

}

struct CBST *add_data(CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b))
{
	CBST *tmp;
   static void *buf = NULL;
   static size_t capacity = 0;
   size_t in_start = fss(root->length);
   size_t out_start = fss(root->length+1);

   if (NULL == buf) {
      capacity = MIN_ELEMENTS;
      buf = malloc(datalen*MIN_ELEMENTS);
      if (NULL == buf) {
         return NULL
      }
   }
   if (capacity <= root->length+1) {
      capacity *= 2;
      tmp = realloc(buf, datalen*capacity);
      if (NULL == tmp) {
         capacity /= 2;
         return tmp;
      }
      buf = tmp;
   }

	if (NULL == root) {
		root = malloc(sizeof(CBST) + datalen*MIN_ELEMENTS);
		if (NULL == root) {
			return root;
		}
		root->length = 1;
		root->capacity = MIN_ELEMENTS;
	} else if (++(root->length) > capacity) {
		root->capacity *= 2;
		tmp = realloc(root, sizeof(CBST) +  datalen*root->capacity);
		if (NULL == tmp) {
			root->capacity /= 2;
			return tmp;
		}
		root = tmp;
   }



  

	

