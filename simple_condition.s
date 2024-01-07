    Lodi    R1, 5
    Sub     R3, R1, R2
    Jmpn    ELSE

Addi    R1, 1
Jmp     END_IF

ELSE:
    Subi    R1, 1

END_IF:
    Halt
