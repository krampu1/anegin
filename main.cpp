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
    return KR_strcmp_letonly_rev(*((char **)a), *((char **)b));
}

void fprintf_text(FILE *ptrfileout, char **text, int text_size) {
    for (int i = 0; i < text_size; i++) {
        fprintf(ptrfileout, "%s\n", text[i]);
    }
}

int main(int argc, char *argv[]) {
    char *file_out_path = (char *)file_path;

    get_file_name_from_flug(argc, argv, &file_out_path);

    char *buff = nullptr;
    int buff_size = get_data_file(&buff, file_path);

    assert(buff != nullptr);

    char **text = nullptr;

    int text_size = buff_to_text(&text, buff, buff_size);

    KR_qsort(text, text_size, sizeof(char*), (int (*)(const void*, const void*))str_cmp);
    
    char *file_out = (char *) calloc(KR_strlen(file_path) + 5, sizeof(char));
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