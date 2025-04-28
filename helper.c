#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

Array new_array(int i, ...) {
  va_list args;
  va_start (args, i);

  Array *head = (Array *) malloc(sizeof(Array));
  head->val = i;
  head->next = NULL;
  Array *current_item = head;

  int total = 1;
  while ((i = va_arg(args, int))) {
    Array *new_item = (Array *) malloc(sizeof(Array));
    new_item->val = i;
    new_item->next = NULL;

    current_item->next = new_item;
    current_item = new_item;
    total++;
  }

  head->length = total;
  va_end(args);

  return *head;
}

char *array_join(Array *array, char* separator) {
  int separator_length = strlen(separator);
  char *output = (char *) malloc(sizeof(char) * array->length + separator_length + 1);
  if (output == NULL) {
    printf("Memory allocation failed!\n");
  }

  Array * current_item = array;
  int total = 0;
  while (current_item != NULL) {
    output[total] = current_item->val + '0';

    current_item = current_item->next;
    if (current_item != NULL) {
      for (int i = 0; i < separator_length; i++) {
        total++;
        output[total] = separator[i];
      }
    }
    total++;
  }
  output[total] = '\0';
  return output;
}

void array_foreach(Array *array, void (*cb)(int, int)) {
  Array *current_item = array;
  int index = 0;
  while (current_item != NULL) {
    cb(current_item->val, index);
    current_item = current_item->next;
    index++;
  }
}

Array array_filter(Array *array, int (*cb)(int, int)) {
  Array *output_array = (Array *) malloc(sizeof(Array));

  Array *current_item = array;
  Array *output_array_tail = output_array;
  int index = 0;
  int amount_pushed = 0;
  while (current_item != NULL) {
    if (cb(current_item->val, index) == 1) {
      if (amount_pushed != 0) {
        Array *new_item = (Array *) malloc(sizeof(Array));
        output_array_tail->next = new_item;
        output_array_tail = new_item;
      }
      output_array_tail->val = current_item->val;
      output_array_tail->next = NULL;
      amount_pushed ++;
    }
    current_item = current_item->next;
    index++;
  }

  output_array->length = amount_pushed;
  return *output_array;
}

int array_find(Array *array, int (*cb)(int, int)) {
  int found_num = -1;
  Array *current_item = array;

  int index = 0;
  while(current_item != NULL) {
    if (cb(current_item->val, index) == 1) {
      found_num = current_item->val;
      break;
    }
    current_item = current_item->next;
    index++;
  }

  return found_num;
}

Array array_map(Array *array, int (*cb)(int, int)) {
  Array *output_array = (Array *) malloc(sizeof(Array));

  int index = 0;
  Array *output_array_tail = output_array;
  Array *current_item = array;
  while (current_item != NULL) {
    if (index != 0) {
      Array *new_item = (Array *) malloc(sizeof(Array));
      output_array_tail->next = new_item;
      output_array_tail = new_item;
    }
    output_array_tail->val = cb(current_item->val, index);
    output_array_tail->next = NULL;
    current_item = current_item->next;
    index ++;
  }

  return *output_array;
}

