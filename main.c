#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"


int main() {
  Array array = new_array(1,4,3,4,0);
  char *array_joined = array_join(&array, "-**-");
  printf("My array is %s\n", array_joined);
  // TODO:
  // 1. Make array_join to work with digits bigger than 0-9
  // 2. array_foreach
  // 3. array_filter
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

