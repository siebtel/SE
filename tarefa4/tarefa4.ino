unsigned long int meuMillis =0;
void setup() {
  // put your setup code here, to run once:
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;//inicia o contador como zero
  TCCR1B |= (1 << WGM12); //aciona o CTC(clear timer on compare) 
  OCR1A = 15626.5223;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  //conta pra calcular esse valor 
  //[16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1

  TCCR1B |= (1 << CS12) | (1 << CS10); //aciona o prescaler de 1024
  TIMSK1 |= (1<<OCIE1A);   // enable timer compare interrupt
  Serial.begin(9600);
}
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
    meuMillis++;
    //meuMillis /= 1000;
    Serial.println("Meu Millis");
    Serial.println(meuMillis);
    Serial.println("Millis");
    Serial.println(millis());
}
void loop() {
  // put your main code here, to run repeatedly:

}

//https://www.instructables.com/id/Arduino-Timer-Interrupts/
