// --------------------------------------------
// Course:      Prova de Aptidão Profissional
// Project:     Button Servo Test
// Author:      Tomas de Sousa Tunes Lopes
// --------------------------------------------

#include <Servo.h>

Servo servo;

#define button 8

void setup() {
    pinMode(button, INPUT_PULLUP);
}

void loop() {
    while (true) {
        if (digitalRead(button) == LOW) {
            servo.attach(10);
            servo.writeMicroseconds(1950); // start
            delay(500);
            servo.writeMicroseconds(1450); // stop
            delay(500);
            servo.detach();
            break;
        }
    }
}