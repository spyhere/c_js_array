#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_utils.h"
#include "logging.h"

Array *new_array(int i, ...) {
  va_list args;
  va_start (args, i);

  Array *p_head = (Array *) malloc(sizeof(Array));
  if (p_head == NULL) {
    ERROR("Memory allocation failed! new_array\n");
  }
  p_head->val = i;
  p_head->p_next = NULL;
  Array *p_current_item = p_head;

  int total = 1;
  while ((i = va_arg(args, int))) {
    Array *p_new_item = (Array *) malloc(sizeof(Array));
    if (p_new_item == NULL) {
      ERROR("Memory allocation failed! new_array while\n");
    }
    p_new_item->val = i;
    p_new_item->p_next = NULL;

    p_current_item->p_next = p_new_item;
    p_current_item = p_new_item;
    total++;
  }

  p_head->length = total;
  va_end(args);

  return p_head;
}

int *measure_array(Array *p_array, int *p_sum) {
  int *p_output = (int *) malloc(sizeof(int) * p_array->length);
  if (p_output == NULL) {
    ERROR("Memory allocation failed! measure_array\n");
  }

  int index = 0;
  int chars_sum = 0;
  Array *p_current_item = p_array;
  while (p_current_item != NULL) {
    int current_length = snprintf(NULL, 0, "%d", p_current_item->val);
    chars_sum += current_length;
    p_output[index] = current_length;

    p_current_item = p_current_item->p_next;
    index++;
  }

  *p_sum = chars_sum;
  return p_output;
}

char *int_to_str(int value, int size) {
  char *p_str = (char *) malloc(sizeof(char) * size + 1);
  if (p_str == NULL) {
    ERROR("Memory allocation failed! int_to_str\n");
  }
  sprintf(p_str, "%d", value);
  return p_str;
}

char *array_join(Array *p_array, char* p_separator) {
  if (p_array->length == 0) {
    return "";
  }

  int array_chars_sum = 0;
  int *p_array_char_lengths = measure_array(p_array, &array_chars_sum);
  int separator_length = strlen(p_separator);
  char *p_output = (char *) malloc(sizeof(char) * array_chars_sum + (separator_length * (p_array->length - 1)) + 1);
  if (p_output == NULL) {
    ERROR("Memory allocation failed! array_join\n");
  }

  Array *p_current_item = p_array;
  int str_index = 0;
  int index = 0;
  while (p_current_item != NULL) {
    char *p_int_str = int_to_str(p_current_item->val, p_array_char_lengths[index]);
    while (*p_int_str != '\0') {
      p_output[str_index] = *p_int_str;
      p_int_str++;
      str_index++;
    }
    free(p_int_str - p_array_char_lengths[index]);

    p_current_item = p_current_item->p_next;
    if (p_current_item != NULL) {
      for (int i = 0; i < separator_length; i++) {
        p_output[str_index] = p_separator[i];
        str_index++;
      }
    }
    index++;
  }
  p_output[str_index] = '\0';
  return p_output;
}

void array_foreach(Array *p_array, void (*p_cb)(int, int)) {
  if (p_array->length == 0) {
    return;
  }
  Array *p_current_item = p_array;
  int index = 0;
  while (p_current_item != NULL) {
    p_cb(p_current_item->val, index);
    p_current_item = p_current_item->p_next;
    index++;
  }
}

Array *array_filter(Array *p_array, int (*p_cb)(int, int)) {
  if (p_array->length == 0) {
    return p_array;
  }

  Array *p_output_array = (Array *) malloc(sizeof(Array));
  if (p_output_array == NULL) {
    ERROR("Memory allocation failed! array_filter\n");
  }

  Array *p_current_item = p_array;
  Array *p_output_array_tail = p_output_array;
  int index = 0;
  int amount_pushed = 0;
  while (p_current_item != NULL) {
    if (p_cb(p_current_item->val, index) == 1) {
      if (amount_pushed != 0) {
        Array *new_item = (Array *) malloc(sizeof(Array));
        if (new_item == NULL) {
          ERROR("Memory allocation failed! array_filter\n");
        }
        p_output_array_tail->p_next = new_item;
        p_output_array_tail = new_item;
      }
      p_output_array_tail->val = p_current_item->val;
      p_output_array_tail->p_next = NULL;
      amount_pushed ++;
    }
    p_current_item = p_current_item->p_next;
    index++;
  }

  p_output_array->length = amount_pushed;
  return p_output_array;
}

int array_find(Array *p_array, int (*p_cb)(int, int)) {
  if (p_array->length == 0) {
    return -1;
  }

  int found_num = -1;
  Array *p_current_item = p_array;

  int index = 0;
  while(p_current_item != NULL) {
    if (p_cb(p_current_item->val, index) == 1) {
      found_num = p_current_item->val;
      break;
    }
    p_current_item = p_current_item->p_next;
    index++;
  }

  return found_num;
}

Array *array_map(Array *p_array, int (*p_cb)(int, int)) {
  if (p_array->length == 0) {
    return p_array;
  }

  Array *p_output_array = (Array *) malloc(sizeof(Array));
  if (p_output_array == NULL) {
    ERROR("Memory allocation failed! array_map\n");
  }

  int index = 0;
  Array *p_output_array_tail = p_output_array;
  Array *p_current_item = p_array;
  while (p_current_item != NULL) {
    if (index != 0) {
      Array *p_new_item = (Array *) malloc(sizeof(Array));
      if (p_new_item == NULL) {
        ERROR("Memory allocation failed! array_map while\n");
      }
      p_output_array_tail->p_next = p_new_item;
      p_output_array_tail = p_new_item;
    }
    p_output_array_tail->val = p_cb(p_current_item->val, index);
    p_output_array_tail->p_next = NULL;
    p_current_item = p_current_item->p_next;
    index ++;
  }

  p_output_array->length = index + 1;
  return p_output_array;
}

int array_push(Array *p_array, int num) {
  if (p_array->length == 0) {
    p_array->val = num;
    p_array->length = 1;
    return p_array->length;
  }

  Array *p_current_item = p_array;
  while (p_current_item->p_next != NULL) {
    p_current_item = p_current_item->p_next;
  }

  Array *p_new_item = (Array *) malloc(sizeof(Array));
  if (p_new_item == NULL) {
    ERROR("Memory allocation failed! array_push\n");
  }
  p_new_item->val = num;
  p_new_item->p_next = NULL;
  p_current_item->p_next = p_new_item;

  p_array->length = p_array->length + 1;
  return p_array->length;
}

int array_pop(Array *p_array) {
  if (p_array->length == 1) {
    p_array->length = 0;
    int ret_value = p_array->val;
    p_array->val = 0;
    return ret_value;
  }

  int index = 0;
  int ret_value = -1;
  Array *p_current_item = p_array;
  while (p_current_item->p_next != NULL) {
    if (index == p_array->length - 2) {
      ret_value = p_current_item->p_next->val;
      Array *p_last_item = p_current_item->p_next;
      p_current_item->p_next = NULL;
      free(p_last_item);
      p_array->length = p_array->length - 1;
      break;
    }
    p_current_item = p_current_item->p_next;
    index++;
  }

  return ret_value;
}

int array_shift(Array **p_array) {
  if ((*p_array)->length == 0) {
    return -1;
  }
  if ((*p_array)->length == 1) {
    int ret_value = (*p_array)->val;
    (*p_array)->val = -1;
    (*p_array)->length = 0;
    return ret_value;
  }

  Array *p_head = *p_array;
  int ret_value = p_head->val;

  *p_array = (*p_array)->p_next;
  (*p_array)->length = p_head->length - 1;
  free(p_head);
  return ret_value;
}

int array_unshift(Array **p_array, int num) {
  if ((*p_array)->length == 0) {
    (*p_array)->length = 1;
    (*p_array)->val = num;
    return 1;
  }

  Array *p_new_head = (Array *) malloc(sizeof(Array));
  p_new_head->length = (*p_array)->length + 1;
  p_new_head->val = num;
  (*p_array)->length = -1;
  p_new_head->p_next = (*p_array);
  *p_array = p_new_head;
  return (*p_array)->length;
}

void array_sort(Array *p_array, int (*p_cb)(const void*, const void*)) {
  if (p_array->length < 2) {
    return;
  }

  int *p_temporary_arr = (int *) malloc(sizeof(int) * p_array->length);
  if (p_temporary_arr == NULL) {
    ERROR("Memory allocation failed! array_sort\n");
  }
  Array *p_current_item = p_array;
  int index = 0;
  while (p_current_item != NULL) {
    p_temporary_arr[index] = p_current_item->val;
    p_current_item = p_current_item->p_next;
    index++;
  }

  qsort(p_temporary_arr, p_array->length, sizeof(int), p_cb);

  p_current_item = p_array;
  for (int i = 0; i < p_array->length; i++) {
    p_current_item->val = p_temporary_arr[i];
    p_current_item = p_current_item->p_next;
  }
  free(p_temporary_arr);
}

Array *array_slice(Array *p_array, int start, int end) {
  Array *p_output_array = (Array *) malloc(sizeof(int) * p_array->length);
  if (p_array->length <= 1) {
    p_output_array->length = p_array->length;
    p_output_array->val = p_array->val;
    return p_output_array;
  }

  int is_start_valid = start >= 0 && start < p_array->length;
  int is_end_valid = end > start;
  if (!is_start_valid || !is_end_valid) {
    return p_output_array;
  }

  int index = 0;
  int amount_copied = 0;
  Array *p_cur_array_item = p_array;
  Array *p_cur_output_item = p_output_array;

  while (p_cur_array_item != NULL) {
    if (index >= start && index < end) {
      if (amount_copied != 0) {
        Array *p_new_item = (Array *) malloc(sizeof(Array));
        if (p_new_item == NULL) {
          ERROR("Memory allocation failed! array_slice while\n");
        }
        p_cur_output_item->p_next = p_new_item;
        p_cur_output_item = p_new_item;
      }
      p_cur_output_item->val = p_cur_array_item->val;
      amount_copied++;
    }

    p_cur_array_item = p_cur_array_item->p_next;
    index++;
  }

  p_output_array->length = amount_copied;
  return p_output_array;
}

Array *array_splice(Array **p_array, int start, int amount) {
  Array *p_output_array = (Array *) malloc(sizeof(Array));
  int is_start_valid = start >= 0 && start < (*p_array)->length;
  if (!is_start_valid) {
    return p_output_array;
  }

  int initial_arr_length = (*p_array)->length;
  int index = 0;
  int amount_copied = 0;
  Array **p_cur_array_item = p_array;
  Array *p_prev_array_item = NULL;
  Array *p_cur_output_item = p_output_array;

  while (*p_cur_array_item != NULL) {
    if (index++ < start) {
      p_prev_array_item = *p_cur_array_item;
      p_cur_array_item = &(*p_cur_array_item)->p_next;
      continue;
    }
    if (amount_copied >= amount) {
      break;
    }

    if (amount_copied != 0) {
      Array *p_new_item = (Array *) malloc(sizeof(Array));
      if (p_new_item == NULL) {
        ERROR("Memory allocation failed! array_splice while\n");
      }
      p_cur_output_item->p_next = p_new_item;
      p_cur_output_item = p_new_item;
    }
    p_cur_output_item->val = (*p_cur_array_item)->val;
    amount_copied++;

    Array *p_dead_item = *p_cur_array_item;
    if (p_prev_array_item == NULL) {
      *p_cur_array_item = (*p_dead_item).p_next;
    } else {
      p_prev_array_item->p_next = p_dead_item->p_next;
      /* Since previous line is doing exactly the same the next line is reduntant.
       * Explanation: p_prev_array_item->p_next === *p_cur_array_item and since we always
       * dereference p_cur_array_item it will give us the same pointer as p_prev_array_item->p_next.
       * Took me a while to understand...
       * */
      // p_cur_array_item = &p_prev_array_item->p_next;
    }
    free(p_dead_item);
  }

  p_output_array->length = amount_copied;
  (*p_array)->length = initial_arr_length - amount_copied;
  return p_output_array;
}

