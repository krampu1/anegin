#include <stdio.h>
#include "IO/io.h"
#include <assert.h>
#include <cstdlib>
#include "string/string.h"
#include "sort/sort.h"
#include <iostream>
#include <string>

const char *file_path = "resources/onegin.txt";

int str_cmp(const void *a, const void *b) {
    assert(a != nullptr);
    assert(b != nullptr);

    return KR_strcmp_letonly((*((KR_string *)a)).ptr, (*((KR_string *)b)).ptr);
}

int str_cmp_r(const void *a, const void *b) {
    assert(a != nullptr);
    assert(b != nullptr);
    
    return KR_strcmp_letonly_rev((*((KR_string *)a)), (*((KR_string *)b)));
}

void fprintf_text(FILE *ptrfileout, KR_string *text, size_t text_size) {
    assert(ptrfileout != nullptr);
    assert(text != nullptr);

    for (size_t i = 0; i < text_size; i++) {
        fprintf(ptrfileout, "%s\n", text[i].ptr);
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Russian");

    const char *file_out_path = file_path;

    get_file_name_from_flug(&file_out_path, argc, argv);

    assert(file_out_path != nullptr);

    size_t buff_size = 0;
    char *buff  = nullptr;
    KR_string *text = nullptr;

    size_t text_size = get_text_file(&text, &buff, &buff_size, file_path);

    assert(text != nullptr);
    assert(buff != nullptr);

    KR_qsort(text, text_size, sizeof(KR_string), (int (*)(const void*, const void*))str_cmp);
    
    char *file_out = (char *) calloc(KR_strlen(file_path) + 5, sizeof(char));

    assert(file_out != nullptr);

    KR_strcat(file_out, file_out_path);
    KR_strcat(file_out, ".out");

    FILE * ptrfileout = fopen(file_out, "wb");

    assert(ptrfileout != nullptr);

    fprintf_text(ptrfileout, text, text_size);
    
    fprintf(ptrfileout, "------------------------------begin string reverse comporator sort----------------------------\n");

    KR_qsort(text, text_size, sizeof(KR_string), (int (*)(const void*, const void*))str_cmp_r);

    fprintf_text(ptrfileout, text, text_size);

    fprintf(ptrfileout, "------------------------------------------source text-----------------------------------------\n");

    fprintf_buff(ptrfileout, buff, buff_size);
}