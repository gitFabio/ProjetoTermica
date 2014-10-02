/*
Desenvolver uma termica que ser possivel atraves de botoes selecionar
a temperatura maxima a ser atingida pela agua, e quando a temperatura
maxima for atingida devera ter um aviso sonoro e um visual no
monitor lcd (16,2) informando que a agua chegou na temperatura
selecionada pelo usuario, para encerrar o aviso sera necessario o usuario
pressionar os 2 botoes, e caso a termica continue ligado na luz ela ficara
monitorando e controlando a temperatura da agua.

Materiais necessarios:

Display LCD 16,2;
3 botoes;
1 buzzer;
1 potenciometro


OBS:
Temepratura minima 15ºC
Temperatura maxima 200ºC

OBS:
Para deslifgar o alarme eh necessario que seja pressionado os botoes de aumentar e
diminuir temperatura simultaneamente ateh que desligado o alarme.
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define botaoAumentarTemperatura 6
#define botaoDiminuirTemperatura 7
#define botaoLigar 8
#define buzzer 9
#define tmpPressionaBotao 300
#define sensorTemperatura 0

int temperatura = 40;

void setup() {
  pinMode(botaoAumentarTemperatura, INPUT);
  pinMode(botaoDiminuirTemperatura, INPUT);
  pinMode(botaoLigar, INPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Select Temp.");
  lcd.setCursor(0, 1);
  lcd.print ("Temp ");
  lcd.print(temperatura);
  lcd.print("C");

  Serial.begin(9600);
}

void loop() {

  //Aumenta temperatura
  if (digitalRead(botaoAumentarTemperatura)) {
    
    //Caso tenha sido desligado pelo botao entao e for religado entao
    //entra nesse if econfigura novamente o LCD
    if (temperatura == 14) {
      temperatura = 40;
      lcd.setCursor(0, 0);
      lcd.print("Select Temp.");
      lcd.setCursor(0, 1);
      lcd.print ("Temp ");
      lcd.print(temperatura);
      lcd.print("C");
    }

    temperatura++;
    regulaTemperatura();
    delay(tmpPressionaBotao);
  }

  //Diminui temperatura
  if (digitalRead(botaoDiminuirTemperatura)) {
    if (temperatura > 15) {
      temperatura--;
    }
    regulaTemperatura();
    delay(tmpPressionaBotao);
  }

  //Liga
  if (digitalRead(botaoLigar)) {
    aquecer();
    delay(tmpPressionaBotao);
  }
}


void regulaTemperatura() {
  limpaLCD(5, 10, 1);
  lcd.print(temperatura);
  lcd.print("C");
}

void limpaLCD(int ci, int cf, int l) {
  for (int i = ci; i <= cf; i++) {
    lcd.setCursor(i, l);
    lcd.print(" ");
  }
  lcd.setCursor(ci, l);
}

void aquecer() {
  while (true) {
    if (analogRead(sensorTemperatura) < temperatura) {
      Serial.println("Aquecendo");

    } else {
      alarmeVisual();


      if (digitalRead(botaoAumentarTemperatura) && digitalRead(botaoDiminuirTemperatura)) {
        Serial.println("Alarme desligado indo para a funacao para controle de temperatura");
        limpaLCD(0, 12, 0);
        lcd.print("Manter Temp.");
      }
    }
  }
}

void manterTemperatura() {
  while (true) {
    if (analogRead(sensorTemperatura) < temperatura - 10) {
      Serial.println("Aquecendo");
    }

    if (analogRead(sensorTemperatura) > temperatura + 2) {
      Serial.println("Desligando");
    }

    if (digitalRead(botaoLigar)) {
      limpaLCD(0, 12, 1);
      limpaLCD(0, 12, 0);
      lcd.print("Desligado");
      temperatura = 14;
      break;
    }
  }
}

void alarmeVisual() {
  char mensagem[] = "AQUECIDO!!!";
  limpaLCD(0, 12, 0);

  //Escrevendo a mensagem no display
  for (int i = 0; i < 11; i++) {
    lcd.setCursor(i, 0);
    lcd.print(mensagem[i]);
    alarmeSonoro();
  }

  //Pisca a Mensagem no display
  limpaLCD(0, 12, 0);
  alarmeSonoro();
  delay(200);
  lcd.print(mensagem);
  alarmeSonoro();
  delay(300);
}

void alarmeSonoro() {
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}
