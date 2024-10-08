#include <Arduino.h>


#include <Wire.h>

#define I2C_SDA 8
#define I2C_SCL 9
static int count_green=0;
static int count_blue=0;
static int count_red=0;
static int count_yellow=0;
void red_led();
void writeRegister(uint8_t slaveAddress, uint8_t registerAddress, uint8_t payload) {
  Wire.beginTransmission(slaveAddress);
  // Writing values to various registers
  Wire.write(registerAddress);
  Wire.write(payload);  // Value for the register
  Wire.endTransmission();
}
void readRegister(uint8_t slaveAddress, uint8_t registerAddress) {
  Wire.beginTransmission(slaveAddress);
  Wire.write(registerAddress);  // Point to the register we want to read
  Wire.endTransmission();
  Wire.requestFrom(slaveAddress, 1);  // Request 1 byte from the device
  if (Wire.available()) {
    uint8_t readValue = Wire.read();  // Read the byte
    // Here you can process readValue as needed
    // For example, you might print it or store it for verification
//     Serial.print("Register 0x");
//     Serial.print(registerAddress, HEX);
//     Serial.print(": 0x");
//     Serial.println(readValue, HEX);
  }
}
void readRegister_16(uint8_t slaveAddress, uint8_t registerAddress) {
  Wire.beginTransmission(slaveAddress);
  Wire.write(registerAddress);  // Point to the register we want to read
  Wire.endTransmission();
  Wire.requestFrom(slaveAddress, 2);  // Request 1 byte from the device
  if (Wire.available()) {
    uint16_t readValue = Wire.read();  // Read the byte
    // Here you can process readValue as needed
    // For example, you might print it or store it for verification
//     Serial.print("Register 0x");
//     Serial.print(registerAddress, HEX);
//     Serial.print(": 0x");
//     Serial.println(readValue, HEX);
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(I2C_SDA, INPUT_PULLUP);
  pinMode(I2C_SCL, INPUT_PULLUP);
  Wire.setPins(I2C_SDA, I2C_SCL);
  Wire.begin();

}
void green_led()
{
    count_green++;
    if(count_green==1)
    {
      writeRegister(0x68, 9, 0xD0);
      writeRegister(0x68, 10, 0x00);
    }
    else if(count_green==2)
    {
      writeRegister(0x68, 9, 0xD0);
      writeRegister(0x68, 10, 0xD0);
    }
    else if(count_green==3)
    {
      writeRegister(0x68, 9, 0xDD);
      writeRegister(0x68, 10, 0xD0);
    }
    else if(count_green==4)
   {
      writeRegister(0x68, 9, 0x00);
      writeRegister(0x68, 10, 0x00);
   }
    else if(count_green>4)
    {
      count_green=0;
      green_led();
    }
}
void blue_led()
{

  count_blue++;
  if(count_blue==1 && count_yellow==0)
  {
    writeRegister(0x68, 11, 0xE0); 
    writeRegister(0x68, 12, 0x00);    
  }
  else if(count_blue==1 && (count_yellow==1 || count_yellow==2 || count_yellow==3 || count_yellow==4 || count_yellow==5 ))
  {
    writeRegister(0x68, 11, 0xE9);
    writeRegister(0x68, 12, 0x00); 
  }
  else if(count_blue>1 && (count_yellow==1 || count_yellow==2 || count_yellow==3 || count_yellow==4 || count_yellow==5 ))
  {
    writeRegister(0x68, 11, 0x09); 
    writeRegister(0x68, 12, 0x00);       
    count_blue=0;
    
//    blue_led();
  }
  else if(count_blue==0 &&(count_yellow==1 || count_yellow==2 || count_yellow==3 || count_yellow==4 || count_yellow==5 ))
   {
    writeRegister(0x68, 11, 0x09);
    writeRegister(0x68, 12, 0x00); 
  }
  else if(count_blue==0 && count_yellow==0)
  {
    writeRegister(0x68, 11, 0x00);
    writeRegister(0x68, 12, 0x00); 
  }
  else if(count_blue>1 && count_yellow==0)
  {
    writeRegister(0x68, 11, 0x00);
    writeRegister(0x68, 12, 0x00); 
    count_blue=0;
  }
}

void yellow_led()
{

  count_yellow++;
  if(count_yellow==1 && count_blue==0)
  {
    writeRegister(0x68, 11, 0x09); 
//    writeRegister(0x68, 11, 0x09);    
    writeRegister(0x68, 13, 0x00);
    writeRegister(0x68, 14, 0x00);
  }
  else if(count_yellow==1 && count_blue==1)
  {
    writeRegister(0x68, 11, 0xE9);    
    writeRegister(0x68, 13, 0x00);
    writeRegister(0x68, 14, 0x00);
  }
  else if(count_yellow==2 && count_blue==1)
  {
    writeRegister(0x68, 11, 0xE9);
//    writeRegister(0x68, 11, 0x09); 
    writeRegister(0x68, 13, 0x09);
    writeRegister(0x68, 14, 0x00);
  }
  else if(count_yellow==3 && count_blue==1)
  {
    writeRegister(0x68, 11, 0xE9);
//    writeRegister(0x68, 11, 0x09);
    writeRegister(0x68, 13, 0x99);
    writeRegister(0x68, 14, 0x00);
  }
  else if(count_yellow==4 && count_blue==1)
  {
    writeRegister(0x68, 11, 0xE9);
//    writeRegister(0x68, 11, 0x09);
    writeRegister(0x68, 13, 0x99);
    writeRegister(0x68, 14, 0x90);
  }
  else if(count_yellow==5 && count_blue==1)
  {
    writeRegister(0x68, 11, 0xE9);
//    writeRegister(0x68, 11, 0x09);
    writeRegister(0x68, 13, 0x99);
    writeRegister(0x68, 14, 0x99);
  }
  else if(count_yellow>5 && count_blue==1)
  {
    writeRegister(0x68, 11, 0xE0); 
    writeRegister(0x68, 13, 0x00);
    writeRegister(0x68, 14, 0x00);
    count_yellow=0;
//    yellow_led();     
  }
 else if(count_yellow==1 && count_blue==0)
  {
    writeRegister(0x68, 11, 0x09);    
    writeRegister(0x68, 13, 0x00);
    writeRegister(0x68, 14, 0x00);
  }
  else if(count_yellow==2 && count_blue==0)
  {
    writeRegister(0x68, 11, 0x09); 
    writeRegister(0x68, 13, 0x09);
    writeRegister(0x68, 14, 0x00);
  }
  else if(count_yellow==3 && count_blue==0)
  {
    writeRegister(0x68, 11, 0x09); 
    writeRegister(0x68, 13, 0x99);
    writeRegister(0x68, 14, 0x00);
  }
  else if(count_yellow==4 && count_blue==0)
  {
    writeRegister(0x68, 11, 0x09); 
    writeRegister(0x68, 13, 0x99);
    writeRegister(0x68, 14, 0x90);
  }
  else if(count_yellow==5 && count_blue==0)
  {
    writeRegister(0x68, 11, 0x09); 
    writeRegister(0x68, 13, 0x99);
    writeRegister(0x68, 14, 0x99);
  }
  else if(count_yellow>5 && count_blue==0)
  {
    writeRegister(0x68, 11, 0x00); 
    writeRegister(0x68, 13, 0x00);
    writeRegister(0x68, 14, 0x00);
    count_yellow=0;
//    yellow_led(); 
  }
    else if(count_yellow==0 && count_blue==1)
  {
    writeRegister(0x68, 11, 0xE0); 
    writeRegister(0x68, 13, 0x00);
    writeRegister(0x68, 14, 0x00);
  }
}
void led_off()
{
  writeRegister(0x68, 9, 0x00);
  writeRegister(0x68, 10, 0x00);
  writeRegister(0x68, 11, 0x00);
  writeRegister(0x68, 12, 0x00);
  writeRegister(0x68, 13, 0x00);
  writeRegister(0x68, 14, 0x00);
  count_red=0;
  count_green=0;
  count_blue=0;
  count_yellow=0;
}
void red_led()
{

  count_red++;
  if(count_red==1)
  {
    writeRegister(0x68, 9, 0xBB);
    writeRegister(0x68, 10, 0xBB);
    writeRegister(0x68, 11, 0xBB);
    writeRegister(0x68, 12, 0xBB);
    writeRegister(0x68, 13, 0xBB);
    writeRegister(0x68, 14, 0xBB);
//    red_led();
//    delay()
  }

  else if(count_red>1)
  {
    led_off();
//    red_led();
  }
}
void loop() 
{
char user_input=Serial.read();
// LED Driver Configuration
  writeRegister(0x68, 3, 0x28);
  writeRegister(0x68, 4, 0x28);
  writeRegister(0x68, 5, 0x28);
  writeRegister(0x68, 6, 0x00);
  writeRegister(0x68, 7, 0x00);
  writeRegister(0x68, 8, 0x00);
  writeRegister(0x68, 2, 0x80);
  readRegister(0x68, 0);
  if(user_input == 'g')
  {
    if(count_red==0)
    {
      green_led();
    }
    else
    {
      writeRegister(0x68, 9, 0xBB);
      writeRegister(0x68, 10, 0xBB);
      writeRegister(0x68, 11, 0xBB);
      writeRegister(0x68, 12, 0xBB);
      writeRegister(0x68, 13, 0xBB);
      writeRegister(0x68, 14, 0xBB);
//      red_led();
    }
  }
  else if(user_input == 'b')
  {
    if(count_red==0)
    {
      blue_led();
    }
    else
    {
//      red_led();
    writeRegister(0x68, 9, 0xBB);
    writeRegister(0x68, 10, 0xBB);
    writeRegister(0x68, 11, 0xBB);
    writeRegister(0x68, 12, 0xBB);
    writeRegister(0x68, 13, 0xBB);
    writeRegister(0x68, 14, 0xBB);
    }
  }

//   delay(5000);
 else if(user_input=='y')
 {
    if(count_red==0)
    {
      yellow_led();
    }
    else
    {
//      red_led();
    writeRegister(0x68, 9, 0xBB);
    writeRegister(0x68, 10, 0xBB);
    writeRegister(0x68, 11, 0xBB);
    writeRegister(0x68, 12, 0xBB);
    writeRegister(0x68, 13, 0xBB);
    writeRegister(0x68, 14, 0xBB);
    }
 }
 else if(user_input=='r')
 {
    red_led();
 }
}

