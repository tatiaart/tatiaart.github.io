/*
  STM32Duino UART basic example

  Periodically print a hello world message over a connected uart module.

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


void loop() {
  delay(1000);
  myserial.print("Hello world!\r\n");
}
