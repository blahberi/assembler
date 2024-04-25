/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_HANDLE_LABEL_H
#define ASSEMBLER_HANDLE_LABEL_H

struct Context;

typedef int LabelHandler(struct Context* context);

int handle_label_instruction(struct Context* context);
int handle_label_data(struct Context *context);
int handle_label_entry(struct Context *context);
int handle_label_extern(struct Context *context);

#endif /* ASSEMBLER_HANDLE_LABEL_H */
