#define SYM_AMOUNT 16
uint8_t symbol[SYM_AMOUNT] = {0b00000010, 0b10011110, 0b00100100, 0b00001100, 0b10011000, 0b01001000, 0b01000000, 0b00011110, 
                              0b00000000, 0b00001000, 0b00010000, 0b11000000, 0b01100010, 0b10000100, 0b01100000, 0b01110000};

void send_data(uint8_t data){
    for(int i = 0; i<8; i++){
                                
        if( (data>>i) & 0b1 )   // Set/Reset MOSI
        {
            GPIOA->BSRR |= (0b1<<12);
        }
        else
        {
            GPIOA->BRR |= (0b1<<12);
        }

                                // Pulse CLK
        GPIOA->BSRR |= (0b1<<1); 
        delay(100);             // For demonstration purposes, these delays are exaggerated
                                // For instant operation, replace with delayMicroseconds(1);
        GPIOA->BRR |= (0b1<<1);
        delay(100);
    }
}

void setup() {
  RCC->IOPENR |= (11 << 0);       // Enable GPIO Port A & B clock

  GPIOB->MODER &= ~(0b11 << 0);
  GPIOB->MODER |=  (0b01 << 0);   // PB_0 set to output

  GPIOA->MODER &= ~(0b11 << 24);
  GPIOA->MODER |=  (0b01 << 24);  // PA_12 set to output

  GPIOA->MODER &= ~(0b11 << 2);
  GPIOA->MODER |=  (0b01 << 2);   // PA_1 set to output
}

uint8_t num = 0;

void loop() {
    send_data(symbol[num%SYM_AMOUNT]);      // Send symbol
    num++;                                  // Increment counter

    GPIOB->BSRR |= (0b1<<0);    // Enable display
    delay(1000);                // for 1 second

    // GPIOB->BRR |= (0b1<<0);  // Disable display
    // ^^^^^^^^^^^^^^^^^^^^^^^
    // This pin reset for disabling the display is commented out
    // To showcase how the shift-register gets filled in sequentially in real time
    // Uncomment it and reduce the delay in send_data() 
    // For instant operation
}
