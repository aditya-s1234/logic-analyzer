#include <iostream>
#include "SerialPort.h"
#include <bitset>
int main() {


    SerialPort port("blah", 1);
    port.open();
    port.read();
    std::array<uint8_t, 512> y {port.getBuffer()};
    for (uint8_t x : y)
        std::cout << std::bitset<8>(x) << '\n';

    return 0;
}
