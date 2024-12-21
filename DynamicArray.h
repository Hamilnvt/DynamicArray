#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct
{
  void **items;
  int count;
  int capacity;
  size_t typeSize;
} DynamicArray;

DynamicArray DA_create(size_t typeSize, int capacity);
DynamicArray DA_create_from_array(size_t typeSize, void **array, int length);

DynamicArray DA_clone_new_capacity(DynamicArray da, int capacity);
DynamicArray DA_clone(DynamicArray da);

void DA_resize(DynamicArray *da);

void DA_insert(DynamicArray *da, void *item, int index);
void DA_append(DynamicArray *da, void *item);
void DA_append_many(DynamicArray *da, void **items, int count);

void *DA_delete(DynamicArray *da, int index);
void *DA_pop(DynamicArray *da);

bool isEmpty(DynamicArray da);

void DA_free(DynamicArray *da);

void DA_print_info(DynamicArray da);
void print_int(void *_int);
void print_float(void *_float);
void print_char(void *_char);
void print_str(void *_str);
void print_pointer(void *_p);

#endif /* DYNAMIC_ARRAY_H */
