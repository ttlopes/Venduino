// --------------------------------------------
// Course:      Prova de Aptidão Profissional
// Project:     InfraRed Servo Test
// Author:      Tomas de Sousa Tunes Lopes
// --------------------------------------------

#include <Servo.h>

Servo servo;

#define ir 8

void setup() {
    pinMode(ir, INPUT_PULLUP);
}

void loop() {
    while (true) {
        if (digitalRead(ir) == LOW) {
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