#include <stdio.h>
#include "IO/io.h"
#include <assert.h>
#include <cstdlib>
#include "string/string.h"
#include "sort/sort.h"

const char *file_path = "resources/gamlet.txt";

int str_cmp(const void *a, const void *b) {
    return KR_strcmp_letonly(*((char **)a), *((char **)b));
}

int str_cmp_r(const void *a, const void *b) {
    return KR_strcmp_letonly_r(*((char **)a), *((char **)b));
}

int main() {
    char *buff = nullptr;
    int buff_size = get_data_file(&buff, file_path);

    assert(buff != nullptr);

    char **text = nullptr;

    int text_size = buff_to_text(&text, buff, buff_size);

    KR_qsort(text, text_size, sizeof(char*), (int (*)(const void*, const void*))str_cmp);

    FILE * ptrfileout = fopen("resources/gamletsort.txt", "wb");

    assert(ptrfileout != nullptr);

    for (int i = 0; i < text_size; i++) {
        fprintf(ptrfileout, "%s\n", text[i]);
    }

    fprintf(ptrfileout, "------------------------------begin string reverse comporator sort----------------------------");

    KR_qsort(text, text_size, sizeof(char*), (int (*)(const void*, const void*))str_cmp_r);

    for (int i = 0; i < text_size; i++) {
        fprintf(ptrfileout, "%s\n", text[i]);
    }

    fprintf(ptrfileout, "------------------------------------------source text-----------------------------------------");

    for (int i = 0; i < buff_size; i++) {
        if (buff[i] == '\0') {
            if (buff[i + 1] != '\0') {
                fprintf(ptrfileout, "\n");
            }
        }
        else {
            fprintf(ptrfileout, "%c", buff[i]);
        }
    }
    
}