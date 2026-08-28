#include "SerialPort.h"
#include "fcntl.h"
#include "unistd.h"
#include "termios.h"

//ignore the comments on this page, they are notes for me

void SerialPort::open() {
    m_fileDescriptor = ::open("/dev/cu.usbmodem101", O_RDONLY);
    //saving original config in case i need it again
    tcgetattr(m_fileDescriptor, &m_original);
    termios newConfig{m_original};
    cfsetispeed(&newConfig, 2000000);
    cfsetospeed(&newConfig, 2000000);

    //function that changes IO bits for me, just makes the input/output raw bytes instead of converting anything
    cfmakeraw(&newConfig);

    //setting control bits to interpret 8N1 receiving
    newConfig.c_cflag |= CS8; //turns on 8 data bits
    newConfig.c_cflag |= CREAD; //allows the driver to receive stuff
    newConfig.c_cflag &= ~(PARENB); //disables parity bit
    newConfig.c_cflag &= ~(CSTOPB); //disables 2 stop bit (only 1)
    newConfig.c_cflag |= CLOCAL; //i think this instantly opens the port vs waiting for a signal

    //should take in at least 1 byte, since it's nonblocking it shouldn't wait it just keeps returning (for read())
    newConfig.c_cc[VMIN] = 1;
    newConfig.c_cc[VTIME] = 0;

    tcsetattr(m_fileDescriptor, TCSANOW, &newConfig);
}

void SerialPort::read() {
    //since read will copy any amount of bytes from 1 to 512, it should keep doing it until it fills the buffer up
    int bytesTransferred{};
    int movement{};
    int tracker{512};
    do {
        //this changes its starting position and how much the max transfer capacity should be based on how much it alr transferred
        bytesTransferred = ::read(m_fileDescriptor, m_programBuffer.data() + movement, tracker);
        tracker -= bytesTransferred;
        movement+= bytesTransferred;
    } while (tracker > 0);
}
