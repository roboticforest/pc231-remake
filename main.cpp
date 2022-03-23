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
    Word_12Bit() = default;

    union {
        unsigned short raw_data: 12;
        struct {
            unsigned short lowNibble: 4;
            unsigned short midNibble: 4;
            unsigned short highNibble: 4;
        };
    };
};

void testWord(){
    using namespace std;
    Word_12Bit data;
    cout << "Raw Word:\t" << data.raw_data << endl; // Uninitialized. Should be a random value.
    data.raw_data = 5;
    cout << "Raw Word:\t" << data.raw_data << endl;
    int num = 0x421; // Dec: 1057
    data.raw_data = num;
    cout << "Raw Word:\t" << data.raw_data << endl;
    cout << "High Nibble:\t" << data.highNibble << endl;
    cout << "Mid  Nibble:\t" << data.midNibble << endl;
    cout << "Low  Nibble:\t" << data.lowNibble << endl;
}

class Memory {
  private:
    Word_12Bit* _memory = nullptr;
    unsigned short _size = 0;

  public:
    Memory(unsigned short size) : _size(size) {
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

    Word_12Bit & operator[](unsigned short pos) {
        return _memory[pos % _size];
    }
};

int main() {

//    testWord();
//    return 0;

    Memory mainMemory(256);
    std::string hexTriple;
    unsigned int i = 0;
    std::cout << "LOAD PROGRAM:" << std::endl;

    // BUG: Program terminates with an error status after reading an EOF character from the terminal. It should accept that as an end to the user input for a program.
    bool validInput = true;
    while (!std::cin.eof()) {
        std::cin >> hexTriple;
        if (!std::cin.good()) {
            std::cin.clear();  // REMEMBER! You have to clear the error state before you can do ANYTHING with the stream.
            std::cin.ignore();  // With the error state cleared, you can now ignore the offending character.
            validInput = false;
            break;
        }
        if (hexTriple.length() != 3) {
            validInput = false;
            break;
        }
        try {
            mainMemory[i].raw_data = std::stoi(hexTriple, nullptr, 16);
        }
        catch (const std::invalid_argument& exception) {
            validInput = false;
            break;
        }
        ++i; // TODO: Check if i > mainMemory.size().
        // TODO: Handle each possible error with an appropriate message for the end user.
    }

    if (!validInput) {
        std::cout << "INVALID PROGRAM" << std::endl;
        return -1;
    }
    return 0;
}

