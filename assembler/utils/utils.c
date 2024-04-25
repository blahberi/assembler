/*
 Author: Eitan H.
*/


#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "../../memory_allocator/memory_allocator.h"
#include "../../errors.h"

char* my_strdup_helper(const char* s) { /* Duplicate a string and return a pointer to the new string */
    /*
     * I don't think we can use POSIX strdup because it's not standard C.
     */
    char* d;
    if (s == NULL) return NULL; /* Check for NULL pointer */

    /* Allocate memory for the new string including the null terminator */
    d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL; /* If memory allocation fails, return NULL */

    /* Copy the string into the newly allocated memory */
    strcpy(d, s);
    return d; /* Return the duplicate string */
}

char* my_strdup(const char* s) { /* strdup a string and add it to the memory allocator for tracking */
    char* d = my_strdup_helper(s);
    track_pointer(d);
    return d;
}

char* my_strdup_global(const char *s) { /* strdup a string and add it to the global memory allocator for tracking */
    char* d = my_strdup_helper(s);
    track_pointer_global(d);
    return d;
}

bool check_filename_extension(const char* filepath, const char* extension) { /* Check if a file has a certain extension */
    const char* file_extension = strrchr(filepath, '.');
    if (file_extension != NULL && strcmp(file_extension, extension) == 0) {
        return true;
    }
    return false;
}

char* get_base_name(const char* filepath) { /* Get the base name of a file */
    /*
     * For example, if the filepath is "/home/user/file.txt", the base name is "file.txt".
     */
    char* last_separator = strrchr(filepath, '/');
    char* last_backslash = strrchr(filepath, '\\');
    char* base_name;
    char* last_occurrence;

    /* Use the last occurring separator, whether it's a slash or a backslash */
    if (last_separator > last_backslash) {
        last_occurrence = last_separator;
    } else {
        last_occurrence = last_backslash;
    }

    if (last_occurrence == NULL) {
        return my_strdup(filepath);
    }
    base_name = my_strdup(last_occurrence + 1);
    return base_name;
}

char* remove_extension(const char* filename) { /* Remove the extension from a file */
    /*
     * For example, "file.txt" becomes "file".
     */
    char* dot = strrchr(filename, '.');
    int length;
    char* filepath_without_extension;

    if (dot == NULL) {
        return my_strdup(filename);
    }
    length = dot - filename;
    filepath_without_extension = malloc_track(length + 1);
    strncpy(filepath_without_extension, filename, length);
    filepath_without_extension[length] = '\0';
    return filepath_without_extension;
}

void check_valid_filepath(const char* filepath) { /* Check if a file path is valid */
    /*
     * Check if the filepath has a filename and the extension is ".as".
     */
    char* base_name;

    push_memory();
    base_name = get_base_name(filepath);
    if (!base_name) {
        free_all_memory();
        fprintf(stderr, ERR_INVALID_FILEPATH, filepath);
        exit(EXIT_FAILURE);
    }
    if (!check_filename_extension(base_name, ".as")) {
        free_all_memory();
        fprintf(stderr, ERR_INVALID_FILE_EXTENSION, filepath);
        exit(EXIT_FAILURE);    }
    pop_memory();
}

char* get_preprocessed_filepath(const char* filepath) { /* Get the preprocessed file path */
    /*
     * {filename}.as -> .preprocessed_{filename}.as
     *
     * For example:
     * test1.as -> .preprocessed_code.as
     */
    char* base_name;
    int new_filepath_length;
    char* new_filepath;

    push_memory();
    check_valid_filepath(filepath);
    base_name = get_base_name(filepath);

    new_filepath_length = strlen(".preprocessed_") + strlen(base_name) + 1;
    new_filepath = malloc_track_global(new_filepath_length);
    strcpy(new_filepath, ".preprocessed_");
    strcat(new_filepath, base_name);

    pop_memory();
    return new_filepath;
}

char* get_filename_with_extension(const char* filepath, const char* extension) { /* Get the file name with a certain extension */
    /*
     * For example, if the filename is "file.as" and the extension is ".ext",
     * the new filepath will be "file.ext".
     */
    char* base_name_without_extension;
    int new_filepath_length;
    char* new_filepath;

    push_memory();
    check_valid_filepath(filepath);
    base_name_without_extension = remove_extension(get_base_name(filepath));

    new_filepath_length = strlen(base_name_without_extension) + strlen(extension) + 1;
    new_filepath = malloc_track_global(new_filepath_length);

    strcpy(new_filepath, base_name_without_extension);
    strcat(new_filepath, extension);

    pop_memory();
    return new_filepath;
}

char* get_extern_filename(const char* filepath) { /* Get the extern file path */
    /*
     * {filename}.as -> {filename}.ext
     */
    return get_filename_with_extension(filepath, ".ext");
}

char* get_entry_filename(const char* filepath) { /* Get the entry file path */
    /*
     * {filename}.as -> {filename}.ent
     */
    return get_filename_with_extension(filepath, ".ent");
}

char* get_output_filename(const char* filepath) { /* Get the output file path */
    /*
     * {filename}.as -> {filename}.obj
     */
    return get_filename_with_extension(filepath, ".obj");
}

char* get_current_director() {

    char* current_directory = malloc_track_global(1024);
    getcwd(current_directory, 1024);
    return current_directory;
}