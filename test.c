#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "cbst.h"

struct test_data {
   int key;
   unsigned int cookie;
};

int compare_test_data(const void *_a, const void *_b)
{
   const struct test_data *a=_a, *b=_b;
   return a->key - b->key;
}

void print_test_data(const void *_data)
{
   const struct test_data *data = _data;
   printf("key: %d cookie: 0x%08X\n", data->key, data->cookie);

   return;
}

int main()
{
   struct CBST *test = NULL;
   struct test_data mydata;
   char readbuf[1024];
   ssize_t bytes;

   for (;;) {
      printf("enter 'a <number>' to add, or 'd <number>' to delete\n");
      bytes = read(STDIN_FILENO, readbuf, sizeof(readbuf));
      if (0 == bytes) {
         print_data(test, sizeof(mydata), print_test_data);

         return 0;
      } else if (bytes < 3) {
         printf ("BAD INPUT! ");
      } else if ('a' == readbuf[0]) {
         mydata.key = atoi(&readbuf[1]);
         mydata.cookie = rand();
         test = add_data(test, &mydata, compare_test_data);
         if (NULL == test)
            printf("ERROR ADDING DATA! ");
         else
            print_data(test, sizeof(mydata), print_test_data);
      } else if ('d' == readbuf[0]) {
         mydata.key = atoi(&readbuf[1]);
         mydata.cookie = rand();
         if(delete_data(test, &mydata, compare_test_data))
            printf("COULD NOT DELETE! ");
         print_data(test, sizeof(mydata), print_test_data);
      } else if ('q' == readbuf[0]) {
         print_data(test, sizeof(mydata), print_test_data);

         return 0;
      } else {
         printf("BAD COMMAND! ");
      }
   }

   return 0;
}


