#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "io.h"
#include <assert.h>

int get_data_file(char **buff, const char *file_path) {
    assert(file_path != nullptr);

    FILE * ptrFile = fopen(file_path, "rb");
    assert(ptrFile != nullptr);

    struct stat fileinfo;
    fstat(fileno(ptrFile), &fileinfo);
    
    *buff = (char *)calloc(fileinfo.st_size + 2, sizeof(char));
    fread(*buff, sizeof(char), fileinfo.st_size, ptrFile);
    (*buff)[fileinfo.st_size + 1] = (*buff)[fileinfo.st_size] = 0;

    fclose(ptrFile);

    return fileinfo.st_size;
}

int buff_to_text(char ***text, char *buff, int buff_size) {
    int text_size = 1;

    for (int i = 0; i < buff_size; i++) {
        if (buff[i] == '\n') {
            text_size++;
        }
    }

    *text = (char **)calloc(text_size + 1, sizeof(char *));
    (*text)[text_size] = nullptr;

    (*text)[0] = buff;

    int ptr = 1;
    for (int i = 0; i < buff_size; i++) {
        if (buff[i] == '\r') {
            buff[i] = 0;
        }
        if (buff[i - 1] == '\n') {
            buff[i - 1] = 0;
            (*text)[ptr++] = &buff[i];
        }
    }

    return text_size;
}