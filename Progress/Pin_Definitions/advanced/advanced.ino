void setup() {
  // To configure pins PA_13 and PA_14 as inputs with pullup resistors, and PA_11 and PA_12 as outputs:
  // 1. No need to translate arduino to stm32 pins (we already know them - PORT_A, pins 11 - 14)

  // 2. Enable the GPIO port A clock
  RCC->IOPENR |= (1 << 0);       // Set bit 0 of the RCC_IOPENR register, enabling port A clock.

  // 3. No need to set port speed since the default value is adequate.
  // 4. No need to handle alternative pin functions for this MCU

  // 5. Write the configuration registers
  GPIOA->MODER &= ~(0b11111010 << 2 * 11);  // Write the calculated configuration

  GPIOA->PUPDR &= ~(0b1111 << 2 * 13);      // Reset bits 26 - 29, and set bit 26 and 28 of the GPIOA_PUPDR register,
  GPIOA->PUPDR |=  (0b0101 << 2 * 13);      // setting pin PA_13 and PA_14's internal pullup mode to 01 (pull-up) 
}

void loop() {
  GPIOA->ODR = (((GPIOA->IDR >> 13) & 0b11) << 11);
}
