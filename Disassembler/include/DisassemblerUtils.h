/**
 * @file
 * @brief Disassembler utilits for working with disasm objects
*/
#ifndef DISASSEMBLER_UTILS_H
#define DISASSEMBLER_UTILS_H

const size_t COUNT_OF_DUMP_COMMANDS = 10;

disassemblerErrorCode disassembler_verify(disassemblerCase* disasmCase);

disassemblerErrorCode disassembler_ctor(disassemblerCase* disasmCase);

disassemblerErrorCode disassembler_dtor(disassemblerCase* disasmCase);

disassemblerErrorCode disassembler_dump(disassemblerCase* disasmCase);

disassemblerErrorCode processor_CS_dump(disassemblerCase* disasmCase);

disassemblerErrorCode write_CS_bird(disassemblerCase* disasmCase);

disassemblerErrorCode dump_CS_info(const disassemblerCase* disasmCase, size_t bufferLen);

disassemblerErrorCode count_len_of_buffer(const disassemblerCase* disasmCase, size_t* bufferLen);

disassemblerErrorCode copy_data_from_buffer(const char* buffer, void* ptr, size_t len);

#endif