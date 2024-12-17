#define SYM_AMOUNT 16
uint8_t symbol[SYM_AMOUNT] = {0b00000010, 0b10011110, 0b00100100, 0b00001100, 0b10011000, 0b01001000, 0b01000000, 0b00011110, 
                              0b00000000, 0b00001000, 0b00010000, 0b11000000, 0b01100010, 0b10000100, 0b01100000, 0b01110000};

#include <SPI.h>
SPIClass mySPI (PA12, PA11, PA1, PNUM_NOT_DEFINED); //MOSI, MISO, CLK, NSS (not used here)
              //      ^^^^^
              //  Note a limitation of STM32Duino core: appropriate MISO pin MUST be defined 
              //  for the SPI interface, even if never used. 
              //  It will be configured with it's alternate function set for the SPI peripheral,
              //  And must be reconfigured if it needs to be used elsewhere.

void setup() {
  RCC->IOPENR |= (1 << 1); // Enable GPIO Port B clock


  GPIOB->MODER &= ~(0b11 << 0);
  GPIOB->MODER |=  (0b01 << 0); // PB_0 set to output


  mySPI.begin(); // Initialize STM32Duino SPI
                 // Pin configuration is handled automatically
  mySPI.beginTransaction(SPISettings(25, LSBFIRST, SPI_MODE0)); // Set up transmission settings
}

uint8_t num = 0;

void loop() {
    mySPI.transfer(symbol[num%SYM_AMOUNT]); // Send symbol
    num++;                                  // Increment counter

    GPIOB->BSRR |= (0b1<<0); // Enable display
    delay(1000);             // for 1 second

    GPIOB->BRR |= (0b1<<0);  // Disable display
}
