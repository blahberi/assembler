//
// Author: Eitan H.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../assembler/directive_to_machine_code.h"
#include "../utils/utils.h"

void test2() {
    AssemblerContext context = {
            .IC = 100,
            .is_first_pass = false,
    };

    Word *words = malloc(5 * sizeof(Word));
    memset(words, 0, 5 * sizeof(Word));

    generate_data_directive(NULL, "1        ,    -1,8191,     +603,-125", &context, words);

    for (int i = 0; i < 5; i++) {
        print_binary(words[i].word, 14);
    }

    free(words);
}