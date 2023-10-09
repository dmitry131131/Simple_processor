/**
 * @file
 * @brief Functions for reading programm from text
*/

const size_t FILE_HEADER_LEN = 10;

processorErrorCode prepare(const char* filename, softProcessorUnit* processor);

processorErrorCode read_programm_body(FILE* file, char** buff, size_t len);

processorErrorCode read_bin_file(const char* filename, softProcessorUnit* processor);

processorErrorCode read_char_from_file(FILE* file, char* ch);

processorErrorCode read_int_from_file(FILE* file, int* num);