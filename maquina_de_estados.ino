#define LED 13
#define BUT_LOW 7
#define BUT_HIGH 6

unsigned long previousTime = 0, currentTime = 0, intervalo = 1000, butHigh, butLow;
enum Estados{led_aceso1 = 1, led_desligado1, led_aceso2, led_desligado2, manter};
enum Estados estado = led_aceso1;
int led = 1;
bool highPressed = false, lowPressed = false;

void mudaEstadoHorizontalTransition(int estadoAtual){
  switch (estadoAtual)
  {
  case 1:
    estado = 2;
  break;
  case 2:
    estado = 1;
  break;
  case 3:
    estado = 4;
  break;
  case 4:
    estado = 3;
  break;
  default:
    break;
  }
}

void horizontalTransition(int estadoAtual){
    currentTime = millis();
    if (currentTime - previousTime >= intervalo){
      mudaEstadoHorizontalTransition(estadoAtual);
      led = !led;
      previousTime = currentTime;
      digitalWrite(LED, led);
    }
}
void verticalTransition(int estadoFuturo){
  int high, low;
  high = digitalRead(BUT_HIGH);
  low = digitalRead(BUT_LOW);
  //transicao de solta B1 ou B2
  if (high) highPressed = false;
  if (low) lowPressed = false;
  //transicao de pressionaB1 ou pressionaB2
  if (!high && !highPressed){
    highPressed = !highPressed;
    butHigh = millis();
    if (intervalo > 200)
      intervalo -= 200;
    estado = estadoFuturo;
  }
  if (!low && !lowPressed){
    lowPressed = !lowPressed;
    butLow = millis();
    if (intervalo < 3000)
      intervalo += 200;
    estado = estadoFuturo;
  }
  Serial.print(high);
  Serial.print(low);
  Serial.print(highPressed);
  Serial.println(lowPressed);
}

void finalTransition(int possivelEstadoFuturo){
  int high, low;
  unsigned long time2button1 = abs(butHigh - butLow);
  unsigned long time2button2 = abs(butLow - butHigh);
  high = digitalRead(BUT_HIGH);
  low = digitalRead(BUT_LOW);
  Serial.print(high);
  Serial.print(low);
  Serial.print(highPressed);
  Serial.print(lowPressed);
  Serial.print(butHigh);
  Serial.println(butLow);
  if ((time2button1 < 500) || time2button2 < 500){
    estado = 5;
  }
  else{
    estado = possivelEstadoFuturo;
  }
  
}

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUT_LOW, INPUT);
  pinMode(BUT_HIGH, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(estado);
  //delay(200);
  int high, low;
  switch (estado){
  case led_aceso1:
    horizontalTransition(led_aceso1);
    verticalTransition(3);
    break;
  case led_desligado1:
    horizontalTransition(led_desligado1);
    verticalTransition(4);
    break;
  case led_aceso2:
    horizontalTransition(led_aceso2);
    finalTransition(1);
    break;
  case led_desligado2:
    horizontalTransition(led_desligado2);
    finalTransition(2);
    break;
  default:
    break;
  }
}
