#include <rgb_lcd.h>
#include <Servo.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define TOUCH 2
#define LED 3
#define LUZ A0

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

int servoPosition = 0;
int sensorBiometrico;
int var = 0; // Variavel de controle para evitar o loop do texto porta aberta
int luz;
int intensidadeLuz;
bool trancado = true;

Servo myServo;
rgb_lcd lcd;


void setup()
{

  Serial.begin(115200);
  myServo.attach(8);

  pinMode(TOUCH, INPUT);
  pinMode (LED, OUTPUT);
  pinMode (LUZ, INPUT);

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.setRGB(255, 0, 0); // Cor Vermelha
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Tranca Fechada");
  lcd.setCursor(0, 1);
  lcd.print(0);

}

void loop()
{


  sensorBiometrico = digitalRead(TOUCH);

  if (sensorBiometrico == 1) {

    lcd.setRGB(250, 200 , 20); // Cor Amarelo
    lcd.clear();

    if (trancado) {
      lcd.print("Abrindo Tranca");
    } else {
      lcd.print("Fechando Tranca");
    }

    lcd.setCursor(0, 1);
    lcd.print(sensorBiometrico);


    if (trancado) {

      trancado = false;
      for (servoPosition = 180; servoPosition >= 0; servoPosition -= 1) {   // Fechamento da Trava
        myServo.write(servoPosition);
        delay(15);
      }

    } else {

      trancado = true;
      for (servoPosition = 0; servoPosition <= 180; servoPosition += 1) {    // Abertura da Trava
        myServo.write(servoPosition);


        delay(15);
      }

    }
  }
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);

  if (!trancado) {                // --------------------------- TRANCA ABERTA -------------------------------
    lcd.setRGB(0, 255, 0);       // Cor Verde
    lcd.print("Tranca Aberta");
  } else {                      // --------------------------- TRANCA FECHADA -------------------------------
    lcd.setRGB(255, 0, 0);     // Cor Vermelha
    lcd.print("Tranca Fechada");
  }
  lcd.setCursor(0, 1);
  lcd.print(sensorBiometrico);
}
