/*
 Author: Eitan H.
*/


#include <stdio.h>
#include <stdlib.h>
#include "words.h"
#include "../memory_allocator/memory_allocator.h"


char* word_to_string(int word) {
    char* str = malloc_track(8); /* 7 digits plus null terminator */
    char* p = str + 7; /* start at the end of the string */
    int i;
    char* map;
    *p = '\0'; /* null terminator */
    p--; /* move to the last digit */

    /* map from base 4 digits to characters */
    map = "*#%!";

    /* convert the word to base 4 */
    for (i = 0; i < 7; i++) {
        int digit = word % 4;
        *p = map[digit];
        p--;
        word /= 4;
    }

    return str;
}

void write_line(Word* word, int address, FILE* file) { /* Write a line to the file */
    char* str = word_to_string(word->word);
    fprintf(file, "%04d %s\n", address, str); /* Write the address and the machine code */
}

void write_file(char* filepath, Word* words, int ic, int dc) { /* Write the words to the file */
    int words_count = ic + dc;
    int i;
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open file %s\n", filepath);
        free_all_memory();
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%4d %d\n", ic, dc); /* Write the header, which is the number of instructions and the number of data values */

    for (i = 0; i < words_count; i++) {
        write_line(&words[i], i+100, file); /* Write each line */
    }
    fclose(file);
}