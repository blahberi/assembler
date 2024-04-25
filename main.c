#include <stdio.h>
#include "assembler/assembler.h"

int main(int argc, char *argv[]) {
    const char* filepath;
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return 1;
    }

    filepath = argv[1];
    assemble(filepath);

    return 0;
}