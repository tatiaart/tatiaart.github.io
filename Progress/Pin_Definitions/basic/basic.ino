void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D12, INPUT_PULLUP);
                                /*
                                Note that STM32duino provides macros for the pins defined on the nucleo board.
                                LED_BUILTIN is actually pin PC_6, and D12 is PB_4
                                */
}

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(D12)); // Note that we write the inverse of the D12 pin's state
}
