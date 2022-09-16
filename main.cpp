#include <stdio.h>
#include "IO/io.h"
#include <assert.h>
#include <cstdlib>
#include "string/string.h"
#include "sort/sort.h"

const char *file_path = "resources/gamlet.txt";

int str_cmp(const void *a, const void *b) {
    assert(a != nullptr);
    assert(b != nullptr);

    return KR_strcmp_letonly(*((char **)a), *((char **)b));
}

int str_cmp_r(const void *a, const void *b) {
    assert(a != nullptr);
    assert(b != nullptr);
    
    return KR_strcmp_letonly_rev(*((char **)a), *((char **)b));
}

void fprintf_text(FILE *ptrfileout, char **text, size_t text_size) {
    assert(ptrfileout != nullptr);
    assert(text != nullptr);

    for (size_t i = 0; i < text_size; i++) {
        fprintf(ptrfileout, "%s\n", text[i]);
    }
}

int main(int argc, char *argv[]) {
    const char *file_out_path = file_path;

    get_file_name_from_flug(&file_out_path, argc, argv);

    assert(file_out_path != nullptr);

    size_t buff_size = 0;
    char *buff  = nullptr;
    char **text = nullptr;

    size_t text_size = get_text_file(&text, &buff, &buff_size, file_path);

    assert(text != nullptr);
    assert(buff != nullptr);

    KR_qsort(text, text_size, sizeof(char*), (int (*)(const void*, const void*))str_cmp);
    
    char *file_out = (char *) calloc(KR_strlen(file_path) + 5, sizeof(char));

    assert(file_out != nullptr);

    KR_strcat(file_out, file_out_path);
    KR_strcat(file_out, ".out");

    FILE * ptrfileout = fopen(file_out, "wb");

    assert(ptrfileout != nullptr);

    fprintf_text(ptrfileout, text, text_size);
    

    fprintf(ptrfileout, "------------------------------begin string reverse comporator sort----------------------------\n");

    KR_qsort(text, text_size, sizeof(char*), (int (*)(const void*, const void*))str_cmp_r);

    fprintf_text(ptrfileout, text, text_size);

    fprintf(ptrfileout, "------------------------------------------source text-----------------------------------------\n");

    fprintf_buff(ptrfileout, buff, buff_size);
    
}