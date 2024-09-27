#include <Arduino.h>
#include <Wire.h>

#define KTD2061Q    0x68                     // slave address
#define CTRL_REG    0x02                     // control register 

#define IRED0_REG   0x03                    // color0 register and to set the current in mA with 125uA steps
#define IGRN0_REG   0x04
#define IBLU0_REG   0x05
#define IRED1_REG   0x06                    // color1 register
#define IGRN1_REG   0x07
#define IBLU1_REG   0x08

#define ISELA12_REG 0x09                   // selection register
#define ISELA34_REG 0x0A
#define ISELB12_REG 0x0B
#define ISELB34_REG 0x0C
#define ISELC12_REG 0x0D
#define ISELC34_REG 0x0E


// A bus three RGB LEDS 
// B bus two RGB LEDS
// C bus four RGB LEDS
// total 9 LEDS for POWER/RPM , BLE and TIMER indications
// A1, A2, A3 PINS 6, 7, 9
// B1, B2 PINS 11, 12
// C1, C2, C3, C4 PINS 16, 17, 18, 19
// by default the LED will be in shutdown mode
// to operate in normal mode 


// color settings registers 0x03 to 0x08

// selection register 0x09 to 0x0E 

// enable the normal mode

void enable_normal_mode(){
  Wire.beginTransmission(KTD2061Q);
  
  Wire.write(CTRL_REG);                   // normal mode enable
  Wire.write(0x80);                       //10000000 will enable normal mode and supply a current of 0 to 24mA
  Wire.endTransmission();
}

void set_green_color(){
  Wire.beginTransmission(KTD2061Q);
  Wire.write(IBLU0_REG);
  Wire.write(0);
  Wire.write(IBLU1_REG);
  Wire.write(0);
  Wire.write(IRED0_REG);
  Wire.write(0);
  Wire.write(IRED1_REG);
  Wire.write(0);
  Wire.write(ISELA12_REG);                // selecting A bus Two LEDS
  Wire.write(0xAA);                       // green color for two LEDS,- 1010 1010 

  Wire.write(ISELA34_REG);                // selecting third LED - green color
  Wire.write(0xA0);                       // 1010 0000 
  Wire.endTransmission();                 // blinking LED part to be added 


}

void set_blue_color(){
  Wire.beginTransmission(KTD2061Q);
  Wire.write(IGRN0_REG);
  Wire.write(0);
  Wire.write(IGRN1_REG);
  Wire.write(0);
  Wire.write(IRED0_REG);
  Wire.write(0);
  Wire.write(IRED1_REG);
  Wire.write(0);
  Wire.write(ISELB12_REG);

  Wire.write(0x90);                       //  blue color for two LEDS 1001 1100 
  Wire.endTransmission();


}

void set_yellow_color(){

  Wire.beginTransmission(KTD2061Q);
  Wire.write(IRED0_REG);
  Wire.write(0);
  Wire.write(IRED1_REG);
  Wire.write(0);
  Wire.write(ISELB12_REG);
  Wire.write(0x0D);                       // selecting bus B for Yellow

  Wire.write(ISELC12_REG);                // Selecting C bus for two LEDS
  Wire.write(0xDD);                       // Yellow color for two LEDS

  Wire.write(ISELC34_REG);
  Wire.write(0xDD);                       // yellow color for remianing two LEDS
  Wire.endTransmission();
}

void set_red_color(){
  Wire.beginTransmission(KTD2061Q);
  Wire.write(IBLU0_REG);
  Wire.write(0);
  Wire.write(IBLU1_REG);
  Wire.write(0);
  Wire.write(IGRN1_REG);
  Wire.write(0);
  Wire.write(IGRN0_REG);
  Wire.write(0);

  Wire.write(ISELA12_REG);                // Selecting bus A 
  Wire.write(0xCC);                       // red color in case of error or warning 1100 1100

  Wire.write(ISELA34_REG);                // selecting bus B
  Wire.write(0xC0);                       // red color for thrid LED

  Wire.write(ISELB12_REG);                // selecting bus B 
  Wire.write(0xCC);                       // red color for BLE LED and timer LED 1

  Wire.write(ISELC12_REG);                // selecting bus C
  Wire.write(0xCC);                       // red color for timer LEDS

  Wire.write(ISELC34_REG);                // selecting bus C
  Wire.write(0XCC);                       // red color for timer LEDS
  Wire.endTransmission();
}

void setup() {
Wire.setPins(21,22);
Wire.begin();
Serial.begin(115200);
Serial.println("Setup finished");
enable_normal_mode();
Serial.println("Normal mode");
set_blue_color();
delay(100);
set_green_color();
delay(100);
set_yellow_color();
delay(100);
set_red_color();
delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:
}

