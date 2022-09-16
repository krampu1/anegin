#include "sort.h"

void KR_sort(void *data, int data_size, int element_size, int (* cmp) (const void *, const void *)) {
    for (int a = 0; a < data_size; a++) {
        for (int i = 1; i < data_size; i++){
            if (cmp((char *)data + i * element_size, (char *)data + (i - 1) * element_size) < 0){
                for (int k = 0; k < element_size; k++) {
                    char p = *((char *)data + i * element_size + k);
                    *((char *)data + i * element_size + k) = *((char *)data + (i - 1) * element_size + k);
                    *((char *)data + (i - 1) * element_size + k) = p;
                }
            }
        }
    }
}