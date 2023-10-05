/**
 * @file
 * @brief Main functions or processor
*/

const int DOUBLE_COEF = 1000;

/**
 * @brief Main processing function
 * @param [in] text Pointer to programm text
 * @return Error code or NO_ERRORS if everything is ok
*/
enum errorCode processing(textData* text);

enum errorCode processor_push(const char* line, Stack* stack);

enum errorCode processor_out(Stack* stack, FILE* stream);

enum errorCode processor_add(Stack* stack);

enum errorCode processor_sub(Stack* stack);

enum errorCode processor_mue(Stack* stack);

enum errorCode processor_div(Stack* stack);
