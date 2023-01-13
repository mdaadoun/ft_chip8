# A Chip8 Ecosystem

## steps:
1. Build disassembler, assembler, octo compiler and debugger.
2. Graphic device and IDE for play and coding chip8 games with octo.
3. Implement it to an embedded raspberry pi pico interpreter.
4. Program some classic games to learn instructions and octo.
5. Add a terminal, a tiny basic interpreter and new chip101 instructions ?
6. Document clearly all the project and build pdf project.

## todo:
* implement opcode for guess program then try to run guess
* Remplacer array par des vector ?
* Remplacer loop pour initialiser a 0 par des memset, solution c++
* Save disassembly to text file <filename>.asm.txt

## Main ref:
* http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

## references:
* https://chip-8.github.io/
* https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set
* https://en.wikipedia.org/wiki/CHIP-8

* https://github.com/search?l=C%2B%2B&q=chip8&type=Repositories

* https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
* http://www.emulator101.com/introduction-to-chip-8.html
* https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP%E2%80%908
* https://github.com/JohnEarnest/Octo
* https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
* https://johnearnest.github.io/Octo/docs/BeginnersGuide.html
* https://austinmorlan.com/posts/chip8_emulator/
* https://tonisagrista.com/blog/2021/chip8-spec/

### Standard Chip-8 Instructions
00E0 - CLS
00EE - RET
0nnn - SYS addr
1nnn - JP addr
2nnn - CALL addr
3xkk - SE Vx, byte
4xkk - SNE Vx, byte
5xy0 - SE Vx, Vy
6xkk - LD Vx, byte
7xkk - ADD Vx, byte
8xy0 - LD Vx, Vy
8xy1 - OR Vx, Vy
8xy2 - AND Vx, Vy
8xy3 - XOR Vx, Vy
8xy4 - ADD Vx, Vy
8xy5 - SUB Vx, Vy
8xy6 - SHR Vx {, Vy}
8xy7 - SUBN Vx, Vy
8xyE - SHL Vx {, Vy}
9xy0 - SNE Vx, Vy
Annn - LD I, addr
Bnnn - JP V0, addr
Cxkk - RND Vx, byte
Dxyn - DRW Vx, Vy, nibble
Ex9E - SKP Vx
ExA1 - SKNP Vx
Fx07 - LD Vx, DT
Fx0A - LD Vx, K
Fx15 - LD DT, Vx
Fx18 - LD ST, Vx
Fx1E - ADD I, Vx
Fx29 - LD F, Vx
Fx33 - LD B, Vx
Fx55 - LD [I], Vx
Fx65 - LD Vx, [I]
### Super Chip-48 Instructions
00Cn - SCD nibble
00FB - SCR
00FC - SCL
00FD - EXIT
00FE - LOW
00FF - HIGH
Dxy0 - DRW Vx, Vy, 0
Fx30 - LD HF, Vx
Fx75 - LD R, Vx
Fx85 - LD Vx, R