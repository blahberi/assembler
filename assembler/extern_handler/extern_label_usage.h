//
// Author: Eitan H.
//

#ifndef ASSEMBLER_EXTERN_LABEL_USAGE_H
#define ASSEMBLER_EXTERN_LABEL_USAGE_H

typedef struct {
    char* label;
    int memory_address;
} ExternalLabelUsage;

ExternalLabelUsage* construct_external_label_usage(const char* label, int memory_address);

#endif //ASSEMBLER_EXTERN_LABEL_USAGE_H
