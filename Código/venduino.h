// --------------------------------------------
// Course:      Prova de Aptidão Profissional
// Project:     Venduino
// Author:      Tomas de Sousa Tunes Lopes
// --------------------------------------------

//Adiciona as Bibliotecas Necessárias: 1º,2º - LCD ; 3º - Servo; 4º - Keypad; 5º Ficheiro que Define Preços dos Produtos, Password e Valor da Moeda

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#include <Keypad.h>
#include <Preco_Password_Moeda.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0 ,4, 5, 6, 7, 3, POSITIVE);

Servo servo1, servo2, servo3, servo4, servo5;

//Define em que Pins é que os Itens Estão Connectados no Arduino

#define coinDetector 2
#define buttonRed 9
#define buttonBlue 8
#define buttonYellow 11
#define buttonGreen 10
#define buttonMoney 12

//Variáveis para a Password

char Data[Password_Length]; 
byte data_count = 0, master_count = 0;
char customKey;
char passKey;

//Define o Tamanho da Linha e Coluna do Keypad

const byte ROWS = 4;
const byte COLS = 4;

//Define a Tecla Correspondente Cada Butão do Keypad

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char passNumber[ROWS][COLS] = {
  {'1', '2', '3',},
  {'4', '5', '6',},
  {'7', '8', '9',},
  {'*', '0', '#',}
};

//Define em que Pins é que o Keypad está Connectado

byte rowPins[ROWS] = {37, 39, 41, 43};;
byte colPins[COLS] = {45, 47, 49, 51};

//Char para Escrever o Símbolo do Euro (€)

uint8_t euroChar[8] = {0x3,0x4,0x8,0x1f,0x8,0x1f,0x4,0x3};

//Variáveis

int red; //Stock Vermelho
int blue; //Stock Azul
int yellow;  //Stock Amarelo
int green;  //Stock Verde
int parf;
int producttype;
bool sld;
float banca;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Keypad passKeypad = Keypad(makeKeymap(passNumber), rowPins, colPins, ROWS, COLS);

void setup() {
    
//    Define as Dimensões (Altura e Lagura) do Ecrã LCD e Inicia a Interface
    
    lcd.begin(20, 4);
    Serial.begin(9600);
    
//    Cria o Char do Euro para o LCD
    
    lcd.createChar(0, euroChar);

//    Define o Estado Inicial do Coin Acceptor e dos Butões
    
    pinMode(coinDetector, INPUT);
    pinMode(buttonRed, INPUT_PULLUP);
    pinMode(buttonBlue, INPUT_PULLUP);
    pinMode(buttonYellow, INPUT_PULLUP);
    pinMode(buttonGreen, INPUT_PULLUP);
    pinMode(buttonMoney, INPUT_PULLUP);

    lcd.clear();
    
    lcd.setCursor(3, 2);
    lcd.print("---Venduino---");

    lcd.setCursor(3, 3);
    lcd.print("By Tomas Lopes");
    
    lcd.setCursor(0,0);
    lcd.print("Booting:");
    
//    Funcão para Contar de 0 a 100 (%) ao Iniciar
    
    for (int i = 0; i <= 100; i++) {
        lcd.setCursor(8,0);
        if (i<100) lcd.print(" ");
        if (i<10) lcd.print(" ");
        lcd.print(i);
        lcd.print("%");
        Serial.print("Booting: ");
        Serial.print(i);
        Serial.print("%");
        Serial.println("");
        delay(60);
    }
    
    Serial.println("--Venduino--- ");
    Serial.println("By Tomas Lopes \n");
    
    stock();
    
    paragrafo();
    
    stockatual();
}

void loop() {
    
//    Variáveis de Tempo (Millis)
    
    static unsigned long prevCoinMillis = 0;
    
    unsigned long currentMillis = millis();
    
//    Repor Banca

    banca = 0;
    
    bool sld = false;
    
    paragrafo();
    
    //    Label para "Goto" Statement
    
    opcoes:
    
    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print("Introduz Uma Moeda");

    lcd.setCursor(3, 1);
    lcd.print("de 50 Centimos");

    lcd.setCursor(3, 2);
    lcd.print("---Venduino---");

    lcd.setCursor(3, 3);
    lcd.print("By Tomas Lopes");
    
    Serial.println("Introduz Uma Moeda");
    Serial.println("de 50 Centimos");
    Serial.println("---Venduino---");
    Serial.println("By Tomas Lopes \n");
    
    while (true) {
        
//        Deteta se Alguma Moeda Passa por o Coin Acceptor (coinDetector) e Sai do Loop
//        Se Algum dos butões for Pressionado vai Correr uma Custom Function e Voltar ao Início
        
        if ((currentMillis - prevCoinMillis >= 50) && (digitalRead(coinDetector) == HIGH)) {
//            Em Caso Afirmativo, Adiciona +0.5€ (Valor da Moeda) à Banca
            banca += moeda;
            
            delay(250);
            
            break;
        }
        
//        Deteta se o Botão de Administrador Foi Pressionado
        
        if (digitalRead(buttonMoney) == LOW) {

            lcd.clear();
            
            lcd.setCursor(0, 0);
            lcd.print("Ver Stock : A");

            lcd.setCursor(0, 1);
            lcd.print("Alterar Stock : B");

            lcd.setCursor(0, 2);
            lcd.print("Retirar Dinheiro : C");

            lcd.setCursor(0, 3);
            lcd.print("Voltar : D");

            Serial.println("Ver Stock : A");
            Serial.println("Alterar Stock : B");
            Serial.println("Retirar Dinheiro : C");
            Serial.println("Voltar : D \n");

            while(true) {     
                
                customKey = customKeypad.getKey();  
                
//                Ver Stock
                    
                if (customKey == 'A') {

                    stockatual();
                    
                    delay(3000);

                    paragrafo();

                    goto opcoes;
                }
                
//                Alterar Stock
                
                if (customKey == 'B') {
                    
                    stock();
                    
                    Serial.println("");
                    
                    loop();
                }
                
//                Retirar Dinheiro
                
                if (customKey == 'C') {

                    lcd.clear();

                    lcd.setCursor(0,0);
                    lcd.print("Introduza a Password");

                    Serial.println("Introduza a Password:");

                    kpd:

                    passKey = passKeypad.getKey(); 
                    
//                    Escreve a Password no LCD / Serial Monitor

                    if (passKey){
                        Data[data_count] = passKey; 
                        lcd.setCursor(data_count,2);
                        lcd.print(Data[data_count]);
                        Serial.print(Data[data_count]);
                        data_count++; 
                    }
                    
//                    Confirma se Está Correta ou Incorreta
                    
                    if(data_count == Password_Length-1){
                        lcd.clear();
                        Serial.println("");
                        
//                        Correta

                        if(!strcmp(Data, Master)){
                            lcd.print("Correta");
                            
                            Serial.println("Correta \n");
                            
                            abrir();
                            
                            delay(2000);
                            
                            clearData();
                            
                            lcd.clear();
                            
                            lcd.setCursor(0,0);
                            lcd.print("Carregue novamente");
                            
                            lcd.setCursor(0,1);
                            lcd.print("no botao para fechar");
                            
                            lcd.setCursor(0,2);
                            lcd.print("a porta");
                            
                            Serial.println("Carregue novamente no botao para fechar a porta \n");
                            
                            while (true) {
                                if (digitalRead(buttonMoney) == LOW){
                                    
                                    fechar();
                                    
                                    delay(1000);
                                    
                                    goto opcoes;
                                }
                            }
                        }
                        
//                        Incorreta
                        
                        else{
                            lcd.print("Incorreta");
                            Serial.println("");
                            Serial.println("Incorreta \n");
                            delay(2000);
                            clearData();
                            goto opcoes;
                        }
                    }
                    goto kpd; 
                }
                
//                Voltar
                
                if (customKey == 'D'){
                    goto opcoes;
                }
            }
        }
        
//        Preço Vermelho
        
        if (digitalRead(buttonRed) == LOW) {
            
            lcd.clear();
            
            lcd.setCursor(0, 0);
            lcd.print("Preco: ");
            lcd.print(preco_red);
            lcd.print((char)0);
                
            Serial.print("Preco: ");
            Serial.print(preco_red);
            Serial.println(" € \n");
            
            aviso();
            
            delay(2500);
            
            goto opcoes;
        }
        
//        Preço Azul
        
        if (digitalRead(buttonBlue) == LOW) {
            
            lcd.clear();
            
            lcd.setCursor(0, 0);
            lcd.print("Preco: ");
            lcd.print(preco_blue);
            lcd.print((char)0);
            
            Serial.print("Preco: ");
            Serial.print(preco_blue);
            Serial.println(" € \n");
            
            aviso();
            
            delay(2500);
            
            goto opcoes;
        }
        
//        Preço Amarelo
        
        if (digitalRead(buttonYellow) == LOW) {
            
            lcd.clear();
            
            lcd.setCursor(0, 0);
            lcd.print("Preco: ");
            lcd.print(preco_yellow);
            lcd.print((char)0);
                
            Serial.print("Preco: ");
            Serial.print(preco_yellow);
            Serial.println(" € \n");
            
            aviso();
            
            delay(2500);
            
            goto opcoes;
        }
        
//        Preço Verde
        
        if (digitalRead(buttonGreen) == LOW) {
            
            lcd.clear();
            
            lcd.setCursor(0, 0);
            lcd.print("Preco: ");
            lcd.print(preco_green);
            lcd.print((char)0);
                
            Serial.print("Preco: ");
            Serial.print(preco_green);
            Serial.println(" € \n");
            
            aviso();
            
            delay(2500);
            
            goto opcoes;
        }
    }
    
    delay(100);

//    Label para "Goto" Statement
    
    product:

    lcd.clear();
    
    lcd.setCursor(1, 0);
    lcd.print("Saldo Atual = ");
    lcd.print(banca);
    lcd.print((char)0);
    
    lcd.setCursor(1, 1);
    lcd.print("Escolha um Produto");
    
    lcd.setCursor(5, 2);
    lcd.print("A  B  C  D");
    
    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");
    
    Serial.print("Saldo Atual = ");
    Serial.print(banca);
    Serial.println(" €");
    Serial.println("Escolha um Produto");
    Serial.println("A  B  C  D");
    Serial.println("---Venduino--- \n");
    
    currentMillis = millis();

    while (true) {
        if ((currentMillis - prevCoinMillis >= 50) && (digitalRead(coinDetector) == HIGH)) {
//            Em Caso Afirmativo, Adiciona +0.5€ (Valor da Moeda) à Banca
            banca += moeda;
            
            delay(250);
            
            goto product;
        }
        
        if (digitalRead(buttonRed) == LOW) {
            if (red == 0) {            
                unavailable();   
                goto product;
            }
            
            if (banca < preco_red) {
                saldo();
                goto product;
            }
            
            producttype = 1;
            deliver1();
            
            banca -= preco_red;
            red--;
            
            break;
        }
        
        if (digitalRead(buttonBlue) == LOW) {
            if (blue == 0) {
                unavailable();
                goto product;
            }
            
            if (banca < preco_blue) {
                saldo();
                goto product;
            }
            
            producttype = 2;
            deliver2();
            
            banca -= preco_blue;
            blue--;
            
            break;
        }
        
        if (digitalRead(buttonYellow) == LOW) {
            if (yellow == 0) {
                unavailable();
                goto product;
            }
            
            if (banca < preco_yellow) {
                saldo();
                goto product;
            }
            
            producttype = 3;
            deliver3();
            
            banca -= preco_yellow;
            yellow--;
            
            break;
        }
        
        if (digitalRead(buttonGreen) == LOW) {
            if (green == 0) {
                unavailable();
                goto product;
            }
            
            if (banca < preco_green) {   
                saldo();
                goto product;
            }
            
            producttype = 4;
            deliver4();
            
            banca -= preco_green;
            green--;
            
            break;
        }
    }    
    
    delay(2000);
    
    lcd.clear();
    
    lcd.setCursor(1, 0);
    lcd.print("Produto Entregue!!");
    
    Serial.println("");
    Serial.println("Produto Entregue!! \n");
    
    Serial.println("");
    Serial.println("A Máquina Não Dá Troco \n");
    
    lcd.setCursor(4, 2);
    lcd.print("Saldo = ");
    
    if (banca != 0) {
        sld = true;
}
    
//    Função para Fazer uma Contagem Decrescente da Banca, do Valor Atual da Banca até 0€
    
    for (banca; banca >= 0; banca = banca - 0.1) { 
        lcd.setCursor(12,2);
        lcd.print(banca);
        lcd.print((char)0);
        Serial.print("Saldo = ");
        Serial.print(banca);
        Serial.println(" €");
        delay(300);
    }
    
    if (sld == true) {
        lcd.setCursor(4, 2);
        lcd.print("Saldo = 0.00 ");
        lcd.print((char)0);
        Serial.println("Saldo = 0.00 €");
    }
    
    Serial.println("");
    
    lcd.setCursor(3, 3);
    lcd.print("Volte Sempre!!!");
    
    Serial.print("Volte Sempre!!!");
    
    delay(2000);
    
//    Força o Programa a Voltar ao Início
    
    loop();
    
}


// == Custom Functions ==============================

//Função para Alterar Stock

void stock() {
        
//    Define o Número de Produtos do Primeiro Servo
    
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Unidades do Produto");

    lcd.setCursor(0, 1);
    lcd.print("--> 1");

    lcd.setCursor(3, 2);
    lcd.print("A-0 B-1 C-2 D-3");

    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");
    
    Serial.println("Unidades do Produto 1");
    Serial.println("A-0 B-1 C-2 D-3");
    Serial.println("---Venduino---");
    Serial.println("By Tomas Lopes \n");
    
    while (true) {
//        Botão Vermelho "Não Tem Itens"; Botão Azul "Tem 1 Item"; Botão Amarelo "Tem 2 Itens"; Botão Verde "Tem 3 Itens"
        if (digitalRead(buttonRed) == LOW) {
            red = 0;
            break;
        }
        if (digitalRead(buttonBlue) == LOW) {
            red = 1;
            break;
        }
        if (digitalRead(buttonYellow) == LOW) {
            red = 2;
            break;
        }
        if (digitalRead(buttonGreen) == LOW) {
            red = 3;
            break;
        }
    }
    
    Serial.print("Produto 1: ");
    Serial.print(red);
    Serial.println(" unid.");
    Serial.println("");
    Serial.println("--------------------- \n");
    
    delay(1000);
    
//    Define o Número de Produtos do Segundo Servo
    
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Unidades do Produto");

    lcd.setCursor(0, 1);
    lcd.print("--> 2");

    lcd.setCursor(3, 2);
    lcd.print("A-0 B-1 C-2 D-3");

    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");
    
    Serial.println("Unidades do Produto 2");
    Serial.println("A-0 B-1 C-2 D-3");
    Serial.println("---Venduino---");
    Serial.println("By Tomas Lopes \n");

    while (true) {
//        Botão Vermelho "Não Tem Itens"; Botão Azul "Tem 1 Item"; Botão Amarelo "Tem 2 Itens"; Botão Verde "Tem 3 Itens"
        if (digitalRead(buttonRed) == LOW) {
            blue = 0;
            break;
        }
        if (digitalRead(buttonBlue) == LOW) {
            blue = 1;
            break;
        }
        if (digitalRead(buttonYellow) == LOW) {
            blue = 2;
            break;
        }
        if (digitalRead(buttonGreen) == LOW) {
            blue = 3;
            break;
        }
    }
    
    Serial.print("Produto 2: ");
    Serial.print(blue);
    Serial.println(" unid.");
    Serial.println("");
    Serial.println("--------------------- \n");
    
    delay(1000);
    
//    Define o Número de Produtos do Terceiro Servo
    
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Unidades do Produto");

    lcd.setCursor(0, 1);
    lcd.print("--> 3");

    lcd.setCursor(3, 2);
    lcd.print("A-0 B-1 C-2 D-3");

    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");
    
    Serial.println("Unidades do Produto 3");
    Serial.println("A-0 B-1 C-2 D-3");
    Serial.println("---Venduino---");
    Serial.println("By Tomas Lopes \n");
        
    while (true) {
//        Botão Vermelho "Não Tem Itens"; Botão Azul "Tem 1 Item"; Botão Amarelo "Tem 2 Itens"; Botão Verde "Tem 3 Itens"
        if (digitalRead(buttonRed) == LOW) {
            yellow = 0;
            break;
        }
        if (digitalRead(buttonBlue) == LOW) {
            yellow = 1;
            break;
        }
        if (digitalRead(buttonYellow) == LOW) {
            yellow = 2;
            break;
        }
        if (digitalRead(buttonGreen) == LOW) {
            yellow = 3;
            break;
        }
    }
    
    Serial.print("Produto 3: ");
    Serial.print(yellow);
    Serial.println(" unid.");
    Serial.println("");
    Serial.println("--------------------- \n");
    
    delay(1000);

//    Define o Número de Produtos do Quarto Servo

    lcd.setCursor(0, 0);
    lcd.print("Unidades do Produto");

    lcd.setCursor(0, 1);
    lcd.print("--> 4");

    lcd.setCursor(3, 2);
    lcd.print("A-0 B-1 C-2 D-3");

    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");
    
    Serial.println("Unidades do Produto 4");
    Serial.println("A-0 B-1 C-2 D-3");
    Serial.println("---Venduino---");
    Serial.println("By Tomas Lopes \n");
        
    while (true) {
//        Botão Vermelho "Não Tem Itens"; Botão Azul "Tem 1 Item"; Botão Amarelo "Tem 2 Itens"; Botão Verde "Tem 3 Itens"
        if (digitalRead(buttonRed) == LOW) {
            green = 0;
            break;
        }
        if (digitalRead(buttonBlue) == LOW) {
            green = 1;
            break;
        }
        if (digitalRead(buttonYellow) == LOW) {
            green = 2;
            break;
        }
        if (digitalRead(buttonGreen) == LOW) {
            green = 3;
            break;
        }
    }
    
    Serial.print("Produto 4: ");
    Serial.print(green);
    Serial.println(" unid.");
    
    delay(1000);
}

//Função para Mostrar o Stock Atual

void stockatual() {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Produto 1: ");
    lcd.print(red);
    lcd.print(" unid.");

    lcd.setCursor(0, 1);
    lcd.print("Produto 2: ");
    lcd.print(blue);
    lcd.print(" unid.");

    lcd.setCursor(0, 2);
    lcd.print("Produto 3: ");
    lcd.print(yellow);
    lcd.print(" unid.");

    lcd.setCursor(0, 3);
    lcd.print("Produto 4: ");
    lcd.print(green);
    lcd.print(" unid.");


    Serial.print("Produto 1: ");
    Serial.print(red);
    Serial.println(" unid. \n");

    Serial.print("Produto 2: ");
    Serial.print(blue);
    Serial.println(" unid. \n");

    Serial.print("Produto 3: ");
    Serial.print(yellow);
    Serial.println(" unid. \n");

    Serial.print("Produto 4: ");
    Serial.print(green);
    Serial.println(" unid. \n");
}

//Função para Fazer Girar o Primeiro Servo

void deliver1() {
    entrega();
    servo1.attach(6);
    servo1.writeMicroseconds(1950);
    delay(950);
    servo1.writeMicroseconds(1450);
    delay(10);
    servo1.detach();
}

//Função para Fazer Girar o Segundo Servo

void deliver2() {
    entrega();
    servo2.attach(5);
    servo2.writeMicroseconds(1950);
    delay(950);
    servo2.writeMicroseconds(1450);
    delay(10);
    servo2.detach();
}

//Função para Fazer Girar o Terceiro Servo

void deliver3() {
    entrega();
    servo3.attach(4);
    servo3.writeMicroseconds(1950);
    delay(950);
    servo3.writeMicroseconds(1450);
    delay(10);
    servo3.detach();
}

//Função para Fazer Girar o Quarto Servo

void deliver4() {
    entrega();
    servo4.attach(3);
    servo4.writeMicroseconds(1950);
    delay(950);
    servo4.writeMicroseconds(1450);
    delay(10);
    servo4.detach();
}

//Função para Fazer o Servo da Porta Rodar 180º

void abrir() {
    servo5.attach(7);
    servo5.writeMicroseconds(0);
    delay(500);
    servo5.detach();
}

//Função para Fazer o Servo da Porta Voltar à Posição Original

void fechar() {
    servo5.attach(7);
    servo5.writeMicroseconds(3000);
    delay(500);
    servo5.detach();
}

//Função para Mostrar Mensagem no LCD

void entrega() {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Selecionou Produto ");
    Serial.print("Selecionou Produto ");
    switch (producttype) {
        case 1:
            lcd.print("1");
            Serial.println("1");
            break;
        case 2:
            lcd.print("2");
            Serial.println("2");
            break;
        case 3:
            lcd.print("3");
            Serial.println("3");
            break;
        case 4:
            lcd.print("4");
            Serial.println("4");
            break;
    }
    
    lcd.setCursor(3, 1);
    lcd.print("Entregando....");
  
    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");
    
    Serial.println("Entregado....");
    Serial.println("---Venduino---");
}

//Função para Mostrar Mensagem no LCD

void unavailable() {
    lcd.clear();
  
    lcd.setCursor(0, 1);
    lcd.print("Produto Indisponivel");
  
    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");   
    
    Serial.println("Produto Indisponível");
    Serial.println("---Venduino---");
    Serial.println("");
    
    delay(1000);
}

//Função para Mostrar Mensagem no LCD

void saldo() {
    lcd.clear();
    
    lcd.setCursor(1, 1);
    lcd.print("Saldo Insuficiente");
  
    lcd.setCursor(3, 3);
    lcd.print("---Venduino---");
    
    Serial.println("Saldo Insuficiente");
    Serial.println("---Venduino---");
    Serial.println("");
    
    delay(1000);
}

//Função para Mostrar Mensagem no LCD

void aviso() {
    lcd.setCursor(6, 1);
    lcd.print("AVISO!!!");
    
    lcd.setCursor(2, 2);
    lcd.print("A Maquina Nao Da");
    
    lcd.setCursor(7, 3);
    lcd.print("Troco");
    
    Serial.println("AVISO!!!");
    Serial.println("A Maquina Nao Da Troco");
    Serial.println("");
}

//Função Auxiliar à Password, Serve para Limpar da Memória a Password que o Admin Inseriu

void clearData() {
  while(data_count !=0) {
    Data[data_count--] = 0; //Limpa o Array para Receber Nova Data
  }
  return;
}

//Função para Fazer um Paragrafo Grande no Serial Monitor

void paragrafo() {
    if(parf < 10) {
        Serial.println("");
        parf ++;
        paragrafo();
    }
    parf = 0;
}
