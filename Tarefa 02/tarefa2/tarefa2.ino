////////////////////////////////////
//sensor de Umidade
#include "DHT.h"

#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

int maxHum = 70;
int maxTemp = 30;

DHT dht(DHTPIN, DHTTYPE);
/////////////////////////////////////

//////////////////////////////////////
//sensor de movimento
int sensor = 7;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
//////////////////////////////////////

/////////////////////////////////////
//buzzer config
#include "pitches.h"
#define BUZZER 10
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
///////////////////////////////////////

//buzzerFunction
void playBuzz(){
    //digitalWrite(BUZZER, HIGH);   // turn BUZZER ON
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
    // stop the tone playing:
        noTone(BUZZER);
    }

}


//SETUP
void setup() {
  pinMode(BUZZER, OUTPUT);      // initalize BUZZER as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  dht.begin();
  Serial.begin(9600);        // initialize serial
}

///////////////////////////////////////
//LOOP
void loop(){
  val = digitalRead(sensor);   // read sensor value
 // Serial.println(val);
  if (!val){
    Serial.println("no motion");
        
  }
  if (val == HIGH) {           // check if the sensor is HIGH
    playBuzz();
    if (state == LOW) {
      Serial.println("Motion detected!");
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      //digitalWrite(BUZZER, LOW); // turn BUZZER OFF
      //delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  if(h > maxHum || t > maxTemp) {
      playBuzz();
  } else {
     digitalWrite(BUZZER, LOW); 
  }
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

}
