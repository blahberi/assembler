/*
 Author: Eitan H.
*/

#ifndef ASSEMBLER_HANDLE_LABEL_H
#define ASSEMBLER_HANDLE_LABEL_H

struct Context;

typedef int LabelHandler(struct Context* context);

int handle_label_instruction(struct Context* context); /* Handle the label for instructions */
int handle_label_data(struct Context *context); /* Handle the label for .data and .string directives */
int handle_label_entry(struct Context *context); /* Handle the label for .entry directive */
int handle_label_extern(struct Context *context); /* Handle the label for .extern directive */

#endif /* ASSEMBLER_HANDLE_LABEL_H */
