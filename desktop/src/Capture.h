#pragma once
#include "SerialPort.h"
#include <vector>
#include <chrono>

//this is for samples that are different from their previous one
struct Transition {
    int sample{};
    uint8_t bitsChanged{};
};

//
struct Levels {
    bool volts{};
    int duration{};
};


class Capture {
private:
    std::vector<uint8_t> m_allSamples{};
    std::chrono::milliseconds m_target{};
    SerialPort m_port;
    std::vector<Transition> m_allTransitions{};
    std::vector<Levels> m_allTimings{};
    int m_channel{5};

public:
    Capture (SerialPort& port, int target)
        :m_target{target}, m_port{port} {
        m_allSamples.reserve(target/1000 * 100000);
    }

    std::vector<uint8_t>& getSamples() {
        return m_allSamples;
    }

    std::vector<Transition>& getTransitions() {
        return m_allTransitions;
    }

    std::vector<Levels>& getTimings() {
        return m_allTimings;
    }

    void setChannel(int x) {
        m_channel = x;
    }

    void fillBuffer();
    void detectTransitions();
    void timing();
};