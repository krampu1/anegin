#include "sort.h"
#include <random>
#include <assert.h>

void KR_swap_data(void *a, void *b, size_t n) {
    assert(a != nullptr);
    assert(b != nullptr);

    for (size_t i = 0; i < n / sizeof(int64_t) ; i++) {
        int64_t p = *((int64_t *)a + i);
        *((int64_t *)a + i) = *((int64_t *)b + i);
        *((int64_t *)b + i) = p;
    }

    if (n % sizeof(int64_t) >= sizeof(int32_t)) {
        int32_t p = *((int32_t *)a + (n - n % sizeof(int64_t)));
        *((int32_t *)a + (n - n % sizeof(int64_t))) = *((int32_t *)b + (n - n % sizeof(int64_t)));
        *((int32_t *)b + (n - n % sizeof(int64_t))) = p;
    }

    if (n % sizeof(int32_t) >= sizeof(int16_t)) {
        int16_t p = *((int16_t *)a + (n - n % sizeof(int32_t)));
        *((int16_t *)a + (n - n % sizeof(int32_t))) = *((int16_t *)b + (n - n % sizeof(int32_t)));
        *((int16_t *)b + (n - n % sizeof(int32_t))) = p;
    }

    if (n % sizeof(int16_t) >= sizeof(int8_t)) {
        int8_t p = *((int8_t *)a + (n - n % sizeof(int16_t)));
        *((int8_t *)a + (n - n % sizeof(int16_t))) = *((int8_t *)b + (n - n % sizeof(int16_t)));
        *((int8_t *)b + (n - n % sizeof(int16_t))) = p;
    }
}

void KR_sort(void *data, size_t data_size, size_t element_size, int (* cmp) (const void *, const void *)) {
    assert(data != nullptr);

    for (size_t a = 0; a < data_size; a++) {
        for (size_t i = 1; i < data_size; i++){
            if (cmp((char *)data + i * element_size, (char *)data + (i - 1) * element_size) <= 0){
                KR_swap_data((char *)data + i * element_size, (char *)data + (i - 1) * element_size, element_size);
            }
        }
    }
}

void KR_qsort(void *data, size_t data_size, size_t element_size, int (* cmp) (const void *, const void *)) {
    assert(data != nullptr);

    if (data_size <= 1) {
        return;
    }

    size_t m = rand()%data_size;
    size_t l = 0;

    for (size_t r = 0; r < data_size; r++){
        if (cmp((char *)data + r * element_size, (char *)data + m * element_size) <= 0) {
            KR_swap_data((char *)data + r * element_size, (char *)data + l * element_size, element_size);

            if (r == m) {
                m = l;
            }

            l++;
        }
    }
    if (l != data_size){
        KR_qsort(data, l, element_size, cmp);
        KR_qsort((char *)data + l * element_size, data_size - l, element_size, cmp);
    }
    else {
        KR_swap_data((char *)data + m                                     * element_size, 
                     (char *)data + (data_size - 1 /*последний элемент*/) * element_size,
                     element_size);
        KR_qsort(data, data_size - 1, element_size, cmp);
    }
}