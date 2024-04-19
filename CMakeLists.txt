cmake_minimum_required(VERSION 3.27)
project(assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(assembler main.c
        symbol_table/table/symbol_table.c
        symbol_table/table/symbol_table.h
        machine_code_generator/instruction_to_machine_code.c
        machine_code_generator/instruction_to_machine_code.h
        utils/utils.c
        utils/utils.h
        config/config.h
        symbol_table/symbol_node/symbol_node.h
        symbol_table/symbol/symbol.h
        symbol_table/global_symbol_table/global_symbol_table.h
        symbol_table/symbol/symbol.c
        symbol_table/symbol_node/symbol_node.c
        symbol_table/global_symbol_table/global_symbol_table.c
        words/instruction_word.h
        descriptors/operation_descriptor.h
        descriptors/operand_descriptor.h
        words/operand_words.h
        addressing_mode/addressing_mode.c
        machine_code_generator/operand_to_machine_code/operand_to_machine_code.c
        addressing_mode/addressing_mode.h
        machine_code_generator/operand_to_machine_code/operand_to_machine_code.h
        enums/are.h
        assembler_context/assembler_context.h)
