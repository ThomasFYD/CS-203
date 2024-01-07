START:
    Lodi R1, 0

LOOP:
    Addi R1, 1
    Lodi R2, 34
    Sub R3, R1, R2

    Jmpz END_LOOP

    Jmp LOOP

END_LOOP:
    Halt