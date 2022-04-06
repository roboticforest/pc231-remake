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
 * during operation. One thing I don't have anymore is Fritz's original VM, so I won't be able to make the
 * behavior of mine match his. Do I want to though? It doesn't have to be exact.
 */


#include <iostream>
#include <string>

// TODO: Add an endianness check? Do we care for this project?
union Word_12Bit {
    unsigned short raw_data: 12;
    struct {
        unsigned short lowNibble: 4;
        unsigned short midNibble: 4;
        unsigned short highNibble: 4;
    };
};

void testWord() {
    using namespace std;
    Word_12Bit data {};
    cout << "Raw Word:\t" << data.raw_data << endl; // Uninitialized. Should be a random value.
    data.raw_data = 5; // Constant assignment.
    cout << "Raw Word:\t" << data.raw_data << endl;
    int num = 0x421; // Dec: 1057
    data.raw_data = num; // Variable assignment.
    cout << "Raw Word:\t" << data.raw_data << endl;
    cout << "High Nibble:\t" << data.highNibble << endl; // Should be: 4
    cout << "Mid  Nibble:\t" << data.midNibble << endl;  // Should be: 2
    cout << "Low  Nibble:\t" << data.lowNibble << endl;  // Should be: 1
}

class Memory {
  private:
    Word_12Bit* _memory = nullptr;
    unsigned short _size = 0;

  public:
    explicit Memory(unsigned short size) : _size(size) {
        _memory = new Word_12Bit[_size];
        // Initialize all memory to 0.
        for (auto i = 0; i < _size; ++i) {
            auto word = _memory[i];
            word.raw_data = 0;
        }
    }

    virtual ~Memory() { delete[] _memory; }

    // It doesn't make sense to move or copy memory chips in a running computer.
    Memory(const Memory&) = delete;
    Memory& operator=(const Memory&) = delete;
    Memory& operator=(const Memory&&) = delete;

    Word_12Bit& operator[](unsigned short pos) {
        return _memory[pos % _size];
    }

    unsigned short capacity() const {
        return _size;
    }
};

int main() {

    Memory mainMemory(256);
    std::string hexTriple;
    unsigned int i = 0;
    bool readingProgram = true;
    std::cout << "LOAD PROGRAM:" << std::endl;

    // TODO: While this is a bit better, (sometime when you're not about to fall asleep at your
    //  keyboard) replace this with a character by character parse like you're used to doing.
    //  OH! And you can also add in a search for "END" along with the EOF character.
    while (readingProgram) {
        std::cin >> hexTriple;
        if (!std::cin.good()) {
            if (std::cin.eof()) {
                std::cout << "PROGRAM LOADED." << std::endl;
                readingProgram = false;
            }
            else {
                std::cout << "READ ERROR." << std::endl;
                std::cin.clear();  // REMEMBER! You have to clear the error state before you can do ANYTHING with the stream.
                std::cin.ignore();  // With the error state cleared, you can now ignore the offending character.
                continue;
            }
        }
        if (hexTriple.length() == 3) {
            try {
                mainMemory[i].raw_data = std::stoi(hexTriple, nullptr, 16);
            }
            catch (const std::invalid_argument& exception) {
                std::cout << "BAD HEX TRIPLE. SKIPPING WORD." << std::endl;
                continue;
            }
            i = (i + 1) % mainMemory.capacity();
        }
    }

    return 0;
}

