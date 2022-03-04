// --------------------------------------------
// Course:      Prova de Aptidão Profissional
// Project:     Prototype
// Author:      Tomas de Sousa Tunes Lopes
// --------------------------------------------

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0 ,4, 5, 6, 7, 3, POSITIVE);

Servo servo1, servo2, servo3, servo4;

#define coinDetector 12
#define buttonRed 9
#define buttonBlue 8
#define buttonYellow 11
#define buttonGreen 10

void setup() {
      lcd.begin(20, 4);
      pinMode(coinDetector, INPUT);
      pinMode(buttonRed, INPUT_PULLUP);
      pinMode(buttonBlue, INPUT_PULLUP);
      pinMode(buttonYellow, INPUT_PULLUP);
      pinMode(buttonGreen, INPUT_PULLUP);
      servo1.attach(6);
      servo2.attach(5);
      servo3.attach(4);
      servo4.attach(3);
  }
}

void loop() {
      lcd.clear();
      delay(10);
      lcd.setCursor(3, 0);
      lcd.print("Introduz Moeda");
      lcd.setCursor(3, 1);
      lcd.print("de 50 Centimos");
      lcd.setCursor(3, 2);
      lcd.print("---Venduino---");
      lcd.setCursor(3, 3);
      lcd.print("By Tomas Lopes");
      while (true) {
        if (digitalRead(coinDetector) == LOW) {
        break;
        }
      }
      delay(100);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Escolha um Produto");
      lcd.setCursor(5, 1);
      lcd.print("A  B  C  D");
      lcd.setCursor(3, 3);
      lcd.print("---Venduino---");
      while (true) {
        if (digitalRead(buttonRed) == LOW) {
            servo1.writeMicroseconds(1950);
            delay(950);
            servo1.writeMicroseconds(1450);
            delay(10);
            break;
        }
        if (digitalRead(buttonBlue) == LOW) {
            servo2.writeMicroseconds(1950);
            delay(950);
            servo2.writeMicroseconds(1450);
            delay(10);
            break;
        }
        if (digitalRead(buttonYellow) == LOW) {
            servo3.writeMicroseconds(1950);
            delay(950);
            servo3.writeMicroseconds(1450);
            delay(10);
            break;
        }
        if (digitalRead(buttonGreen) == LOW) {
            servo4.writeMicroseconds(1950);
            delay(950);
            servo4.writeMicroseconds(1450);
            delay(10);
            break;
        }
      }
      lcd.setCursor(1, 0);
      lcd.print("Produto Entregue!!");
      delay(600);
      lcd.setCursor(3, 2);
      lcd.print("Volte Sempre!!");
      delay(3000);
      loop();
    }