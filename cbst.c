#include <string.h>
#include <strings.h>
#include "cbst.h"

static const size_t MIN_ELEMENTS = 8;
static void *scratch = NULL;
static size_t scratch_len = 0;

/*
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
*/

void do_print_cbst_in_order(const void *buf, int start, size_t count, size_t datalen, void (*print)(const void *))
{
	if (start < count)
	{
		do_print_cbst_in_order(buf, start*2, count, datalen, print);
      print(buf+start*datalen);
		do_print_cbst_in_order(buf, start*2+1, count, datalen, print);
	}

   return;
}

void print_data(const struct CBST *root, size_t datalen, void (*print)(const void *data))
{
   void *treestart = (void *)(&root->data - datalen);
   do_print_cbst_in_order(treestart, 0, root->length, datalen, print);
}

void array_to_tree(void *tree, size_t length, size_t datalen)
{
   size_t span = ffs(length);
   size_t index = 1;
   size_t iter;
   size_t byteoff;

   while (span > 0) {
     iter = 1;
     while (span*iter-1 < length) {
         byteoff = (span*iter-1)*datalen;
         memcpy(tree+index*datalen, scratch+byteoff, datalen);
         iter += 2;
         index++;
      }
   }

   return;
}

void do_add(void *tree, size_t length, void *data, size_t datalen,
      int (*compare)(const void *a, const void *b))
{
   size_t index = 1;
   size_t span = ffs(length);
   size_t iter;
   size_t byteoff;
   int inserted = 0;

   while (span) {
     iter = 1;
     while (span*iter-1 < length) {
       // todo - refactor iter to be a bitshift so we don't have to multiple
       // here... assuming the compiler doesn't catch that for us
       byteoff = (span*iter-1)*datalen;
        if (!inserted && compare(scratch+byteoff, tree+index*datalen)) {
           memcpy(scratch+byteoff, data, datalen);
           inserted = 1;
        } else {
           memcpy(scratch+byteoff, tree+index*datalen, datalen);
           iter += 2;
        }
       index++;
     }
     span /= 2;
   }

   if(!inserted)
      memcpy(scratch+datalen*length, data, datalen);

   array_to_tree(tree, length+1, datalen);

   return;
}

struct CBST *_add_data(struct CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b))
{
	struct CBST *tmp;
   size_t in_start = ffs(root->length);
   size_t out_start = ffs(root->length+1);

   if (NULL == scratch) {
      scratch_len = MIN_ELEMENTS;
      scratch = malloc(datalen*MIN_ELEMENTS);
      if (NULL == scratch) {
         return NULL;
      }
   }
   if (scratch_len <= root->length+1) {
      scratch_len *= 2;
      tmp = realloc(scratch, datalen*scratch_len);
      if (NULL == tmp) {
         scratch_len /= 2;
         return tmp;
      }
      scratch = tmp;
   }

	if (NULL == root) {
		root = malloc(sizeof(struct CBST) + datalen*MIN_ELEMENTS);
		if (NULL == root) {
			return root;
		}
		root->length = 1;
		root->capacity = MIN_ELEMENTS;
	} else if (++(root->length) > root->capacity) {
		root->capacity *= 2;
		tmp = realloc(root, sizeof(struct CBST) + datalen*root->capacity);
		if (NULL == tmp) {
			root->capacity /= 2;
			return tmp;
		}
		root = tmp;
   }

   do_add(&root->data - datalen, root->length++, data, datalen, compare);

   return root;
}

int _delete_data(struct CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b))
{
   void *treestart = &root->data - datalen;
   size_t span = ffs(root->length);
   size_t index = 1;
   size_t iter;
   size_t byteoff;
   int found = 0;

   while (span > 0) {
      iter = 1;
      while (span*iter-1 < root->length) {
         // todo - refactor iter to be a bitshift so we don't have to multiple
         // here... assuming the compiler doesn't catch that for us
         byteoff = (span*iter-1)*datalen;
         if (0 == compare(scratch+byteoff, treestart+index*datalen))
            found = 1;
         else {
            memcpy(scratch+byteoff, treestart+index*datalen, datalen);
            iter += 2;
         }
         index++;
      }
      span /= 2;
   }

   if (found)
      root->length--;
      
   array_to_tree(treestart, root->length, datalen);

   return !found;
}

void *_find_data(struct CBST *root, void *data, size_t datalen,
		int (*compare)(const void *a, const void *b))
{
   void *treestart = &root->data - datalen;
   size_t index = 1;
   size_t byteoff;
   int result;

   while (index <= root->length) {
      byteoff = index*datalen;
      result = compare(treestart+byteoff, data);
      if (0 == result)
         return treestart+byteoff;
      else if (result > 0)
         index = index*2+1;
      else
         index = index*2;
   }

   return NULL;
}
