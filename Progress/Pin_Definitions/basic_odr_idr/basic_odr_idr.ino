void setup() {
  pinMode(PA_14, INPUT_PULLUP);
  pinMode(PA_13, INPUT_PULLUP);
  pinMode(PA_12, OUTPUT);
  pinMode(PA_11, OUTPUT);
}

void loop() {
  GPIO->ODR = (((GPIOA->IDR >> 13) & 0b11) << 11);
}
