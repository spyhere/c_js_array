#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "array_utils.h"

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
int sort_cb(const void *p_a, const void *p_b) {
  const int a = *(const int*)p_a;
  const int b = *(const int*)p_b;
  return (a > b) - (a < b);
}

int main() {
  /* new_array */
  Array *p_array = new_array(1,4,3,4, 100000, 99992929, -10, 0);
  printf("My new array is %s\n", array_join(p_array, " ** "));

  /* array_foreach */
  array_foreach(p_array, &foreach_cb);

  /* array_filter */
  Array *p_filtered_array = array_filter(p_array, &filter_cb);
  printf("My filtered array: %s\n", array_join(p_filtered_array, ", "));
  printf("My original array: %s\n", array_join(p_array, "-"));

  /* array_find */
  printf("Found digit: %d\n", array_find(p_array, &find_cb));

  /* array_map */
  Array *p_mapped_array = array_map(p_array, &map_cb);
  printf("Mapped new array: %s\n", array_join(p_mapped_array, ", "));

  /* array_push */
  array_push(p_array, 11);
  printf("Original array after push operation: %s\n", array_join(p_array, ", "));

  /* array_pop */
  printf("Retained value: %d\n", array_pop(p_array));
  printf("My current array: %s\n", array_join(p_array, ", "));

  /* array_shift */
  printf("Shifted value: %d\n", array_shift(&p_array));
  printf("My original array: %s\n", array_join(p_array, ", "));

  /* array_unshift*/
  array_unshift(&p_array, 99);
  printf("Original array after unshift: %s\n", array_join(p_array, ", "));

  /* array_sort */
  array_sort(p_array, &sort_cb);
  printf("Array after sort: %s\n", array_join(p_array, ", "));

  /* array_slice */
  Array *p_sliced_array = array_slice(p_array, 3, 5);
  printf("Sliced array: %s\n", array_join(p_sliced_array, ", "));
  printf("My initial array is still: %s\n", array_join(p_array, ", "));

  /* array_splice */
  Array *p_removed_elements = array_splice(&p_array, 6, 2);
  printf("Removed elements: %s\n", array_join(p_removed_elements, ", "));
  printf("My initial array has become: %s\n", array_join(p_array, ", "));

  return 0;
}

