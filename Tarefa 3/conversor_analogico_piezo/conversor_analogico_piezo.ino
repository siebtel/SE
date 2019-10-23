#define pinLed 13
#define sensor 0

int val = 0;      // Initializing the variable for the voltage value

void setup() {
  ADMUX = 0;
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1<<ADEN);
  Serial.begin(9600);  // Initializing the serial port at 9600 baud
}

void loop() {
//  val = analogRead(sensor);  // Read the voltage
  ADCSRA |= (1 << ADSC);
  while(ADCSRA & (1 << ADSC));

  int v = ADCL;
  v = (ADCH << 8) + v;
  
  if (v){
    Serial.println(v, DEC); // Print the voltage to the terminal
    delay(500);
  }
  Serial.println(v);
  if(v) {
    digitalWrite(pinLed,HIGH);
  } else {
    digitalWrite(pinLed,LOW);
  }
}
