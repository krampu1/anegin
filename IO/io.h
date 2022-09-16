#ifndef IO
#define IO

size_t get_data_file(char **buff, const char *file_name);

size_t buff_to_text(char ***text, char *buff, size_t buff_size);

void get_file_name_from_flug(const char **file_path, int argc, char *argv[]);

void fprintf_buff(FILE *ptrfileout, char *buff, size_t buff_size);

size_t get_text_file(char ***text, char **buff, size_t *buff_size, const char *file_path);

#endif