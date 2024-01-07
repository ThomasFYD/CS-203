START:
    Lodi    R1, 0

WHILE_LOOP:
    Lodi    R2, 15
    Sub     R3, R2, R1

    Jmpz   ELSE_BLOCK

    Addi    R1, 1
    Jmp     CONTINUE

ELSE_BLOCK:
    Lodi    R2, 2
    Add     R1, R1, R2

CONTINUE:
    Lodi    R2, 34
    Sub     R3, R1, R2
    Jmpz   END_LOOP
    Jmp     WHILE_LOOP

END_LOOP:
    Halt