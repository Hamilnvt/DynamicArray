#include "DynamicArray.h"

#include <stdio.h>
#include <stdlib.h>

DynamicArray DA_create(size_t typeSize, int capacity)
{
  DynamicArray da = {0};
  da.items = (void **)malloc(capacity*sizeof(typeSize));
  da.count = 0;
  da.typeSize = typeSize;
  da.capacity = capacity;
  return da;
}

DynamicArray DA_create_from_array(size_t typeSize, void **array, int length) //TODO
{
  printf("Creating da from array\n");
  DynamicArray da = DA_create(typeSize, length);
  for (int i = 0; i < length; i++) {
    printf("appending %d\n", *(int *)array[i]);
    DA_append(&da, array[i]);
  }
  return da;
}

void DA_resize(DynamicArray *da)
{
  //printf("Current capacity: %d.\t", da->capacity);
  size_t new_capacity;
  if (da->count >= 3*da->capacity/4) {
    new_capacity = da->capacity*2;
    //printf("Resize (double): %d\n", new_capacity); 
    da->items = (void **)reallocarray(da->items, new_capacity, sizeof(da->typeSize));
  }
  else if (da->count < da->capacity/4) {
    new_capacity = da->capacity/2;
    //printf("Resize (half): %d\n", new_capacity);
    // questo è solo per precauzione, forse (TODO)
    for (int i = da->count; i < da->capacity; i++) {
      if (da->items[i]) {
	printf("you're free now\n");
	free(da->items[i]);
      }
    }
  }
  else return;

  da->capacity = new_capacity;
}

DynamicArray DA_clone_new_capacity(DynamicArray da, int capacity)
{
  printf("Cloning Dynamic Array\n");
  DynamicArray clone = DA_create(da.typeSize, capacity);
  
  printf("  Cloned type size: %d\n", clone.typeSize);
  printf("  Cloned capacity: %d\n", clone.capacity);
  for (size_t i = 0; i < da.count; i++) {
    if (i == clone.capacity) break;
    DA_append(&clone, da.items[i]);
  }
  printf("  Cloned items count: %d\n", clone.count);
  return clone;
}
DynamicArray DA_clone(DynamicArray da)
{
  return DA_clone_new_capacity(da, da.capacity);
}

void DA_insert(DynamicArray *da, void *item, int index)
{
  if (!item) return;
  da->items[da->count] = malloc(da->typeSize);
  for (int i = da->count; i >= index+1; i--) {
    memcpy(da->items[i], da->items[i-1], da->typeSize);
  }
  memcpy(da->items[index], item, da->typeSize);
  da->count++;
  DA_resize(da);
}

void DA_append(DynamicArray *da, void *item)
{
  DA_insert(da, item, da->count);
}

void DA_append_many(DynamicArray *da, void **items, int count)
{
  if (!items) return;
  for (int i = 0; i < count; i++) DA_append(da, items[i]);
}

void *DA_delete(DynamicArray *da, int index)
{
  if (isEmpty(*da) || index >= da->count) return NULL;
  void *item = malloc(da->typeSize);
  memcpy(item, da->items[index], da->typeSize);
  for (int i = index; i < da->count-1; i++) {
    memcpy(da->items[i], da->items[i+1], da->typeSize);
  }
  da->count--;
  da->items[da->count] = NULL;
  DA_resize(da);
  return item;
  // rember to free
}

void *DA_pop(DynamicArray *da)
{
  return DA_delete(da, da->count-1);
}

bool isEmpty(DynamicArray da) { return da.count == 0; }

void DA_free(DynamicArray *da)
{
  void *item;
  for (int i = 0; i < da->capacity; i++) {
    item = da->items[i];
    if (item) free(item);
  }
  free(da->items);
  //printf("Dynamic Array freed\n");
}

void DA_print_info(DynamicArray da)
{
  printf("Printing Dynamic Array:\n");
  printf("  Type size:  %zu\n", da.typeSize);
  printf("  Capacity:  %d\n", da.capacity);
  printf("  Count: %d\n", da.count);
}
