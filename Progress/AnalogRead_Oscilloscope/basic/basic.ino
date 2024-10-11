int conversion_result = 0;
#define VOLTAGE_REFERENCE 3300  //mV
#define MAX_ANALOG_READ   1024  
#define VOLTAGE_COEFFICIENT int(1000*((float)VOLTAGE_REFERENCE/MAX_ANALOG_READ))
unsigned int value = 0;
unsigned int time_since_start = 0;

void setup() {
  pinMode(D12, OUTPUT);           // initialize D12 as an output.      
  pinMode(A1, INPUT);           // initialize A1 as input                        

  Serial.begin(2000000);          // Crank the usart frequency up to increase possible the amount of samples we can send per second

  analogWriteFrequency(1000);     // PWM freq
  analogWrite(D12, 128);          // Duty cycle = 128/256 = 50%

  Serial.print("$$TSTM32DUINO"); // Intro message 
}

void loop() {
  conversion_result = analogRead(A1);                               // Run one-off conversion
  value = conversion_result*VOLTAGE_COEFFICIENT;                    // Convert to millivolt
  time_since_start = micros();           

  Serial.write("$$Puu4", 6);
  Serial.write((unsigned char *)&time_since_start, 4);
  Serial.write("uu4", 3);
  Serial.write(((unsigned char*)&value), 4);
  Serial.write(";", 1);
}