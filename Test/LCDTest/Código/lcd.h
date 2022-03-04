// --------------------------------------------
// Course:      Prova de Aptidão Profissional
// Project:     LCD Test
// Author:      Tomas de Sousa Tunes Lopes
// --------------------------------------------

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0 ,4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(7, 1);
  lcd.print("Ola!!!");
}

void loop() {}