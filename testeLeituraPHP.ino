/*
Indica separacao entre um tipo de dado ou outro
# h -> hora atual
% m -> minuto atual
* s -> segundo atual
@ t -> temperatura
! hD -> hora de despertar
= mD -> minuto de despertar
*/


String horaA = String ("");
String minutoA = String ("");
String segundoA = String ("");
String horaD = String ("");
String minutoD = String ("");
String segundoD = String ("");
String temperatura = String("");

char entrada;

void setup() {
  Serial.begin(9600);

}

void loop() {
  if (Serial.available() > 0) {
    entrada = (char) Serial.read();

    if (entrada == '#') {
      Serial.println("Pegando hora atual");
      if (horaA != "") {
        horaA = "";
      }
      obtemHoraPHPA();
    }

    if (entrada == '%') {
      Serial.println("Pegando minuto atual");
      if (minutoA != "") {
        minutoA = "";
      }
      obtemMinutoPHPA();

    }

    if (entrada == '*') {
      Serial.println("Pegando segundo atual");
      if (segundoA != "") {
        segundoA = "";
      }
      obtemSegundoPHPA();
    }

    if (entrada == '@') {
      Serial.println("Pegando Temperatura");
      if (temperatura != "") {
        temperatura = "";
      }
      obtemTemperatura();
    }

    if (entrada == '!') {
      Serial.println("Pegando hora despertar");
      if (horaD != "") {
        horaD = "";
      }
      obtemHoraPHPD();
    }

    if (entrada == '=') {
      Serial.println("Pegando minuto despertar");
      if (minutoD != "") {
        minutoD = "";
      }
      obtemMinutoPHPD();
    }
  }
}

void obtemMinutoPHPD() {
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
}

void obtemHoraPHPD() {
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
}

void obtemTemperatura() {
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
}

void obtemSegundoPHPA() {
  while (true) {
    if (Serial.available() > 0) {
      entrada = (char) Serial.read();
      if (entrada != '*') {
        segundoA += entrada;
      } else {
        break;
      }
    }
  }
  Serial.print(segundoA);
  Serial.println(" s");
}

void obtemMinutoPHPA() {
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
}

void obtemHoraPHPA() {
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
}
