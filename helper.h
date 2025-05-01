#ifndef HELPER_H
#define HELPER_H

typedef struct Item {
  int val;
  struct Item *next;
  int length;
} Array;

Array *new_array(int i, ...);
char *array_join(Array *array, char *separator);
void array_foreach(Array *array, void (*cb)(int, int));
Array *array_filter(Array *array, int (*cb)(int, int));
int array_find(Array *array, int (*cb)(int, int));
Array *array_map(Array *array, int (*cb)(int, int));
int array_push(Array *array, int num);
int array_pop(Array *array);
int array_shift(Array **array);
int array_unshift(Array **array, int num);
void array_sort(Array *array, int (*cb)(const void*, const void*));
Array *array_slice(Array *array, int start, int end);
Array *array_splice(Array **array, int start, int amount);
#endif

