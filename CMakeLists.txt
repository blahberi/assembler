cmake_minimum_required(VERSION 3.27)
project(assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(assembler main.c
        assembler/symbol_table/symbol_table.c
        assembler/symbol_table/symbol_table.h
        assembler/instruction_to_machine_code.c
        assembler/instruction_to_machine_code.h
        assembler/utils/utils.c
        assembler/utils/utils.h
        config.h
        assembler/symbol_table/symbol_node.h
        assembler/symbol_table/symbol.h
        assembler/symbol_table/global_symbol_table.h
        assembler/symbol_table/symbol.c
        assembler/symbol_table/symbol_node.c
        assembler/symbol_table/global_symbol_table.c
        assembler/descriptors/operation_descriptor.h
        assembler/descriptors/operand_descriptor.h
        assembler/words.h
        assembler/addressing_mode.c
        assembler/operand_to_machine_code.c
        assembler/addressing_mode.h
        assembler/operand_to_machine_code.h
        assembler/are.h
        assembler/context/assembler_context.h
        assembler/utils/assembly_strings.c
        assembler/utils/assembly_strings.h
        assembler/directive_to_machine_code.c
        assembler/descriptors/directive_descriptor.h
        assembler/handlers/handle_label.c
        assembler/handlers/handle_label.h
        assembler/directive_to_machine_code.h
        assembler/handlers/handle_line.c
        assembler/sentence_type.h
        assembler/descriptors/directive_descriptor.c
        assembler/descriptors/operation_descriptor.c
        assembler/descriptors/operand_descriptor.c
        assembler/handlers/handle_line.h
        assembler/read_file.h
        assembler/extern_handler/extern_label_node.h
        assembler/extern_handler/extern_label_list.h
        assembler/extern_handler/extern_label_list.c
        assembler/extern_handler/extern_handler.c
        assembler/extern_handler/extern_label_usage.c
        assembler/extern_handler/extern_label_usage.h
        assembler/extern_handler/extern_handler.h
        assembler/read_file.c
        assembler/assembler.c
        assembler/assembler.h
        assembler/utils/error_checking.c
        assembler/utils/error_checking.h
        assembler/utils/errors.h
        assembler/handlers/handle_line.c
        assembler/descriptors/line_descriptor.h
        assembler/context/context.h
)
