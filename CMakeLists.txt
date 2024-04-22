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
        assembler/operation_descriptor.h
        assembler/operand_descriptor.h
        assembler/words.h
        assembler/addressing_mode.c
        assembler/operand_to_machine_code.c
        assembler/addressing_mode.h
        assembler/operand_to_machine_code.h
        assembler/are.h
        assembler/assembler_context.h
        assembler/assembly_strings.c
        assembler/assembly_strings.h
        assembler/directive_to_machine_code.c
        assembler/directive_descriptor.h
        assembler/handle_label.c
        assembler/handle_label.h
        errors.h
        tests/test1.c
        tests/test1.h
        tests/test2.c
        assembler/directive_to_machine_code.h
        tests/test2.h
        tests/test3.c
        tests/test3.h
        assembler/handle_line.c
        assembler/sentence_type.h
        assembler/directive_descriptor.c
        assembler/operation_descriptor.c
        assembler/operand_descriptor.c
        assembler/handle_line.h
        assembler/file_reader.c
        tests/test4.c
        tests/test4.c.h
        assembler/file_reader.h
)
