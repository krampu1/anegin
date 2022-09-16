#ifndef SORT
#define SORT

#include <stdio.h>
void KR_sort(void *data, size_t data_size, size_t element_size, int (* cmp) (const void *, const void *));

void KR_qsort(void *data, size_t data_size, size_t element_size, int (* cmp) (const void *, const void *));

#endif