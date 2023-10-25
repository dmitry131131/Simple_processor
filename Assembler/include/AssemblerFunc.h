/**
 * @file
 * @brief Main asembler functions
*/
#ifndef ASSEMBLER_FUNC_H
#define ASSEMBLER_FUNC_H

const int TAG_BUFFER_SIZE  = 100;
const int MAX_COMMAND_LEN  = 150;
const int MAX_REGISTER_LEN = 10;

const int VERSION = 2;

#define LISTING_COMMAND_FORMAT "-10"

#include "DSL.h"

struct Tag {
    char name[150];
    int ip;
};

struct TagBuffer {
    size_t size;
    Tag*   bufferName;
};

asmErrorCode main_assembler_function(textData* text, TagBuffer* tagBuffer, const char* filename);

asmErrorCode tag_buffer_ctor(TagBuffer* tag);

asmErrorCode tag_buffer_dtor(TagBuffer* tag);

asmErrorCode add_tag_to_buffer(const char* tagName, int ip, TagBuffer* tagBuffer);

asmErrorCode get_tag_ip(TagBuffer* tagBuffer, const char* tagName, int* ip);

#endif