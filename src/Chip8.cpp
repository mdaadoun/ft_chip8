#include "Chip8.hpp"


#define MSG_ERROR_FILE_PATH "Error: file."

typedef enum e_key_err {
    NO_ERROR,
    ERROR_FILE_PATH,
    ERROR_FILE_READ,
    ERROR_ARGS_NB,
    ERROR_OPCODE,
    ERROR_DISPLAY
} t_key_err;

byte font_set[0x50] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {
    this->_program_counter = START_PROGRAM_ADDRESS;
    this->_identifier = 0x0;
    this->_stack_counter = 0x0;
    this->_delay_timer = 0x0;
    this->_sound_timer = 0x0;

//    memset();
    word i = 0x0;
    while (i < MEMORY_SIZE) {
        this->_memory[i] = 0x0;
        i++;
    }
    i = 0x0;
    while (i < 0xF) {
        this->_registers[i] = 0x0;
        this->_stack[i] = 0x0;
        i++;
    }
}

Chip8::~Chip8() {}

long Chip8::loadFile(const char *filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streampos size = file.tellg();
    if (file) {
        std::vector<char> buffer(size);
        file.seekg(0, std::ios::beg);
        file.read(buffer.data(), size);
        for (int i = 0; i < size; i++)
            this->_memory[START_PROGRAM_ADDRESS + i] = static_cast<byte>(buffer[i]);
        std::cout << filename << " is loaded in memory." << std::endl;
        std::cout << "File size: " << size << std::endl;
        file.close();
    }
    else
        std::cout << MSG_ERROR_FILE_PATH << std::endl;
        // throw exception ?
    return static_cast<std::streamoff >(size);
}

byte Chip8::getNibble(word const &opcode, byte const &position) const {
    switch (position) {
        case 1:
            return (opcode >> 12  & 0xf);
        case 2:
            return (opcode >> 8  & 0xf);
        case 3:
            return (opcode >> 4  & 0xf);
        case 4:
            return (opcode & 0xf);
        default:
            std::cerr << "Error: Can't get nibble to this position." << std::endl;
            break;
    }
    return 0x0;
}

word Chip8::getOpcode(const word &address) const {
    byte byte_high;
    byte byte_low;
    word opcode;
    byte_high = this->_memory[address] & 0xff;
    byte_low = this->_memory[address + 1] & 0xff;
    opcode = byte_high << 8 | byte_low;
    return (opcode);
}

void Chip8::loadRom(const char *filename) {
    std::cout << "Load rom " << filename << std::endl;
    this->_program_size = this->loadFile(filename);
}

// read file as binary and dump hexadecimal values in a file
void Chip8::dumpRom(const char *filename) {
    std::cout << "Rom dump " << filename << std::endl;
    this->_program_size = this->loadFile(filename);
    std::string save_filename = std::string(filename)  + ".dump.txt";
    std::ofstream save_file;
    save_file.open(save_filename.c_str());

    word i = START_PROGRAM_ADDRESS;
    while (i < START_PROGRAM_ADDRESS + this->_program_size) {
        if (i % 16 == 0)
            save_file << "0x" << std::hex << std::setw(3) << std::setfill('0') << i << ": ";
        save_file << std::setw(2) << std::hex << std::setfill('0') << std::right << (this->_memory[i] & 0xff);
        if ( (i + 1) % 2 == 0 )
            save_file << ' ';
        if ( (i + 1) % 4 == 0 )
            save_file << ' ';
        if ( (i + 1) % 8 == 0 )
            save_file << ' ';
        if ( (i + 1) % 16 == 0 )
            save_file << std::endl;
        i += 0x1;
    }
    save_file.close();
    std::cout << std::endl;
    std::cout << "Saved to file " << save_filename << std::endl;
}

// loop through memory and write each instuction
void Chip8::disassemblyRom(const char *filename) {
    std::cout << "Rom disassembly file " << filename << std::endl;
    this->_program_size = this->loadFile(filename);
    std::string directory = "./assembly/";
    check_existing_directory(directory);
    std::string save_filename = directory + std::string(filename)  + ".asm.txt";
    std::ofstream save_file;
    save_file.open(save_filename.c_str());

    // Columns: $adress | instruction mnemonic | ;comment description
    word i = START_PROGRAM_ADDRESS;
    while (i < START_PROGRAM_ADDRESS + this->_program_size) {
        word o;
        o = Chip8::getOpcode(i);
        byte n1 = Chip8::getNibble(o, 1);
        byte n2 = Chip8::getNibble(o, 2);
        byte n3 = Chip8::getNibble(o, 3);
        byte n4 = Chip8::getNibble(o, 4);
        save_file << "$" << std::hex << i << ' ';
        save_file << std::setw(4) << std::setfill('0') << +o << std::setw(2)  << ": ";
        // set color to distinguish type of chip8 opcodes (schip, xochip, xechip...) or errors/not implemented.
        switch (n1) {
            case (0x0):
                switch (o) {
                    case 0x00e0: // 0x00E0 ;CLS, Clears the display.
                        save_file << "CLS ;Clear the display." << std::endl;
                        break;
                    case 0x00ee: // 0x00EE ;Returns from a subroutine.
                        save_file << "RET ;Returns from a subroutine." << std::endl;
                        break;
                    default: // 0x0NNN ;RCA 1802/VIP instructions are not implemented
                        save_file << "SYS ;Call legacy opcode." << std::endl;
                }
                break;
            case (0x1): // 0x1NNN ;Jumps to address NNN.
                save_file << "JP " << std::hex << +n2 << +n3 << +n4;
                save_file << " ;Jump to address $" << std::hex << +n2 << +n3 << +n4 << std::endl;
                // this->_program_counter = _opcode & 0xfff;
                break;
            case(0x2): // 0x2NNN ;Calls subroutine at NNN.
                save_file << "CALL " << std::hex << +n2 << +n3 << +n4;
                save_file << " ;Call subroutine at $" << std::hex << +n2 << +n3 << +n4 << std::endl;
                // save program_counter to stack
                // this->_program_counter = _opcode & 0xfff;
                break;
            case(0x3): // 0x3XNN ;Skips the next instruction if VX equals NN.
                save_file << "SE " << std::hex << +n2 << "==" << +n3 << +n4;
                save_file << " ;Skips the next instruction if VX (V" << +n2 << ") equals NN (" << +n3 << +n4 << ")." << std::endl;
                // The interpreter compares register VC to NN, and if they are equal, increments the program counter by 2.
                break;
            case(0x4):
                save_file << "Opcode instruction not implemented." << std::endl;
                break;
            case(0x5):
                save_file << "Opcode instruction not implemented." << std::endl;
                break; // 0x6XNN ;The interpreter puts the value NN into register VX.
            case(0x6):
                save_file << "LD V" << std::hex << +n2 << "=" << +n3 << +n4;
                save_file << " ;Set the register V" << std::hex << +n2 <<  " to " << +n3 << +n4 << std::endl;
                break;
            case(0x7): // 0x7XNN ;Adds the value NN to the value of register VX, then stores the result in VX.
                save_file << "ADD V" << std::hex << +n2 << "=V" << +n2 << "+" << +n3 << +n4;
                save_file << " ;Adds the value " << std::hex << +n3 << +n4 <<  " to the register V" << +n2
                << ", then stores the result in V" << +n2 << "." << std::endl;
                break;
            case(0x8):
                switch (n4) {
                    case(0x0): // 0x8XY0 ;Stores the value of register Vy in register Vx.
                        save_file << "LD V" << std::hex << +n2 << "=V" << +n3;
                        break;
                    case(0x1):
                        break;
                    case(0x2):
                        break;
                    case(0x3):
                        break;
                    case(0x4):
                        break;
                    case(0x5):
                        break;
                    case(0x6):
                        break;
                    case(0x7):
                        break;
                    case(0xe):
                        break;
                    default:
                        save_file << "Opcode instruction not implemented." << std::endl;
                }
                break;
            case(0x9):
                save_file << "Opcode instruction not implemented." << std::endl;
                break;
            case(0xa): // 0xaNNN ;The value of register I is set to nnn.
                save_file << "LD I=" << std::hex << +n2 << +n3 << +n4;
                save_file << " ;register I set to " << std::hex << +n2 << +n3 << +n4 << std::endl;
                break;
            case(0xb):
                save_file << "Opcode instruction not implemented." << std::endl;
                break;
            case(0xc):
                save_file << "Opcode instruction not implemented." << std::endl;
                break;
            case(0xd):
                save_file << "Opcode instruction not implemented." << std::endl;
                break;
            case(0xe):
                save_file << "Opcode instruction not implemented." << std::endl;
                break;
            case(0xf):
                save_file << "Opcode instruction not implemented." << std::endl;
                break;
            default:
                save_file << "Opcode instruction not implemented." << std::endl;
        }

        i += 0x2;
    }
    save_file.close();
    std::cout << std::endl;
    std::cout << "Saved to file " << save_filename << std::endl;
}
