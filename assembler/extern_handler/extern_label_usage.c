/*
 Author: Eitan H.
*/
#include "extern_label_usage.h"
#include "../../memory_allocator/memory_allocator.h"
#include <string.h>

ExternalLabelUsage* construct_external_label_usage(const char* label, int memory_address) {
    ExternalLabelUsage* usage = malloc_track_global(sizeof(ExternalLabelUsage));
    usage->label = strdup(label); /* Duplicate the label string */
    track_pointer_global(usage->label);
    usage->memory_address = memory_address;
    return usage;
}
