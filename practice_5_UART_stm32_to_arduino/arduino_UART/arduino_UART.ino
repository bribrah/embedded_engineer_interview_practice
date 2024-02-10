#include <SoftwareSerial.h>
#include "CustomUart.h"

CustomUart mySerial(9600); // RX, TX

void setup()
{
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  Serial.println("Debugging started");
}

void loop()
{
  uint8_t tosend;
  char debugBuf[100];
  char uartBuf[100];
  int status;

  Serial.println("What byte to send:");
  while (!Serial.available())
  {
  }
  size_t length = Serial.readBytesUntil('\n', uartBuf, 100);

  Serial.print("Sending: ");
  Serial.write(uartBuf, length);
  Serial.println();
  for (int i = 0; i < length; i++)
  {
    mySerial.sendByte(uartBuf[i]);
  }
  mySerial.sendByte('\n');

  for (int i = 0; i < length; i++)
  {

    uartBuf[i] = mySerial.receiveByte(status);
  }
  Serial.print("Recieved: ");
  Serial.write(uartBuf, length);
  Serial.println();

  delay(1000); // Send the message every second
}
