int get_data_file(char **buff, const char *file_name);

int buff_to_text(char ***text, char *buff, int buff_size);

void get_file_name_from_flug(int argc, char *argv[], char **file_path);

void fprintf_buff(FILE *ptrfileout, char *buff, int buff_size);

int get_text_file(char ***text, char **buff, int *buff_size, const char *file_path);