cmake_minimum_required(VERSION 3.27)
project(assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(assembler main.c
        symbol_table/symbol_table.c
        symbol_table/symbol_table.h
        assembler/instruction_to_machine_code.c
        assembler/instruction_to_machine_code.h
        utils/utils.c
        utils/utils.h
        config.h
        symbol_table/symbol_node.h
        symbol_table/symbol.h
        symbol_table/global_symbol_table.h
        symbol_table/symbol.c
        symbol_table/symbol_node.c
        symbol_table/global_symbol_table.c
        assembler/instruction_word.h
        assembler/operation_descriptor.h
        assembler/operand_descriptor.h
        assembler/operand_words.h
        assembler/addressing_mode.c
        assembler/operand_to_machine_code.c
        assembler/addressing_mode.h
        assembler/operand_to_machine_code.h
        assembler/are.h
        assembler/assembler_context.h
        assembler/register_error.h)
