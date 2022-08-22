#define BLYNK_PRINT Serial
#define LED 5
#define LUZ A0

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "RR2Y_nS7yFfj5WmQvudT7TnimkwyqQ7L";

char ssid[] = "REDE SNAKE_2.4Ghz"; 
char pass[] = "3835373839";
// char ssid[] = "MOTO-G7"; 
// char pass[] = "181e71f5b1bf";

int luz;
int intensidadeLuz;
int opcaoBotao;


void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}


void loop()
{
  Blynk.run();

  if (opcaoBotao == 1)
    digitalWrite (LED, HIGH);


  else if (opcaoBotao == 2)
    digitalWrite (LED, LOW);


  else if (opcaoBotao == 3) {
    luz = analogRead (LUZ);
    Serial.println (luz);

    if (luz >= 0 && luz <= 700) {
      intensidadeLuz = map (luz, 0, 700, 0, 255);
      analogWrite (LED, 255 - intensidadeLuz);


    } else
      digitalWrite (LED, LOW);
  }
}


BLYNK_WRITE(V4) {
  switch (param.asInt())
  {
    case 1: {
        opcaoBotao = 1;
        break;

    } case 2: {
        opcaoBotao = 2;
        break;

    } case 3: {
        opcaoBotao = 3;
        break;
      }
  }
}
