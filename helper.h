#ifndef HELPER_H
#define HELPER_H

typedef struct Item {
  int val;
  struct Item * next;
  int length;
} Array;

Array new_array(int i, ...);
char* array_join(Array *array, char *separator);
void array_foreach(Array *array, void (*cb)(int, int));
#endif

