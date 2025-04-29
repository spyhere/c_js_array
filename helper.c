#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "logging.h"

Array *new_array(int i, ...) {
  va_list args;
  va_start (args, i);

  Array *head = (Array *) malloc(sizeof(Array));
  if (head == NULL) {
    ERROR("Memory allocation failed! new_array\n");
  }
  head->val = i;
  head->next = NULL;
  Array *current_item = head;

  int total = 1;
  while ((i = va_arg(args, int))) {
    Array *new_item = (Array *) malloc(sizeof(Array));
    if (new_item == NULL) {
      ERROR("Memory allocation failed! new_array while\n");
    }
    new_item->val = i;
    new_item->next = NULL;

    current_item->next = new_item;
    current_item = new_item;
    total++;
  }

  head->length = total;
  va_end(args);

  return head;
}

int *measure_array(Array *array, int *sum) {
  int *output = (int *) malloc(sizeof(int) * array->length);
  if (output == NULL) {
    ERROR("Memory allocation failed! measure_array\n");
  }

  int index = 0;
  int chars_sum = 0;
  Array *current_item = array;
  while (current_item != NULL) {
    int current_length = snprintf(NULL, 0, "%d", current_item->val) + 1;
    chars_sum += current_length;
    output[index] = current_length;

    current_item = current_item->next;
    index++;
  }

  *sum = chars_sum;
  return output;
}

char *int_to_str(int value, int size) {
  char *str = (char *) malloc(sizeof(char) * size);
  if (str == NULL) {
    ERROR("Memory allocation failed! int_to_str\n");
  }
  sprintf(str, "%d", value);
  return str;
}

char *array_join(Array *array, char* separator) {
  if (array->length == 0) {
    return "";
  }

  int array_chars_sum = 0;
  int *array_char_lengths = measure_array(array, &array_chars_sum);
  int separator_length = strlen(separator);
  char *output = (char *) malloc(sizeof(char) * array_chars_sum + (separator_length * (array->length - 1)) + 1);
  if (output == NULL) {
    ERROR("Memory allocation failed! array_join\n");
  }

  Array * current_item = array;
  int str_index = 0;
  int index = 0;
  while (current_item != NULL) {
    char *int_str = int_to_str(current_item->val, array_char_lengths[index]);
    while (*int_str != '\0') {
      output[str_index] = *int_str;
      int_str++;
      str_index++;
    }

    current_item = current_item->next;
    if (current_item != NULL) {
      for (int i = 0; i < separator_length; i++) {
        output[str_index] = separator[i];
        str_index++;
      }
    }
    index++;
  }
  output[str_index] = '\0';
  return output;
}

void array_foreach(Array *array, void (*cb)(int, int)) {
  if (array->length == 0) {
    return;
  }
  Array *current_item = array;
  int index = 0;
  while (current_item != NULL) {
    cb(current_item->val, index);
    current_item = current_item->next;
    index++;
  }
}

Array *array_filter(Array *array, int (*cb)(int, int)) {
  if (array->length == 0) {
    return array;
  }

  Array *output_array = (Array *) malloc(sizeof(Array));
  if (output_array == NULL) {
    ERROR("Memory allocation failed! array_filter\n");
  }

  Array *current_item = array;
  Array *output_array_tail = output_array;
  int index = 0;
  int amount_pushed = 0;
  while (current_item != NULL) {
    if (cb(current_item->val, index) == 1) {
      if (amount_pushed != 0) {
        Array *new_item = (Array *) malloc(sizeof(Array));
        if (new_item == NULL) {
          ERROR("Memory allocation failed! array_filter\n");
        }
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
  return output_array;
}

int array_find(Array *array, int (*cb)(int, int)) {
  if (array->length == 0) {
    return -1;
  }

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

Array *array_map(Array *array, int (*cb)(int, int)) {
  if (array->length == 0) {
    return array;
  }

  Array *output_array = (Array *) malloc(sizeof(Array));
  if (output_array == NULL) {
    ERROR("Memory allocation failed! array_map\n");
  }

  int index = 0;
  Array *output_array_tail = output_array;
  Array *current_item = array;
  while (current_item != NULL) {
    if (index != 0) {
      Array *new_item = (Array *) malloc(sizeof(Array));
      if (new_item == NULL) {
        ERROR("Memory allocation failed! array_map while\n");
      }
      output_array_tail->next = new_item;
      output_array_tail = new_item;
    }
    output_array_tail->val = cb(current_item->val, index);
    output_array_tail->next = NULL;
    current_item = current_item->next;
    index ++;
  }

  output_array->length = index + 1;
  return output_array;
}

int array_push(Array *array, int num) {
  if (array->length == 0) {
    array->val = num;
    array->length = 1;
    return array->length;
  }

  Array *current_item = array;
  while (current_item->next != NULL) {
    current_item = current_item->next;
  }

  Array *new_item = (Array *) malloc(sizeof(Array));
  if (new_item == NULL) {
    ERROR("Memory allocation failed! array_push\n");
  }
  new_item->val = num;
  new_item->next = NULL;
  current_item->next = new_item;

  array->length = array->length + 1;
  return array->length;
}

int array_pop(Array *array) {
  if (array->length == 1) {
    array->length = 0;
    int ret_value = array->val;
    array->val = 0;
    return ret_value;
  }

  int index = 0;
  int ret_value = -1;
  Array *current_item = array;
  while (current_item->next != NULL) {
    if (index == array->length - 2) {
      ret_value = current_item->next->val;
      Array *last_item = current_item->next;
      current_item->next = NULL;
      free(last_item);
      array->length = array->length - 1;
      break;
    }
    current_item = current_item->next;
    index++;
  }

  return ret_value;
}

int array_shift(Array **array) {
  if ((*array)->length == 0) {
    return -1;
  }
  if ((*array)->length == 1) {
    int ret_value = (*array)->val;
    (*array)->val = -1;
    (*array)->length = 0;
    return ret_value;
  }

  Array *head = *array;
  int ret_value = head->val;

  *array = (*array)->next;
  (*array)->length = head->length - 1;
  free(head);
  return ret_value;
}

