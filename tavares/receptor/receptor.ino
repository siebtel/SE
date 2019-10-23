#include <SoftwareSerial.h> // Inclui Biblioteca
SoftwareSerial mySerial(2, 3);       // Simula RX e TX em outras portas 
const int ledPin = 13;               // Define que ledPin estará na porta 13
void setup() {
  Serial.begin(9600);                // Taxa de transferência da Serial
  mySerial.begin(9600);              // Taxa de transferência do HC12
  pinMode(ledPin, OUTPUT);           // Define ledPin como saída
}
void loop() {
  if (mySerial.available() > 1) {    // Se o sinal de mySerial for maior que 1
    int input = mySerial.read();     // input será igual ao valor de mySerial
    Serial.println(input);           // Escreve na serial o valor de input
  if (input != 1) {                  // O valor de input for diferente de 1
      digitalWrite(ledPin, HIGH);    // Led acende 
      delay(100);                    // 100 milissegundos 
    }   
  else {                             // Se for igual a 1 
      digitalWrite(ledPin, LOW);     // Led desliga 
      delay(100);                    // 100 milissegundos 
    }
  }
}