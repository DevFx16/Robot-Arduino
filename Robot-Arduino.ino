#include <Servo.h>

//Sensor Ultrasonico
const int TrigSensor = 8;
const int EcSensor = 10;
long distancia = 0;

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
  pinMode(TrigSensor, OUTPUT); //pin como salida
  pinMode(EcSensor, INPUT);  //pin como entrada
}

void loop()  {
  SensorUltrasonico();
  digitalWrite(Led, LOW);
  Frente();
  ServoGrados(90, 500);
  if (distancia <= 40) {
    digitalWrite(Led, HIGH);
    Frenar();
    ServoGrados(0, 500);
    ServoGrados(180, 500);
    Girar();
  }
}

//Funcionamiento Del sensor
void SensorUltrasonico() {
  long t; //timepo que demora en llegar el eco

  digitalWrite(TrigSensor, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(TrigSensor, LOW);

  t = pulseIn(EcSensor, HIGH); //obtenemos el ancho del pulso
  distancia = t / 59;           //escalamos el tiempo a una distancia en cm
  Serial.println(distancia);
}

void Frente() {
  analogWrite(derA, vel);  // Reversa 2 segundos
  analogWrite(izqA, vel);
  delay(1000);
}

void Frenar() {
  analogWrite(derB, 0);  // Detiene los Motores
  analogWrite(izqB , 0);
  analogWrite(derA, 0);  // Detiene los Motores
  analogWrite(izqA , 0);
  delay(500);
}

void Girar() {
  analogWrite(derA, vel);  // Derecha 0,5 segundos
  analogWrite(izqB, 0);
  delay(1000);
}

void Reversa() {
  analogWrite(derB, vel);  // Reversa 2 segundos
  analogWrite(izqB, vel);
  delay(500);
}

void ServoGrados(int Grados, int Delay) {
  ServoMotor.write(Grados);
  delay(Delay);
}
