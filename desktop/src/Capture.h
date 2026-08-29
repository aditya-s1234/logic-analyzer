#pragma once
#include "SerialPort.h"
#include <vector>
#include <chrono>


class Capture {
private:
    std::vector<uint8_t> m_allSamples{};
    std::chrono::milliseconds m_target{};
    SerialPort m_port;
public:
    Capture (SerialPort& port, int target)
        :m_target{target}, m_port{port}
    {}

    std::vector<uint8_t>& getSamples() {
        return m_allSamples;
    }

    void fillBuffer();
};