#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  mySerial.begin(9600);
  Serial.println("Debugging started");
}

void loop()
{
  uint8_t tosend;
  char debugBuf[100];
  char uartBuf[100];

  Serial.println("What byte to send:");
  while (!Serial.available())
  {
  }
  size_t length = Serial.readBytesUntil('\n', uartBuf, 100);

  Serial.print("Sending: ");
  Serial.write(uartBuf, length);
  Serial.println();
  mySerial.write(uartBuf, length);

  Serial.print("Recieved: ");
  mySerial.readBytesUntil('\n', uartBuf, 100);
  Serial.write(uartBuf, length);
  Serial.println();

  delay(1000); // Send the message every second
}
