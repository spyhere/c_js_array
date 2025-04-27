#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"


int main() {
  Array array = new_array(1,4,3,4,0);
  char *array_joined = array_join(&array, "-**-");
  printf("My array is %s\n", array_joined);
  return 0;
}

