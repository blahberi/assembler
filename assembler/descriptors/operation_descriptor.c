//
// Author: Eitan H.
//

#include <string.h>
#include <stdlib.h>
#include "operation_descriptor.h"
#include "../utils/utils.h"
#include "../utils/assembly_strings.h"
#include "../instruction_to_machine_code.h"

OperationDescriptor* get_operation_descriptor(const char* sentance){
    char* operation_str = get_sentence_start(sentance);
    trim_whitespace(operation_str);
    OPCODE type;
    InstructionGenerator *generate = NULL;
    LabelHandler *handle_label = handle_label_instruction;
    if (strcmp(operation_str, "mov") == 0) {
        type = MOV;
        generate = generate_two_word_instruction;
    } else if (strcmp(operation_str, "cmp") == 0) {
        type = CMP;
        generate = generate_two_word_instruction;
    } else if (strcmp(operation_str, "add") == 0) {
        type = ADD;
        generate = generate_two_word_instruction;
    } else if (strcmp(operation_str, "sub") == 0) {
        type = SUB;
        generate = generate_two_word_instruction;
    } else if (strcmp(operation_str, "not") == 0) {
        type = NOT;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "clr") == 0) {
        type = CLR;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "lea") == 0) {
        type = LEA;
        generate = generate_two_word_instruction;
    } else if (strcmp(operation_str, "inc") == 0) {
        type = INC;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "dec") == 0) {
        type = DEC;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "jmp") == 0) {
        type = JMP;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "bne") == 0) {
        type = BNE;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "red") == 0) {
        type = RED;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "prn") == 0) {
        type = PRN;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "jsr") == 0) {
        type = JSR;
        generate = generate_one_word_instruction;
    } else if (strcmp(operation_str, "rts") == 0) {
        type = RTS;
        generate = generate_zero_word_instruction;
    } else if (strcmp(operation_str, "hlt") == 0) {
        type = HLT;
        generate = generate_zero_word_instruction;
    }
    else{
        return NULL;
    }

    OperationDescriptor* descriptor = (OperationDescriptor*) malloc(sizeof(struct operation_descriptor));
    descriptor->opcode = type;
    descriptor->generate = generate;
    descriptor->handle_label = handle_label;
    return descriptor;
}