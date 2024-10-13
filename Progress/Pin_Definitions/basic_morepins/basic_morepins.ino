void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D12, INPUT_PULLUP);
                                /*
                                Note that STM32duino provides macros for the pins defined on the nucleo board.
                                LED_BUILTIN is actually pin PC_6, and D12 is PB_4
                                */

  GPIOB->MODER &= ~(11<<10);     // Reset bits 10 and 11 of the GPIOB_MODER register, setting pin PB_5's mode to 00 (input) 
  GPIOB->PUPDR &= ~(11<<10);
  GPIOB->PUPDR |=  (01<<10);     // Reset bits 10 and 11, and set bit 8 of the GPIOB_PUPDR register,
                                 // setting pin PB_5's internal pullup mode to 01 (pull-up) 
}

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(D12)); // Note that we write the inverse of the D12 pin's state
  delay(500);
  digitalWrite(LED_BUILTIN, !digitalRead(D11)); // Note that we write the inverse of the D12 pin's state
  delay(500);
}
