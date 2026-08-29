#include <iostream>
#include "SerialPort.h"
#include "Capture.h"
#include <vector>
#include <bitset>
#include <chrono>
#include <thread>
int main() {

    SerialPort port{"a", 1};
    port.open();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    Capture taker{port, 5000};
    auto start{std::chrono::steady_clock::now()};
    taker.fillBuffer();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start) << '\n';
    std::cout << std::ssize(taker.getSamples());


    return 0;
}
