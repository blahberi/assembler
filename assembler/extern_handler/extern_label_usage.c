//
// Author: Eitan H.
//
#include "extern_label_usage.h"
#include <stdlib.h>
#include <string.h>

ExternalLabelUsage* construct_external_label_usage(const char* label, int memory_address) {
    ExternalLabelUsage* usage = malloc(sizeof(ExternalLabelUsage));
    usage->label = strdup(label); // Duplicate the label string
    usage->memory_address = memory_address;
    return usage;
}