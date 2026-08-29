#include "Capture.h"
#include <iostream>
using namespace std::chrono_literals;

void Capture::fillBuffer() {
    auto start{std::chrono::steady_clock::now()};
    int reads{};
    while (std::chrono::steady_clock::now() - start < m_target) {
        m_port.read();
        m_allSamples.insert(m_allSamples.end(), std::begin(m_port.getBuffer()), std::end(m_port.getBuffer()));
        ++reads;
    }
    auto elapsed = std::chrono::steady_clock::now() - start;



}