#include<SoftwareSerial.h>
int loop_counter = 0;
static const int Tx= 3, Rx = 4; // change this to the pins required [Remember: Arduino Rx pin connects to Tx of other dvice and vice-versa]
SoftwareSerial S1(Tx,Rx);

void setup() {
int data = 0;
Serial.begin(9600);
delay(250);
S1.begin(9600);
delay(250);
}

void loop() {
 while (loop_counter < 1000) {                                                          
    if (loop_counter < 1000)loop_counter ++;
    delayMicroseconds(4000);                                                              //Wait for 4000us to simulate a 250Hz loop.
    if (loop_counter == 1) {
      uint8_t set_to_97600[28] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x80, 
                              0x25, 0x00, 0x00, 0x07, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA2, 0xB5};
      S1.write(set_to_97600, 28);
      S1.begin(9600);
      delay(250);
      Serial.println("");
      Serial.println("====================================================================");
      Serial.println("Checking gps data @ 9600bps");
      Serial.println("====================================================================");
    }
    if (loop_counter > 1 && loop_counter < 200)while (S1.available())Serial.print((char)S1.read());
    if (loop_counter == 200) {
      Serial.println("");
      Serial.println("====================================================================");
      Serial.println("Checking gps data @ 57600bps");
      Serial.println("====================================================================");
      delay(200);
      
      //Disable GPGSV messages  B5 62 06 01 03 00 F0 03 00 FD 15 
      uint8_t Disable_GPGSV[11] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x03, 0x00, 0xFD, 0x15};
      S1.write(Disable_GPGSV, 11);
      delay(350);
      //Set the refresh rate to 5Hz
      uint8_t Set_to_5Hz[14] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8, 0x00, 0x01, 0x00, 0x01, 0x00, 0xDE, 0x6A};
      S1.write(Set_to_5Hz, 14);
      delay(350);
      //Set the baud rate to 57.6kbps to match the refresh rate
      uint8_t Set_to_57kbps[28] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0,
                                   0x08, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x07, 0x00, 0x03, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0xDE, 0xC9
                                  };
      S1.write(Set_to_57kbps, 28);
      delay(200);

      S1.begin(57600);
      delay(200);


      while (S1.available())S1.read();
    }
    if (loop_counter > 200 && loop_counter < 1000)while (S1.available())Serial.print((char)S1.read());
  }                         
    //since the baud rate is being set back to 9600 reduce the refresh rate
uint8_t set_to_1_Hz[14]= {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xE8, 0x03, 0x01, 0x00, 0x01, 0x00, 0x01, 0x39};
S1.write(set_to_1_Hz, 14);
loop_counter = 0;  
}
