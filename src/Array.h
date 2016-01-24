#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stddef.h>

#define foreach(iterator, array)\
    for(size_t iterator = Array_size(array) - 1;\
        iterator < Array_size(array); iterator--)

#ifdef __cplusplus
    extern "C" {
#endif

typedef struct Array Array;

Array* Array_create  (void);
void   Array_destroy (Array** array);

bool   Array_insert  (Array* self, size_t index, void* value);
bool   Array_remove  (Array* self, size_t index);
void   Array_print   (const Array* self);
size_t Array_size    (const Array* self);
void*  Array_get     (const Array* self, size_t index);

#ifdef __cplusplus
    }
#endif

#endif
