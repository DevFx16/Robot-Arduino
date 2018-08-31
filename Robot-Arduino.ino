
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  SensorUltrasonico();
}

void SensorUltrasonico() {
  long duracion, distancia;
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  duracion = pulseIn(6, HIGH);
  distancia = (duracion / 2) / 29;
  if (distancia <= 15 && distancia >= 1) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }
  delay(100);
}
