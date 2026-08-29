#include "Capture.h"
#include <iostream>
using namespace std::chrono_literals;


//using chrono to time program to keep doing reads of the 512 byte buffer until
//the time limit is reached
void Capture::fillBuffer() {
    auto start{std::chrono::steady_clock::now()};
    int reads{};
    while (std::chrono::steady_clock::now() - start < m_target) {
        m_port.read();
        m_allSamples.insert(m_allSamples.end(), std::begin(m_port.getBuffer()), std::end(m_port.getBuffer()));
        ++reads;
    }
}

//should append the sample numberwhen it changes
void Capture::detectTransitions() {
    m_allTransitions.clear();
    for (std::ptrdiff_t i{}; i < std::ssize(m_allSamples)-1; ++i) {
        if (m_allSamples[i] != m_allSamples[i+1]) {
            Transition x;
            x.sample = i+1;
            //here the xor identifies when two samples are diff
            x.bitsChanged = m_allSamples[i] ^ m_allSamples[i+1];
            m_allTransitions.push_back(x);
        }
    }
}

//
void Capture::timing() {
    m_allTimings.clear();
    //bits should start high
    int startPos{};
    for (std::ptrdiff_t i{}; i < std::ssize(m_allTransitions); ++i) {
        Levels x;
        //this should compare two specific bits on both uint8s, with &1 clearing everythng else
        if ((m_allTransitions[i].bitsChanged >> m_channel) & 1) {
            x.volts = (m_allSamples[m_allTransitions[i].sample-1] >> m_channel) & 1;
            x.duration = m_allTransitions[i].sample - startPos;
            startPos = m_allTransitions[i].sample;
            m_allTimings.push_back(x);
        }
    }
}