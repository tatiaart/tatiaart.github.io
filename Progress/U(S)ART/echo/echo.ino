/*
  STM32Duino UART echo example

  Print back the ascii values of bytes received over UART.

  12.12.2024
  Artem Tatianin
*/

HardwareSerial myserial(PA_10_R, PA_9_R);

void setup() {
  //Initialize serial and wait for port to open:
  myserial.begin(115200);
  while (!myserial) {
  }
}

char incomingByte;

void loop() {      
      if (myserial.available() > 0) {
        incomingByte = myserial.read();
        myserial.print("I received: ");
        myserial.println(incomingByte, DEC);
      }
}
