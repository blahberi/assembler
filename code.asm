MAIN: mov r3, LIST[2]
LOOP: jmp L1
prn #-5
mov STR[5], STR[2]
sub r1, r4
cmp r3, #2
bne END
L1: inc K
bne LOOP
END: hlt
STR: .string "abcdef"
LIST: .data 6, -9, 4
K: .data 22
