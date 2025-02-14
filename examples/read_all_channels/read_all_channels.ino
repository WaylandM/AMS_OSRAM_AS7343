/* This example will read all channels from the AS7343 and print out reported values */

// include the library file from this github
#include "AMS_OSRAM_AS7343.h"

// Define the spectrometer Type
AMS_OSRAM_AS7343 as7343;


void setup() {
  Serial.begin(115200);

  // Wait for communication with the host computer serial monitor
  while (!Serial) {
    delay(1);
  }
  
  if (!as7343.begin()) {
    Serial.println("Could not find AS7343");
    while (1) { delay(10); }
  }

  as7343.setATIME(100);
  as7343.setASTEP(999);1
  as7343.setGain(AS7343_GAIN_256X);
}

void loop() {
    uint16_t readings[18];

  if (!as7343.readAllChannels(readings)) {
    Serial.println("Error reading all channels!");
    return;
  }

  // https://look.ams-osram.com/m/5f2d27fff9a874d2/original/AS7343-14-Channel-Multi-Spectral-Sensor.pdf#page=45&zoom=auto,-110,842
  // Library sets auto_smux to mode 3, meaning the buffer gets populated with 18 readings in the following batches:
  // Cycle 1: FZ, FY, FXL, NIR, 2xVIS, FD
  // Cycle 2: F2, F3, F4, F6, 2xVIS, FD
  // Cycle 3: F1, F7, F8, F5, 2xVIS, FD

  Serial.print("Set1/FZ 440-460nm : ");
  Serial.println(readings[0]);
  Serial.print("Set1/FY 545-565nm : ");
  Serial.println(readings[1]);
  Serial.print("Set1/FXL 590-610nm : ");
  Serial.println(readings[2]);
  Serial.print("Set1/NIR 845-865nm: ");
  Serial.println(readings[3]);
  Serial.print("Set1/2xVIS : ");
  Serial.println(readings[4]);
  Serial.print("Set1/FD ??nm : ");
  Serial.println(readings[5]);

  Serial.print("Set2/F2 415-435nm : ");
  Serial.println(readings[6]);
  Serial.print("Set2/F3 465-485nm : ");
  Serial.println(readings[7]);
  Serial.print("Set2/F4 505-525nm : ");
  Serial.println(readings[8]);
  Serial.print("Set2/F6 630-650nm : ");
  Serial.println(readings[9]);
  //Serial.print("Set2/2xVIS : ");
  //Serial.println(readings[10]);
  //Serial.print("Set2/FD ??nm : ");
  //Serial.println(readings[11]);

  Serial.print("Set3/F1 395-415nm : ");
  Serial.println(readings[12]);
  Serial.print("Set3/F7 680-700nm : ");
  Serial.println(readings[13]);
  Serial.print("Set3/F8 735-755nm : ");
  Serial.println(readings[14]);
  Serial.print("Set3/F5 540-560nm : ");
  Serial.println(readings[15]);
  //Serial.print("Set3/2xVIS : ");
  //Serial.println(readings[16]);
  //Serial.print("Set3/FD ??nm : ");
  //Serial.println(readings[17]);

  Serial.println("-----------------------");
}
