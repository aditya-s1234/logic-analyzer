#pragma once
#include <string>
#include <string_view>
#include "termios.h"
#include <array>
class SerialPort {
private:
    termios m_original;
    std::string m_portName{};
    unsigned long m_baudRate{};
    int m_fileDescriptor{};
    std::array<uint8_t, 512> m_programBuffer{};

public:
    SerialPort(std::string_view portName, unsigned long baudRate)
        :m_portName{portName}, m_baudRate{baudRate}
    {
    }

    void open();
    void close();
    bool checkOpen();
    void read();

};