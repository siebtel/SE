#define LED 13
#define BUT_LOW 7
#define BUT_HIGH 6

int tempoAnterior = 0, tempoAtual = 0, interval = 1000, but_high, but_low;
enum Estados{led_aceso = 1, led_desligado, 
led_acesoB1, led_acesoB2, 
led_desligadoB1, led_desligadoB2, 
led_desligado_intermediario1, 
led_desligado_intermediario2, 
led_aceso_intermediario1, led_aceso_intermediario2, 
manter};
enum Estados estado = led_aceso;
int led = 1;
bool highPressed = false, lowPressed = false;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUT_LOW, INPUT);
  pinMode(BUT_HIGH, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int high, low;
  Serial.println(estado);
  //delay(200);
  switch (estado){
//estado 1
  case led_aceso:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligado;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //transicao de solta B1 ou B2
  if (!high) highPressed = false;
  if (!low) lowPressed = false;
  //apertaB1
    high = digitalRead(BUT_HIGH);
    if (!high && !highPressed){
      highPressed = !highPressed;
      but_high = millis();
      if (interval > 200)
        interval -= 200;
      estado = led_acesoB1;
    }
  //apertaB2
    low = digitalRead(BUT_LOW);
    if (!low && !lowPressed){
      lowPressed = !lowPressed;
      but_low = millis();
      if (interval <= 5000)
        interval += 200;
      estado = led_acesoB2;
    }

  break;
//estado 2
  case led_desligado:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_aceso;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //transicao de solta B1 ou B2
  if (!high) highPressed = false;
  if (!low) lowPressed = false;
  //apertaB1
    high = digitalRead(BUT_HIGH);
    if (!high && !highPressed){
      highPressed = !highPressed;
      but_high = millis();
      if (interval > 200)
        interval -= 200;
      estado = led_desligadoB1;
    }
  //apertaB2
    low = digitalRead(BUT_LOW);
    if (!low && !lowPressed){
      lowPressed = !lowPressed;
      but_low = millis();
      if (interval <= 5000)
        interval += 200;
      estado = led_desligadoB2;
    }

  break;
//estado 3
  case led_acesoB1:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligado_intermediario1;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //passou 500
    high = digitalRead(BUT_HIGH);
    low = digitalRead(BUT_LOW);
    if (!low){
      but_low = millis();
    }
    if (abs(but_low - but_high) >= 500){
      estado = led_aceso;
      Serial.println("passou");
      //delay(500);
    }
  //apertou botao low
    else if(!low && !high){
      estado = manter;
    }

  break;
//estado 4
  case led_acesoB2:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligado_intermediario2;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //passou 500
    high = digitalRead(BUT_HIGH);
    low = digitalRead(BUT_LOW);
    if (!high){
      but_high = millis();
    }
    if (abs(but_high - but_low) >= 500){
      estado = led_aceso;
    }
  //apertou botao high
    else if(!low && !high){
      estado = manter;
    }
  break;
//estado 5
  case led_desligadoB1:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_aceso_intermediario1;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //passou 500
    high = digitalRead(BUT_HIGH);
    low = digitalRead(BUT_LOW);
    if (!low){
      but_low = millis();
    }
    if (abs(but_low - but_high) >= 500)
      estado = led_desligado;
  //apertou botao low
    else if(!low && !high){
      estado = manter;
    }
  break;
//estado 6
  case led_desligadoB2:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_aceso_intermediario2;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //passou 500
    high = digitalRead(BUT_HIGH);
    low = digitalRead(BUT_LOW);
    if (!high){
      but_high = millis();
    }
    if (abs(but_high - but_low) >= 500)
      estado = led_desligado;
  //apertou botao high
    else if(!low && !high){
      estado = manter;
    }
  break;
//estado 7
  case led_desligado_intermediario1:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_acesoB1;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  break;
//estado 8
  case led_desligado_intermediario2:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_acesoB2;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  break;
//estado 9
  case led_aceso_intermediario1:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligadoB1;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  break;
//estado 10
  case led_aceso_intermediario2:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligadoB2;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  break;
  default:
    break;
  }
}