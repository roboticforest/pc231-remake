/*
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright Copyright © 2022 David Vitez. All rights reserved.
 */

#include <iostream>
#include <string>

int main() {
    /*
     * The original assignment got a compiled program from the user as a single long string of hex pairs. The program
     * would then be immediately loaded into memory and run. If there was any output from the program it would display
     * during operation. One thing I don't have any more is Fritz's original VM, so I won't be able to make the
     * behavior of mine match his. Do I want to though? It doesn't have to be exact.
     */
    std::string program;

    std::cout << "LOAD PROGRAM:" << std::endl;
    std::getline(std::cin, program);
    std::cout << program;
    return 0;
}
