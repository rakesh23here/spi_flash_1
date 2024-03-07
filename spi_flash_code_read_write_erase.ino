#include <SerialFlash.h>
//Changed the spi speed from 50MHz to 20MHz in the SerialFlashChip.cpp

#include <SPI.h>

#define FLASH_CS 5

void my_chip_erase(){
  SerialFlash.eraseAll();

  while (SerialFlash.ready() == false) {
   Serial.println("Waiting");
   delay(1000);
  }
}

void setup() {

  Serial.begin(9600);


  if (!SerialFlash.begin(FLASH_CS)) {
    while (1) {
      Serial.println(F("Unable to access SPI Flash chip"));
      delay(1000);
    }
  }
  unsigned char id[5];
  SerialFlash.readID(id);
  unsigned long size = SerialFlash.capacity(id);
  Serial.printf("Accessed %d\n",size);
  
  my_chip_erase();


  if (SerialFlash.create("hello.bin",512)) Serial.println("File Created!");
  else Serial.println("File already exists!");

  SerialFlashFile file;
  
  file = SerialFlash.open("hello.bin");
  if (file) {  // true if the file exists
  Serial.println("Ayyooo");
  file.write("12345678\n",9);
  file.write("87654321\n",9);}
  file.close();

  file = SerialFlash.open("hello.bin");
  char buffer[10];
  if (file) {
    file.read(buffer, 10);
  }
  Serial.println(buffer);
  Serial.println("bie");
}




void loop() {

}