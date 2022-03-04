// --------------------------------------------
// Course:      Prova de Aptidão Profissional
// Project:     Keypad Test
// Author:      Tomas de Sousa Tunes Lopes
// --------------------------------------------

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = {37, 39, 41, 43};

byte colPins[COLS] = {45, 47, 49, 51};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();
   if (key){ //Mostra qual a tecla que foi pressionada
    Serial.println(key);
  }
}