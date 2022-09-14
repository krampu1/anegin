#include <stdio.h>
#include "IO/io.h"
#include <assert.h>
#include <cstdlib>
#include "string/string.h"

const char *file_path = "resources/gamlet.txt";

int str_cmp(char **a, char **b) {
    if (KR_strcmp_letonly(*a, *b)) {
        return -1;
    }
    return +1;
}

int main() {
    char *buff = nullptr;
    int buff_size = get_data_file(&buff, file_path);

    assert(buff != nullptr);

    char **text = nullptr;

    int text_size = buff_to_text(&text, buff, buff_size);

    qsort(text, text_size, sizeof(char*), (int (*)(const void*, const void*))str_cmp);

    FILE * ptrfileout = fopen("resources/gamletsort.txt", "wb");

    assert(ptrfileout != nullptr);

    for (int i = 0; i < text_size; i++) {
        fprintf(ptrfileout, "%s\n", text[i]);
    }
}