# Description:
I developed a reusable library of over 25 subprograms in MIPS assembly using the MARS simulator.

The library covers array manipulation, arithmetic, bitwise logic, string handling and console I/O.  It also includes a Bubble Sort built on a modular swap routine, functions for array sum/average and functions for forward/reverse printing.  I also designed several bit-level utilities, such as circular shifts, NAND/NOR/NOT and shift based multiplication (×4 and ×10) without multiply instructions.  

Every subprogram follows the MIPS calling convention with stack frames and a standardized header documenting its purpose, parameters, returns and side effects.

I wrote an interactive test driver (utilsTestCode.asm) that takes user input and checks each routine's output against the equivalent built in MIPS instruction.