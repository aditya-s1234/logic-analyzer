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
    taker.detectTransitions();
    taker.timing();

    auto elapsed{
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start
        )
    };

    std::cout << "timings: " << std::ssize(taker.getTimings()) << '\n';

    for (const auto& x : taker.getTimings()) {
        std::cout << "level: " << static_cast<int>(x.volts)
                  << " duration: " << x.duration << '\n';
    }

    return 0;
}