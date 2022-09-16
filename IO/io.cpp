#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "io.h"
#include <string.h>
#include <assert.h>

int get_data_file(char **buff, const char *file_path) {
    assert(buff      != nullptr);
    assert(file_path != nullptr);


    FILE * ptrFile = fopen(file_path, "rb");
    assert(ptrFile != nullptr);


    struct stat fileinfo;
    fstat(fileno(ptrFile), &fileinfo);
    

    *buff = (char *)calloc(fileinfo.st_size + 2, sizeof(char));

    assert(buff != nullptr);

    fread(*buff, sizeof(char), fileinfo.st_size, ptrFile);
    (*buff)[fileinfo.st_size + 1] = (*buff)[fileinfo.st_size] = 0;


    fclose(ptrFile);


    return fileinfo.st_size;
}

int buff_to_text(char ***text, char *buff, int buff_size) {
    assert(text != nullptr);
    assert(buff != nullptr);

    int text_size = 1;

    for (int i = 0; i < buff_size; i++) {
        if (buff[i] == '\n') {
            text_size++;
        }
    }

    *text = (char **)calloc(text_size + 1, sizeof(char *));
    
    assert(text != nullptr);

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

void get_file_name_from_flug(int argc, char *argv[], char **file_path) {
    //если есть название файла ввода то флаг -f точно не последний, значит перебирать argc - 1 безсмысленно
    //а так же это поможет избежать ошибки если флаг указали последним
    for (int i = 0; i < argc - 1; i++) {
        if (!strncmp(argv[i], "-f", 3)) {
            *file_path = argv[i + 1];
            break;
        }
    }
}

void fprintf_buff(FILE *ptrfileout, char *buff, int buff_size) {
    assert(ptrfileout != nullptr);
    assert(buff       != nullptr);

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

int get_text_file(char ***text, char **buff, int *buff_size, const char *file_path) {
    assert(text      != nullptr);
    assert(buff      != nullptr);
    assert(buff_size != nullptr);

    *buff_size = get_data_file(buff, file_path);

    assert(buff != nullptr);

    int text_size = buff_to_text(text, *buff, *buff_size);

    assert(text != nullptr);

    return text_size;
}