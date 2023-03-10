# OPCODES
## sources

* http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
* https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set
    * https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP%E2%80%908
* https://en.wikipedia.org/wiki/CHIP-8#Opcode_table 
* https://johnearnest.github.io/Octo/docs/SuperChip.html

## Standard Chip-8 Instructions
* [x] 00E0 - CLS
* [] 00EE - RET
* [x] 0nnn - SYS addr
* [x] 1nnn - JP addr
* [] 2nnn - CALL addr
* [] 3xkk - SE Vx, byte
* [] 4xkk - SNE Vx, byte
* [] 5xy0 - SE Vx, Vy
* [] 6xkk - LD Vx, byte
* [] 7xkk - ADD Vx, byte
* [] 8xy0 - LD Vx, Vy
* [] 8xy1 - OR Vx, Vy
* [] 8xy2 - AND Vx, Vy
* [] 8xy3 - XOR Vx, Vy
* [] 8xy4 - ADD Vx, Vy
* [] 8xy5 - SUB Vx, Vy
* [] 8xy6 - SHR Vx {, Vy}
* [] 8xy7 - SUBN Vx, Vy
* [] 8xyE - SHL Vx {, Vy}
* [] 9xy0 - SNE Vx, Vy
* [] Annn - LD I, addr
* [] Bnnn - JP V0, addr
* [] Cxkk - RND Vx, byte
* [] Dxyn - DRW Vx, Vy, nibble
* [] Ex9E - SKP Vx
* [] ExA1 - SKNP Vx
* [] Fx07 - LD Vx, DT
* [] Fx0A - LD Vx, K
* [] Fx15 - LD DT, Vx
* [] Fx18 - LD ST, Vx
* [] Fx1E - ADD I, Vx
* [] Fx29 - LD F, Vx
* [] Fx33 - LD B, Vx
* [] Fx55 - LD [I], Vx
* [] Fx65 - LD Vx, [I]

## Super Chip-48 Instructions

* https://github.com/Chromatophore/HP48-Superchip

* [] 00Cn - SCD nibble
* [] 00FB - SCR
* [] 00FC - SCL
* [] 00FD - EXIT
* [] 00FE - LOW
* [] 00FF - HIGH
* [] Dxy0 - DRW Vx, Vy, 0
* [] Fx30 - LD HF, Vx
* [] Fx75 - LD R, Vx
* [] Fx85 - LD Vx, R

## Octo

* https://github.com/JohnEarnest/Octo/tree/gh-pages/docs
* https://johnearnest.github.io/Octo/docs/XO-ChipSpecification.html