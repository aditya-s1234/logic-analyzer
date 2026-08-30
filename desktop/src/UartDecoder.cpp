#include "UartDecoder.h"


void UartDecoder::captureUart() {
    std::ptrdiff_t i{0};
    while (i < std::ssize(m_timings)) {
        uint8_t uartByte{0};
        int startLoc{};
        //my sampler only works at 94.6khz rn. this is how long a start/data/stop bit should last
        double bitDuration {94600.0 / m_baudRate};
        //here i am checking for start bit, so bit must be high then low, and it should be appoximately
        //this finds the center of the start bit with bitduration/2 and checks if specific value is low (to avoid issues with noise)
        if (m_timings[i].volts == 1 && (m_allSamples[std::lround(m_timings[i].sample + bitDuration/2)] >> m_channel & 1) == 0)  {
            startLoc = m_timings[i].sample + bitDuration/2;
            for (int j {1}; j < 9; ++j) {
                int dataBit {m_allSamples[std::lround(startLoc + bitDuration*j)] >> m_channel & 1};
                uartByte |= (dataBit << j-1);
            }
            //checking if its stop bit by moving one more length forward
            if ((m_allSamples[std::lround(startLoc + bitDuration*9)] >> m_channel & 1) == 1)
                m_uartData.push_back(uartByte);

            //now it will skip trying to detect each bit of the byte as a start bit and move onto the next one
            double frameEnd {m_timings[i].sample + bitDuration*10};
            while (i < std::ssize(m_timings) && m_timings[i].sample < frameEnd)
                ++i;
        }
        else
            ++i;
    }
}