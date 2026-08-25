#include <Arduino.h>
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
}

void loop() {
// write your code here
    Serial.println(PINB, BIN);
    delay(1000);

}