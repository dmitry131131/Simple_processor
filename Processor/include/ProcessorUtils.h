/**
 * @file
 * @brief Supporting math functions
*/
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

enum dumpMode{
    FULL_DUMP,
    STACK_ONLY,
    RET_STACK_ONLY,
    CS_ONLY,
    REGISTERS_ONLY
};  

processorErrorCode processor_ctor(softProcessorUnit* processor);

processorErrorCode processor_dtor(softProcessorUnit* processor);

processorErrorCode processor_verify(softProcessorUnit* processor);

processorErrorCode processor_dump(softProcessorUnit* processor, dumpMode mode);

processorErrorCode processor_CS_dump(softProcessorUnit* processor);

processorErrorCode copy_data_from_buffer(const char* buffer, void* ptr, size_t len);

processorErrorCode count_len_of_buffer(const softProcessorUnit* processor, size_t* bufferLen);

processorErrorCode dump_CS_info(const softProcessorUnit* processor, size_t bufferLen);

processorErrorCode write_CS_bird(softProcessorUnit* processor);

processorErrorCode write_register_values(softProcessorUnit* processor);


#endif