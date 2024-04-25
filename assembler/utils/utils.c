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

bool check_filename_extension(const char* filepath, const char* extension) {
    const char* file_extension = strrchr(filepath, '.');
    if (file_extension != NULL && strcmp(file_extension, extension) == 0) {
        return true;
    }
    return false;
}

char* get_base_path(const char* filepath) {
    char* last_separator = strrchr(filepath, '/');
    char* last_backslash = strrchr(filepath, '\\');

    /* Use the last occurring separator, whether it's a slash or a backslash */
    char* last_occurrence;
    if (last_separator > last_backslash) {
        last_occurrence = last_separator;
    } else {
        last_occurrence = last_backslash;
    }

    if (last_occurrence == NULL) {
        return NULL;
    }

    int directory_length = last_occurrence - filepath + 1;
    char* directory = malloc_track(directory_length + 1);
    strncpy(directory, filepath, directory_length);
    directory[directory_length] = '\0';
    return directory;
}

char* get_base_name(const char* filepath) {
    char* last_separator = strrchr(filepath, '/');
    char* last_backslash = strrchr(filepath, '\\');

    /* Use the last occurring separator, whether it's a slash or a backslash */
    char* last_occurrence;
    if (last_separator > last_backslash) {
        last_occurrence = last_separator;
    } else {
        last_occurrence = last_backslash;
    }

    if (last_occurrence == NULL) {
        return strdup(filepath);
    }
    char* base_name = strdup(last_occurrence + 1);
    track_pointer(base_name);
    return base_name;
}

char* remove_extension(const char* filepath) {
    char* dot = strrchr(filepath, '.');
    if (dot == NULL) {
        return strdup(filepath);
    }
    int length = dot - filepath;
    char* filepath_without_extension = malloc_track(length + 1);
    strncpy(filepath_without_extension, filepath, length);
    filepath_without_extension[length] = '\0';
    return filepath_without_extension;
}

void check_valid_filepath(const char* filepath) {
    push_memory();
    char* directory = get_base_path(filepath);
    char* base_name = get_base_name(filepath);
    if (!directory || !base_name) {
        pop_memory();
        fprintf(stderr, ERR_INVALID_FILEPATH, filepath);
        exit(EXIT_FAILURE);
    }
    if (!check_filename_extension(base_name, ".as")) {
        pop_memory();
        fprintf(stderr, ERR_INVALID_FILE_EXTENSION, filepath);
        exit(EXIT_FAILURE);    }
    pop_memory();
}

char* get_preprocessed_filepath(const char* filepath) {
    check_valid_filepath(filepath);
    push_memory();
    char* directory = get_base_path(filepath);
    char* base_name = get_base_name(filepath);

    int new_filepath_length = (directory ? strlen(directory) : 0) + strlen(".preprocessed_") + strlen(base_name) + 1;
    char* new_filepath = malloc_track_global(new_filepath_length);

    if (directory) {
        strcpy(new_filepath, directory);
    }
    strcat(new_filepath, ".preprocessed_");
    strcat(new_filepath, base_name);

    pop_memory();
    return new_filepath;
}

char* get_extern_filepath(const char* filepath) {
    check_valid_filepath(filepath);
    push_memory();
    char* directory = get_base_path(filepath);
    char* base_name = remove_extension(get_base_name(filepath));

    int new_filepath_length = (directory ? strlen(directory) : 0) + strlen(base_name) + strlen(".ext") + 1;
    char* new_filepath = malloc_track_global(new_filepath_length);

    if (directory) {
        strcpy(new_filepath, directory);
    }
    strcat(new_filepath, base_name);
    strcat(new_filepath, ".ext");

    pop_memory();
    return new_filepath;
}

char* get_entry_filepath(const char* filepath) {
    check_valid_filepath(filepath);
    push_memory();
    char* directory = get_base_name(filepath);
    char* base_name_without_extension = remove_extension(get_base_name(filepath));

    int new_filepath_length = (directory ? strlen(directory) : 0) + strlen(base_name_without_extension) + strlen(".ent") + 1;
    char* new_filepath = malloc_track_global(new_filepath_length);

    if (directory) {
        strcpy(new_filepath, directory);
    }
    strcat(new_filepath, base_name_without_extension);
    strcat(new_filepath, ".ent");

    pop_memory();
    return new_filepath;
}

char* get_output_filepath(const char* filepath) {
    check_valid_filepath(filepath);
    push_memory();
    char* directory = get_base_path(filepath);
    char* base_name= remove_extension(get_base_name(filepath));

    int new_filepath_length = (directory ? strlen(directory) : 0) + strlen(base_name) + strlen(".obj") + 1;
    char* new_filepath = malloc_track_global(new_filepath_length);

    if (directory) {
        strcpy(new_filepath, directory);
    }
    strcat(new_filepath, base_name);
    strcat(new_filepath, ".obj");

    pop_memory();
    return new_filepath;
}
