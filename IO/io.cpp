#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "io.h"
#include <string.h>
#include <assert.h>

size_t get_file_size(FILE * ptr_file) {
    struct stat fileinfo = {};
    fstat(fileno(ptr_file), &fileinfo);

    return fileinfo.st_size;
}

size_t get_data_file(char **buff, const char *file_path) {
    assert(buff      != nullptr);
    assert(file_path != nullptr);


    FILE * ptrFile = fopen(file_path, "rb");
    assert(ptrFile != nullptr);

    size_t file_size = get_file_size(ptrFile);
    
    

    *buff = (char *)calloc(file_size + 2, sizeof(char));

    assert(buff != nullptr);

    fread(*buff, sizeof(char), file_size, ptrFile);
    (*buff)[file_size + 1] = (*buff)[file_size] = 0;


    fclose(ptrFile);


    return file_size;
}

size_t buff_to_text(char ***text, char *buff, size_t buff_size) {
    assert(text != nullptr);
    assert(buff != nullptr);

    size_t text_size = 1;

    for (size_t i = 0; i < buff_size; i++) {
        if (buff[i] == '\n') {
            text_size++;
        }
    }

    *text = (char **)calloc(text_size + 1, sizeof(char *));
    
    assert(text != nullptr);

    (*text)[text_size] = nullptr;

    (*text)[0] = buff;

    size_t ptr = 1;
    for (size_t i = 0; i < buff_size; i++) {
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

void get_file_name_from_flug(const char **file_path, int argc, char *argv[]) {
    //если есть название файла ввода то флаг -f точно не последний, значит перебирать argc - 1 безсмысленно
    //а так же это поможет избежать ошибки если флаг указали последним
    for (size_t i = 0; i < argc - 1; i++) {
        if (!strncmp(argv[i], "-f", 3)) {
            *file_path = argv[i + 1];
            break;
        }
    }
}

void fprintf_buff(FILE *ptrfileout, char *buff, size_t buff_size) {
    assert(ptrfileout != nullptr);
    assert(buff       != nullptr);

    for (size_t i = 0; i < buff_size; i++) {
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

size_t get_text_file(char ***text, char **buff, size_t *buff_size, const char *file_path) {
    assert(text      != nullptr);
    assert(buff      != nullptr);
    assert(buff_size != nullptr);

    *buff_size = get_data_file(buff, file_path);

    assert(buff != nullptr);

    size_t text_size = buff_to_text(text, *buff, *buff_size);

    assert(text != nullptr);

    return text_size;
}