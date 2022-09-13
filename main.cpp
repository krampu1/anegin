#include <stdio.h>
#include "IO/io.h"
#include <assert.h>

const char *file_path = "resources/gamlet.txt";

int main() {
    char *buff = nullptr;
    int buff_size = get_data_file(&buff, file_path);

    assert(buff != nullptr);

    char **text = nullptr;

    int text_size = buff_to_text(&text, buff, buff_size);
    
    printf("%s\n", text[text_size - 1]);
}