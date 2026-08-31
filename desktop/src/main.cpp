#include <iostream>
#include "SerialPort.h"
#include "Capture.h"
#include "UartDecoder.h"
#include <vector>
#include <bitset>
#include <chrono>
#include <thread>
int main() {
    SerialPort port{"a", 9600};
    port.open();
    Capture recorder(port, 10000);
    recorder.fillBuffer();
    recorder.detectTransitions();
    recorder.timing();
    UartDecoder decoder {recorder, 9600, 5};
    decoder.captureUart();
    std::vector<uint8_t> data {decoder.getData()};
    for (const auto& x : data) {
        std::cout << std::hex << (int)x << " ";
    }
    std::cout << std::dec << "\n";

    return 0;
}