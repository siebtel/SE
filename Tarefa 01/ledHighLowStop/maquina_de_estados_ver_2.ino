#define LED 13
#define BUT_LOW 7
#define BUT_HIGH 6

int tempoAnterior = 0;
int tempoAtual = 0; 
int interval = 1000;
int but_high;
int but_low;
enum Estados{led_aceso = 1, led_desligado, 
led_acesoB1, led_acesoB2, 
led_desligadoB1, led_desligadoB2, 
led_desligado_intermediario1, 
led_desligado_intermediario2, 
led_aceso_intermediario1, led_aceso_intermediario2, 
manter};
enum Estados estado = led_aceso;
int led = 1;


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
  case led_aceso:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligado;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //apertaB1
    high = digitalRead(BUT_HIGH);
    if (!high){
      but_high = millis();
      if (interval > 200)
        interval -= 200;
      estado = led_acesoB1;
    }
  //apertaB2
    low = digitalRead(BUT_LOW);
    if (!low){
      but_low = millis();
      if (interval <= 5000)
        interval += 200;
      estado = led_acesoB2;
    }

  break;
  case led_desligado:
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_aceso;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  //apertaB1
    high = digitalRead(BUT_HIGH);
    if (!high){
      but_high = millis();
      if (interval > 200)
        interval -= 200;
      estado = led_acesoB1;
    }
  //apertaB2
    low = digitalRead(BUT_LOW);
    if (!low){
      but_low = millis();
      if (interval <= 5000)
        interval += 200;
      estado = led_acesoB2;
    }

  break;
  case led_acesoB1:
  //passou 500
    low = digitalRead(BUT_LOW);
    if (!low){
      but_low = millis();
    }
    if (but_low - but_high >= 500)
      estado = led_aceso;
  //apertou botao low
    else if(!low && !high){
      estado = manter;
    }
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligado_intermediario1;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }
  break;
  case led_acesoB2:
  //passou 500
    high = digitalRead(BUT_LOW);
    if (!high){
      but_high = millis();
    }
    if (but_high - but_low >= 500)
      estado = led_aceso;
  //apertou botao high
    else if(!low && !high){
      estado = manter;
    }
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_desligado_intermediario2;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }

  break;
  case led_desligadoB1:
  //passou 500
    low = digitalRead(BUT_LOW);
    if (!low){
      but_low = millis();
    }
    if (but_low - but_high >= 500)
      estado = led_desligado;
  //apertou botao low
    else if(!low && !high){
      estado = manter;
    }
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_aceso_intermediario1;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }

  break;
  case led_desligadoB2:
  //passou 500
    high = digitalRead(BUT_HIGH);
    if (!high){
      but_high = millis();
    }
    if (but_high - but_low >= 500)
      estado = led_desligado;
  //apertou botao high
    else if(!low && !high){
      estado = manter;
    }
  //interval
    tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= interval){
      estado = led_aceso_intermediario2;
      led = !led;
      tempoAnterior = tempoAtual;
      digitalWrite(LED, led);
    }

  break;
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
