#include <Arduino.h>

volatile uint8_t snapshot{};

void setup() {
// write your initialization code here

    Serial.begin(9600);
    //here i am directly setting all portb pins (which is 8-11) to input with bitmask
    DDRB &= ~(1 << PB0);
    DDRB &= ~(1 << PB1);
    DDRB &= ~(1 << PB2);
    DDRB &= ~(1 << PB3);
    DDRB &= ~(1 << PB4);
    DDRB &= ~(1 << PB5);
    //since it's input this is similar to digitalwrite so they will have pullup turned on
    PORTB |= (1 <<PB0);
    PORTB |= (1 <<PB1);
    PORTB |= (1 <<PB2);
    PORTB |= (1 <<PB3);
    PORTB |= (1 <<PB4);
    PORTB |= (1 <<PB5);
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
    snapshot = PINB;
}


void loop() {
// write your code here
    Serial.println(snapshot, BIN);
    delay(500);

}