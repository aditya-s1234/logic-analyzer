#pragma once
#include <vector>
#include "Capture.h"
#include "SerialPort.h"


class UartDecoder {
private:
    std::vector<uint8_t> m_uartData{};
    std::vector<Levels> m_timings{};
    std::vector<uint8_t> m_allSamples{};
    double m_baudRate{};
    int m_channel{};

public:

    UartDecoder (Capture& x, double baudRate, int channel)
        :m_timings{x.getTimings()}, m_baudRate{baudRate}, m_allSamples{x.getSamples()}, m_channel{channel}
    {}

    void captureUart();

};