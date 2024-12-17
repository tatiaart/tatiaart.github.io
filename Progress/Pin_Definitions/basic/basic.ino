void setup() {
  pinMode(PA14, INPUT_PULLUP);
  pinMode(PA13, INPUT_PULLUP);
  pinMode(PA12, OUTPUT);
  pinMode(PA11, OUTPUT);
}

void loop() {
  digitalWrite(PA12, digitalRead(PA14));
  digitalWrite(PA11, digitalRead(PA13));
}
