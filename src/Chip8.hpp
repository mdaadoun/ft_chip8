#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstring>
#include "utils.hpp"

typedef unsigned char   byte; // 2 nibbles, 1 byte, 8bit
typedef unsigned short  word; // 4 nibbles, 2 bytes, 16bit

#define MEMORY_SIZE 0xFFF
#define START_PROGRAM_ADDRESS 0x200
#define FONT_SET_ADDRESS 0x50

class Chip8 {
public:
    Chip8();
    ~Chip8();

    word getOpcode(word const &address) const;
    byte getNibble(word const &opcode, byte const &position) const;
    void loadRom(char const* filename);
    void dumpRom(char const* filename);
    void disassemblyRom(char const* filename);
//    void assemblyRom(char const* filename);

private:
    Chip8(Chip8 const &to_copy);
    Chip8 const &operator=(Chip8 const& to_copy);

    long loadFile(char const* filename);
    long _program_size;

    word _opcode; // store the currently executing instruction
    word _program_counter; // store the currently executing address - start at 0x200 (512)
    word _identifier; // 12 bits wide, used to store an address
    word _stack[0xF]; // store the address that the interpreter should return to when finished with a subroutine
    byte _stack_counter; // point to the topmost level of the stack.
    byte _memory[0xFFF]; // 4KB memory - 4096 - memory address are 12 bits
    byte _registers[0xF]; // 16 general purpose V registers 0-F, F is used as a carry flag
    byte _sound_timer; // if != 0, count down at 60 hertz, until they reach 0.
    byte _delay_timer; // if != 0, count down at 60 hertz, until they reach 0.
};
