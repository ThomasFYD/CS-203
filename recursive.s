    Lodi    R1, 4
    Call    Fun
    Halt

Fun:
    Subi    R1, 1
    Jmpz   End_Fun
    Call    Fun

End_Fun:
    Ret