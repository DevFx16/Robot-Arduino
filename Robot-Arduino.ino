#include <Servo.h>

//Sensor Ultrasonico
const int TrigSensor = 11;
const int EcSensor = 10;

//Led
const int Led = 13;

//ServoMotor
Servo ServoMotor;

//Motores
const int izqA = 3;
const int izqB = 5;
const int derA = 6;
const int derB = 11;
const int vel = 255; // Velocidad de los motores (0-255)

void setup()  {
  Serial.begin(9600);
  //Motores
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  //Servo
  ServoMotor.attach(9);
  //Led
  pinMode(Led, OUTPUT);
  //Sensor ultrasonico
  pinMode(EcSensor, INPUT);
  pinMode(TrigSensor, OUTPUT);
}

void loop()  {
  SensorUltrasonico();
}

//Funcionamiento Del sensor
void SensorUltrasonico() {
  long duracion, distancia;
  digitalWrite(TrigSensor, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigSensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigSensor, LOW);
  duracion = pulseIn(EcSensor, HIGH);
  distancia = (duracion / 2) / 29;
  //Limite
  Serial.println(distancia);
  if (distancia <= 100 && distancia >= 1) {
    digitalWrite(Led, HIGH);
    Frenar();
    ServoGrados(0, 2000);
    ServoGrados(180, 2000);
  } else {
    digitalWrite(Led, LOW);
    Reversa();
    ServoGrados(90, 200);
  }
  delay(200);
}

void Frente() {
  analogWrite(derA, vel);  // Frente 2 segundos
  analogWrite(izqA, vel);
  delay (2000);
}

void Frenar() {
  analogWrite(derA, 0);  // Detiene los Motores
  analogWrite(derB, 0);  // Detiene los Motores
  analogWrite(izqA , 0);
    analogWrite(izqB , 0);
  delay (500);
}

void Girar() {
  analogWrite(derA, vel);  // Derecha 0,5 segundos
  analogWrite(izqA, 0);
  delay (500);

  analogWrite(derA, 0);    // Izquierda 0,5 segundos
  analogWrite(izqA, vel);
  delay (500);
}

void Reversa() {
  analogWrite(derB, vel);  // Reversa 2 segundos
  analogWrite(izqB, vel);
  delay (2000);
}

void ServoGrados(int Grados, int Delay) {
  ServoMotor.write(Grados);
  delay(Delay);
}
