/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_HANDLE_LABEL_H
#define ASSEMBLER_HANDLE_LABEL_H

typedef struct context Context;

typedef int LabelHandler(Context* context);

int handle_label_instruction(Context* context);
int handle_label_data(Context *context);
int handle_label_entry(Context *context);
int handle_label_extern(Context *context);

#endif /* ASSEMBLER_HANDLE_LABEL_H */
