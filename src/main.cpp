#include "Chip8.hpp"

void help() {
    std::cout << "Help Chip8:" << std::endl
        << "\t./chip8 <rom_path> : run the rom.\n\n"
        << "\t./chip8 -b, --bytes <rom_path> :\n\t\t dump the rom bytes.\n\n"
        << "\t./chip8 -d, --disassembly <rom_path> :\n\t\t disassembly the rom, copy content in file <rom_path>.dis.txt\n\n"
//        << "\t./chip8 -a, --assembly <source_path> :\n\t\t assembly the asm text file at <source_path> as a binary rom <source_path>.ch8\n\n"
        << "\t./chip8 -h, --help :\n\t\t display this help." << std::endl;
    // ./chip8 -t <rom_path> ,trace mode to display register values and opcode executed each cycle
    // ./chip8 -c --compile octo.src , compile a XOchip program from octo source code
    // ./chip8 -d --debug , debug mode, step by step running the rom
    // ./chip101 , run the terminal and the tiny basic interpreter
    // -a disable audio
}

int main(int ac, char *av[]) {
    Chip8 interpreter;

    if (ac > 1 && ac < 4) {
        if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help"))
            help();
        else if (!strcmp(av[1], "-b") || !strcmp(av[1], "--bytes"))
            interpreter.dumpRom(av[2]);
        else if (!strcmp(av[1], "-d") || !strcmp(av[1], "--disassembly"))
            interpreter.disassemblyRom(av[2]);
//        else if (!strcmp(av[1], "-a") || !strcmp(av[1], "--assembly"))
//            interpreter.assemblyText(av[2]);
        else
            interpreter.loadRom(av[1]);
    } else {
        std::cerr << "Error arguments." << std::endl;
        help();
    }
    return (0);
}
