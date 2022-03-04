// --------------------------------------------
// Course:      Prova de Aptidão Profissional
// Project:     Coin Acceptor Test
// Author:      Tomas de Sousa Tunes Lopes
// --------------------------------------------

const byte coinDetector = 2;

float banca;

void setup() {
    Serial.begin(9600);
    pinMode(coinDetector, INPUT);
}

void loop() {
    static unsigned long prevCoinMillis = 0;
    static float coinValue = 0;

    unsigned long currentMillis = millis();
    
    if((currentMillis - prevCoinMillis >= 50) && (digitalRead(coinDetector) == HIGH)) {
        prevCoinMillis = currentMillis;
        banca += 0.5;
        Serial.print(banca);
        Serial.println("€");
    }
}