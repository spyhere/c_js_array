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

int find_cb(int num, int index) {
  return (num > 1) && (num < 4);
}

int map_cb(int num, int index) {
  return (num + index) * 2;
}
int sort_cb(const void *a, const void *b) {
  const int arg_a = *(const int*)a;
  const int arg_b = *(const int*)b;
  return (arg_a > arg_b) - (arg_a < arg_b);
}

int main() {
  Array *array = new_array(1,4,3,4, 100000, 99992929, -10, 0);
  printf("My new array is %s\n", array_join(array, "-**-"));
  array_foreach(array, &foreach_cb);
  Array *filtered_array = array_filter(array, &filter_cb);
  printf("My filtered array is %s\n", array_join(filtered_array, ", "));
  printf("My original array is still %s\n", array_join(array, "-"));
  printf("Found digit is %d\n", array_find(array, &find_cb));
  Array *mapped_array = array_map(array, &map_cb);
  printf("Mapped new array: %s\n", array_join(mapped_array, ", "));
  array_push(array, 11);
  printf("Original array after push operation: %s\n", array_join(array, ", "));
  printf("Retained value is %d\n", array_pop(array));
  printf("My current array is %s\n", array_join(array, ", "));
  printf("Shifted value is %d\n", array_shift(&array));
  printf("My new array is %s\n", array_join(array, ", "));
  array_unshift(&array, 99);
  printf("My current array is %s\n", array_join(array, ", "));
  array_sort(array, &sort_cb);
  printf("Array after sort: %s\n", array_join(array, ", "));
  Array *sliced_array = array_slice(array, 3, 5);
  printf("Sliced array: %s\n", array_join(sliced_array, ", "));
  printf("My initial array is still %s\n", array_join(array, ", "));
  Array *removed_elements = array_splice(&array, 6, 2);
  printf("Removed elements are %s\n", array_join(removed_elements, ", "));
  printf("My initial array has become %s\n", array_join(array, ", "));
  return 0;
}

