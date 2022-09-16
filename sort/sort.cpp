#include "sort.h"
#include <random>
#include <assert.h>

void KR_swap_data(void *a, void *b, long long n) {
    assert(a != nullptr);
    assert(b != nullptr);

    for (long long i = 0; i < n ; i++) {
        char p = *((char *)a + i);
        *((char *)a + i) = *((char *)b + i);
        *((char *)b + i) = p;
    }
}

void KR_sort(void *data, int data_size, int element_size, int (* cmp) (const void *, const void *)) {
    assert(data != nullptr);

    for (int a = 0; a < data_size; a++) {
        for (int i = 1; i < data_size; i++){
            if (cmp((char *)data + i * element_size, (char *)data + (i - 1) * element_size) <= 0){
                KR_swap_data((char *)data + i * element_size, (char *)data + (i - 1) * element_size, element_size);
            }
        }
    }
}

void KR_qsort(void *data, int data_size, int element_size, int (* cmp) (const void *, const void *)) {
    assert(data != nullptr);

    if (data_size <= 1) {
        return;
    }

    int m = rand()%data_size;
    int l = 0;

    for (int r = 0; r < data_size; r++){
        if (cmp((char *)data + r * element_size, (char *)data + m * element_size) <= 0) {
            KR_swap_data((char *)data + r * element_size, (char *)data + l * element_size, element_size);

            if (r == m) {
                m = l;
            }

            l++;
        }
    }
    if (l != 0 && l != data_size){
        KR_qsort(data, l, element_size, cmp);
        KR_qsort((char *)data + l * element_size, data_size - l, element_size, cmp);
    }
}