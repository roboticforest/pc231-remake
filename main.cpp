/*
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright Copyright © 2022 David Vitez. All rights reserved.
 */

/*
 * What do we need...
 * Registers
 * Memory.
 * Loading a program into memory.
 * A read-eval loop.
 *   Interpreting each of each instruction.
 *   A check to see if the machine should halt.
*/

/*
 * The original assignment got a compiled program from the user as a single long string of hex pairs. The program
 * would then be immediately loaded into memory and run. If there was any output from the program it would display
 * during operation. One thing I don't have any more is Fritz's original VM, so I won't be able to make the
 * behavior of mine match his. Do I want to though? It doesn't have to be exact.
 */


#include <iostream>
#include <string>

struct Word_12Bit {
    union {
        unsigned short raw_data: 12;
        struct {
            unsigned short lowNibble: 4;
            unsigned short midNibble: 4;
            unsigned short highNibble: 4;
        };
    };
};

class Memory {
  private:
    Word_12Bit* _memory = nullptr;
    unsigned short _size = 0;

  public:
    Memory(unsigned short size) : _size(size) { _memory = new Word_12Bit[_size]; }

    virtual ~Memory() { delete _memory; }

    Memory(const Memory&) = delete;
    Memory& operator=(const Memory&) = delete;
    Memory& operator=(const Memory&&) = delete;

    Word_12Bit operator[](unsigned short pos) {
        if (pos < 0 || pos >= _size) {
            std::cout << "ERROR" << std::endl;
        }
    }

};

int main() {

    std::string program;

    Memory mainMemory(256);

    std::cout << "LOAD PROGRAM:" << std::endl;
    std::getline(std::cin, program);
    std::cout << program;
    return 0;
}
