#include <Arduino.h>

volatile uint8_t buffer1[512]{};
volatile uint8_t buffer2[512]{};
volatile int index{};
volatile bool firstRun{true};
volatile bool readyToExtract{false};

void setup() {
    // write your initialization code here

    Serial.begin(9600);
    //here i am directly setting all portd pins (which is 0-7) to input with bitmask
    DDRD &= 0;

    //all pins will have pullup on by setting all bits of portd to high
    PORTD |= 255;

    //i should only have wgm12 turned on which is 3rd bit in register TCCR1b so im setting iit here
    //this combo gives mode 4 which will do CTC with OCR1A as max
    TCCR1A &= ~(1 << 0);
    TCCR1A &= ~(1 << 1);

    TCCR1B |= (1 << 3);
    TCCR1B &= ~(1 << 4);
    //first three bits are CS1 bits, determines what prescaler should be based on these bits. i want prescaler
    // of 1 so it should be 0 0 1
    TCCR1B |= (1 << 0);
    TCCR1B &= ~(1 << 1);
    TCCR1B &= ~(1 << 2);
    //setting counter to 0
    TCNT1 = 0;
    //doing 100 khz sampling so for 16 mhz arduino clock i will do 159 samples as max (0 counts)
    OCR1A = 159;
    //timsk1 handles interrupts, bit 1 is OCIE1A, makes timer interrupt when ocr1a is matched
    TIMSK1 |= (1 << 1);
}


ISR(TIMER1_COMPA_vect) {
    //samples here

    //here i am making a ping pong buffer. when the first gets full it signals to
    //switch to the second one and turns the readytoextract bool to true so the serial will
    //extract the data from it on time
    if (firstRun) {
        buffer1[index] = PIND;
        ++index;
        if (index >511 ) {
            firstRun = false;
            index=0;
            readyToExtract = true;
        }

    }
    else if (!firstRun) {
        buffer2[index] = PIND;
        ++index;
        if (index >511 ) {
            firstRun = true;
            index=0;
            readyToExtract = true;
        }
    }
}


void loop() {
    // write your code here
    if (readyToExtract) {
        //first buffer finished uploading here
        if (!firstRun) {
            for (uint8_t x : buffer1) {
                Serial.write(x);
            }
        }
        //second buffer finishes uploading here
        else {
            for (uint8_t x : buffer2) {
                Serial.write(x);
            }
        }

    }
    readyToExtract = false;


}