/*
Projeto termica com hora, despertador, temperatura, entradaWeb

*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define botaoDefinir 8
#define botaoMais 6
#define botaoMenos 10
#define tempoPressionarBotao 300

boolean confHora = false;
boolean confDepertador = false;
boolean confTemperatura = false;
boolean ligadoAquecedor = false;
int operacao = 0;

int hora = -1;
int minuto = -1;

int horaD = -1;
int minutoD = -1;

int temperatura = -1;

boolean debug = true;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);


  Serial.begin(9600);
}

void loop() {

  if (operacao > 3) {
    operacao = 0;
  }


  switch (operacao) {
    case 0:
      recemLigado();
      operacao += 1;
      break;
    case 1:
      configurarHora();
      operacao += 1;
      break;
    case 2:
      configurarDespertador();
      operacao += 1;
      break;
    case 3:
      configurarTemperatura();
      operacao += 1;
      break;
  }

  if (confHora && confDepertador && confTemperatura) {
    //Iniciar a contagem do tempo
    Serial.println("Iniciando a contagem do tempo");
    contagemTempo();
  }


}

boolean dadosWeb() {
  String horaA = "", minutoA = "", temperaturaPHP = "", horaDPHP = "", minutoDPHP = "";
  char entrada;

  if (Serial.available() > 0) {
    Serial.println("Aqui dados web2");
    entrada = (char) Serial.read();

    if (entrada == '#') {
      Serial.println("Pegando hora atual");
      if (horaA != "") {
        horaA = "";
      }
      hora = obtemHoraPHPA(horaA, entrada);
    }

    if (entrada == '%') {
      Serial.println("Pegando minuto atual");
      if (minutoA != "") {
        minutoA = "";
      }
      minuto = obtemMinutoPHPA(minutoA, entrada);

    }

    if (entrada == '@') {
      Serial.println("Pegando Temperatura");
      if (temperaturaPHP != "") {
        temperaturaPHP = "";
      }
      temperatura = obtemTemperaturaPHP(temperaturaPHP, entrada);
    }

    if (entrada == '!') {
      Serial.println("Pegando hora despertar");
      if (horaDPHP != "") {
        horaDPHP = "";
      }
      horaD = obtemHoraPHPD(horaDPHP, entrada);
    }

    if (entrada == '=') {
      Serial.println("Pegando minuto despertar");
      if (minutoDPHP != "") {
        minutoDPHP = "";
      }
      minutoD = obtemMinutoPHPD(minutoDPHP, entrada);
    }
  }



  if (hora != -1 && minuto != -1 && temperatura != -1 && horaD != -1 && minutoD != -1) {
    confHora = true;
    confDepertador = true;
    confTemperatura = true;
    operacao = 4;
    Serial.println(hora);
    Serial.println(minuto);
    Serial.println(temperatura);
    Serial.println(horaD);
    Serial.println(minutoD);
    return true;
  }

  return false;
}


int obtemMinutoPHPD(String minutoD, char entrada) {
  while (true) {
    if (Serial.available() > 0) {
      entrada = (char) Serial.read();
      if (entrada != '=') {
        minutoD += entrada;
      } else {
        break;
      }
    }
  }
  Serial.print(minutoD);
  Serial.println(" m");
  return minutoD.toInt();
}

int obtemHoraPHPD(String horaD, char entrada) {
  while (true) {
    if (Serial.available() > 0) {
      entrada = (char) Serial.read();
      if (entrada != '!') {
        horaD += entrada;
      } else {
        break;
      }
    }
  }
  Serial.print(horaD);
  Serial.println(" h");
  return horaD.toInt();
}

int obtemTemperaturaPHP(String temperatura, char entrada) {
  while (true) {
    if (Serial.available() > 0) {
      entrada = (char) Serial.read();
      if (entrada != '@') {
        temperatura += entrada;
      } else {
        break;
      }
    }
  }
  Serial.print(temperatura);
  Serial.println(" C");
  return temperatura.toInt();
}

int obtemMinutoPHPA(String minutoA, char entrada) {
  while (true) {
    if (Serial.available() > 0) {
      entrada = (char) Serial.read();
      if (entrada != '%') {
        minutoA += entrada;
      } else {
        break;
      }
    }
  }
  Serial.print(minutoA);
  Serial.println(" m");
  return minutoA.toInt();
}

int obtemHoraPHPA(String horaA, char entrada) {
  while (true) {
    if (Serial.available() > 0) {
      entrada = (char) Serial.read();
      if (entrada != '#') {
        horaA += entrada;
      } else {
        break;
      }
    }
  }
  Serial.print(horaA);
  Serial.println(" h");
  return horaA.toInt();
}

/**
Funcao usada para exibir hora e temperatura atual do sensor na primeira linha
e na segunda linha o horario de ligar e a temperatura que devera esquentar a agua
*/
void exibirHoraLCD(int h, int m, int s, int temp, int hD, int mD) {
  //============================== Primeira linha do display =========================//
  if (s % 2 == 0) {
    Serial.println("Aqui1");
    escreverLCD(":", 2, 2, 0);
    escreverLCD(":", 5, 5, 0);
  } else {
    Serial.println("Aqui2");
    escreverLCD(" ", 2, 2, 0);
    escreverLCD(" ", 5, 5, 0);
  }

  if (h < 10) {
    escreverLCD("0", 0, 0, 0);
    escreverLCD(String(h), 1, 1, 0);
  } else {
    escreverLCD(String(h), 0, 1, 0);
  }

  if (m < 10) {
    escreverLCD("0", 3, 3, 0);
    escreverLCD(String(m), 4, 4, 0);

  } else {
    escreverLCD(String(m), 3, 4, 0);
  }

  if (s < 10) {
    escreverLCD("0", 6, 6, 0);
    escreverLCD(String(s), 7, 7, 0);
  } else {
    escreverLCD(String(s), 6, 7, 0);
  }

  escreverLCD(" ", 8, 8, 0);
  //Temperatura atual do sensor
  escreverLCD(" ", 9, 14, 0);
  //
  escreverLCD("C", 15, 15, 0);


  //============================== Primeira linha do display =========================//

  //============================= Segunda Linha do Display ===========================//

  escreverLCD(":", 2, 2, 1);
  escreverLCD(":", 5, 5, 1);


  if (hD < 10) {
    escreverLCD("0", 0, 0, 1);
    escreverLCD(String(hD), 1, 1, 1);
  } else {
    escreverLCD(String(hD), 0, 1, 1);
  }

  if (mD < 10) {
    escreverLCD("0", 3, 3, 1);
    escreverLCD(String(mD), 4, 4, 1);
  } else {
    escreverLCD(String(mD), 3, 4, 1);
  }

  escreverLCD("00", 6, 7, 1);

  escreverLCD(" | ", 8, 10, 1);
  escreverLCD(String(temp), 11, 14, 1);
  escreverLCD("C", 15, 15, 1);
  //============================= Segunda Linha do Display ===========================//

}

/*
Contagem da hora
*/
void contagemTempo() {
  int segundo = 0, ant = 0;
  int h = hora;
  int m = minuto;
  unsigned long time = 0;
  //Limpando resto do display
  escreverLCD(" ", 8, 15, 1);

  while (true) {
    //Segundos
    if (millis() - time < 0) {
      time = millis();
    } else {
      segundo = int((millis() - time) / 1000);

    }
    if (ant != segundo) {
      ant = segundo;

      if (segundo > 59) {
        m++;
        segundo = 0;
        time = millis();
      }

      if (m > 59) {
        m = 0;
        h++;
      }

      if (h > 23) {
        h = 0;
      }

      exibirHoraLCD(h, m, segundo, temperatura, horaD, minutoD);
    }
    if (h == horaD && m == minutoD) {
      Serial.println("Iniciando o aquecimento da agura");
      ligadoAquecedor = true;
    }

    if (ligadoAquecedor) {
      aquecendo();
    }
  }
}

/**
*/
void aquecendo() {
  Serial.println("Aquecendo");


}

void recemLigado() {
  escreverLCD("** ** **** ** **", 0, 16, 0);
  escreverLCD("** ** **** ** **", 0, 16, 1);
  while (true) {
    if (dadosWeb()) {
      break;
    }
    if (digitalRead(botaoDefinir) == HIGH) {
      delay(tempoPressionarBotao);
      break;
    }
  }
}

void configurarHora() {
  escreverLCD("Conf Relogio", 0, 16, 0);
  escreverLCD("", 0, 16, 1);
  while (true) {
    hora = obtemHora();
    minuto = obtemMinuto();
    confHora = true;
    break;
  }
}

int obtemMinuto() {
  int m = 0;
  escreverLCD("Minuto: ", 0, 8, 1);
  escreverLCD(String(m), 8, 11, 1);

  while (true) {
    if (digitalRead(botaoMais) == HIGH) {
      m += 1;
      if (m > 59) {
        m = 0;
      }
      escreverLCD(String(m), 8, 11, 1);
      delay(tempoPressionarBotao);
    }

    if (digitalRead(botaoMenos) == HIGH) {
      m -= 1;
      if (m < 0) {
        m = 59;
      }
      escreverLCD(String(m), 8, 11, 1);
      delay(tempoPressionarBotao);
    }

    if (digitalRead(botaoDefinir) == HIGH) {
      delay(tempoPressionarBotao);
      break;
    }
  }
  return m;
}

int obtemHora() {
  int h = 0;
  escreverLCD("Hora: ", 0, 6, 1);
  escreverLCD(String(h), 6, 10, 1);
  while (true) {

    if (digitalRead(botaoMais) == HIGH) {
      h += 1;
      if (h > 23) {
        h = 0;
      }
      escreverLCD(String(h), 6, 10, 1);
      delay(tempoPressionarBotao);
    }

    if (digitalRead(botaoMenos) == HIGH) {
      h -= 1;
      if (h < 0) {
        h = 23;
      }
      escreverLCD(String(h), 6, 10, 1);
      delay(tempoPressionarBotao);
    }

    if (digitalRead(botaoDefinir) == HIGH) {
      delay(tempoPressionarBotao);
      break;
    }
  }
  return h;
}

void configurarDespertador() {
  escreverLCD("Conf Despert", 0, 16, 0);
  escreverLCD("", 0, 16, 1);
  while (true) {
    horaD = obtemHora();
    minutoD = obtemMinuto();
    confDepertador = true;
    break;
  }
}

int obtemTemperatura() {
  int temp = 60;
  while (true) {
    if (digitalRead(botaoMais) == HIGH) {
      if (temp < 200) {
        temp += 1;
      }
      escreverLCD(String(temp), 0, 5, 1);
      escreverLCD("Celcius", 5, 16, 1);
      delay(tempoPressionarBotao);
    }

    if (digitalRead(botaoMenos) == HIGH) {
      if (temp > 0) {
        temp -= 1;
      }
      escreverLCD(String(temp), 0, 5, 1);
      escreverLCD("Celcius", 5, 16, 1);
      delay(tempoPressionarBotao);
    }

    if (digitalRead(botaoDefinir) == HIGH) {
      delay(tempoPressionarBotao);
      break;
    }

  }
  return temp;
}

void configurarTemperatura() {
  escreverLCD("Conf Temperatura", 0, 16, 0);
  escreverLCD("60", 0, 5, 1);
  escreverLCD("Celcius", 5, 16, 1);
  while (true) {
    temperatura = obtemTemperatura();
    confTemperatura = true;
    break;
  }
}


void escreverLCD(String text, int inicio, int fim, int linha) {
  if (debug) {
    Serial.print (text.length());
    Serial.print(" -> ");
    Serial.println(fim - inicio);

    Serial.print("Posicao ");
    Serial.print(inicio);
    Serial.print(" ");
    Serial.println(fim);

    Serial.println(text);
  }

  if (text.length() > (fim + 1) - inicio || text.length() > 16) {
    if (fim - inicio == 0 && text.length() == 1) {
      lcd.setCursor(inicio, linha);
      lcd.print(text);
    }
    Serial.println("Erro, ou string eh maior que fim - inicio, ou eh maior que 16 caracteres");
  } else {
    for (int k = inicio; k <= fim; k++) {
      lcd.setCursor(k, linha);
      lcd.print(" ");
    }
    lcd.setCursor(inicio, linha);
    lcd.print(text);
  }
}