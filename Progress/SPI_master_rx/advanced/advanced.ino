#define SYM_AMOUNT 16
uint8_t symbol[SYM_AMOUNT] = {0b00000010, 0b10011110, 0b00100100, 0b00001100, 0b10011000, 0b01001000, 0b01000000, 0b00011110, 
                              0b00000000, 0b00001000, 0b00010000, 0b11000000, 0b01100010, 0b10000100, 0b01100000, 0b01110000};

void spi_setup(){

  RCC->IOPENR  |=   (0b1 << 0);   // Enable GPIO Port A clock
  RCC->APBENR2 |=  (0b1 << 12);   // Enable SPI1 clock

  GPIOA->MODER &= ~(0b11 << 24);
  GPIOA->MODER |=  (0b10 << 24);  // PA_12 set to alternate mode

  GPIOA->MODER &= ~(0b11 << 2);
  GPIOA->MODER |=  (0b10 << 2);   // PA_1 set to alternate mode

  SPI1->CR1 = 0b0000001110111100; // TODO: describe
  
  SPI1->CR2  = 0b1    << 12;
  SPI1->CR2 |= 0b0111 << 8;
  
  SPI1->CR1 |= 0b1    << 6;
}

void spi_send(uint8_t data){
  *(volatile uint8_t*)&SPI1->DR = (data); // Make sure to write only 8 bits
}

void setup() {
  RCC->IOPENR |= (1 << 1); // Enable GPIO Port B clock

  GPIOB->MODER &= ~(0b11 << 0);
  GPIOB->MODER |=  (0b01 << 0); // PB_0 set to output

  spi_setup();
}

uint8_t num = 0;

void loop() {
    spi_send(symbol[num%SYM_AMOUNT]); // Send symbol
    num++;                            // Increment counter

    GPIOB->BSRR |= (0b1<<0); // Enable display
    delay(1000);             // for 1 second

    GPIOB->BRR |= (0b1<<0);  // Disable display
}
