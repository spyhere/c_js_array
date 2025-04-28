#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

void foreach_cb(int num, int index) {
  printf("Num is %d with index %d\n", num, index);
}

int filter_cb(int num, int index) {
  return num % 2 == 0;
}

int main() {
  Array array = new_array(1,4,3,4,0);
  printf("My new array is %s\n", array_join(&array, "-**-"));
  array_foreach(&array, &foreach_cb);
  Array filtered_array = array_filter(&array, &filter_cb);
  printf("My filtered array is %s\n", array_join(&filtered_array, ", "));
  printf("My original array is still %s\n", array_join(&array, "-**-"));
  // TODO:
  // 1. Make array_join to work with digits bigger than 0-9
  // 2. array_foreach +
  // 3. array_filter +
  // 4. array_find
  // 5. array_map
  // 6. array_push
  // 7. array_pop
  // 8. array_shift
  // 9. array_unshift
  // 10. array_sort
  // 11??? splice/slice
  return 0;
}

