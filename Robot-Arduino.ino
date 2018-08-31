#include <Servo.h>

Servo s;
long duracion, distancia;

void setup() {
  Serial.begin(9600);
  s.attach(2);
  pinMode(13, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(7, LOW);

  duracion = pulseIn(6, HIGH);
  distancia = (duracion / 2) / 29;          // calcula la distancia en centimetros

  if (distancia >= 500 || distancia <= 0) { // si la distancia es mayor a 500cm o menor a 0cm
    Serial.println("---");                  // no mide nada
  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");
    digitalWrite(13, HIGH); // le coloca a la distancia los centimetros "cm"
    // en bajo el pin 13
  }

  if (distancia <= 10 && distancia >= 1) {
    digitalWrite(13, LOW);
    // en alto el pin 13 si la distancia es menor a 10cm
    Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial
  }
  delay(400);                                // espera 400ms para que se logre ver la distancia en la consola

}
