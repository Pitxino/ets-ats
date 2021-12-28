/*
Copyright (c) 2013, Silas Parker
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
    The name of Silas Parker may not be used to endorse or promote products
    derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <LiquidCrystal.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>


const int SPEEDO_PIN      = A6;
const int RPM_PIN         = A3;
const int LEFT_INDICATOR  = 15;
const int RIGHT_INDICATOR = 38;
const int PARKING_BREAK   = 45;
const int FUEL_WARNING    = 16;

// Servo variables
Servo speedo;
Servo rpm;



#define PACKET_SYNC 0xFF
#define PACKET_VER  2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true

#define PIN         6 
#define NUMPIXELS   75 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t rojo = pixels.Color(255, 0, 0);
const uint32_t verde = pixels.Color(0, 255, 0);
const uint32_t azul = pixels.Color(0, 0, 255);
const uint32_t amarillo = pixels.Color(255, 255, 0);
const uint32_t negro = pixels.Color(0, 0, 0);
const uint32_t blanco = pixels.Color(255, 255, 255);


int serial_byte;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);

void setup()
{
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  lcd.begin(16, 2);
  lcd.print("Self Test");
  
  // Initialise servos
  speedo.attach(SPEEDO_PIN);
  speedo.write(180);
  
  rpm.attach(RPM_PIN);
  rpm.write(180);
  
  // Initialise LEDs
  pixels.setPixelColor( LEFT_INDICATOR, verde);    // encendemos verde
  pixels.setPixelColor( RIGHT_INDICATOR, verde);    // encendemos verde
  pixels.setPixelColor( PARKING_BREAK, rojo);    // encendemos rojo
  pixels.setPixelColor( FUEL_WARNING, amarillo);    // encendemos amarillo
  pixels.show();
  delay(1000);
  pixels.clear();  // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.

  speedo.write(0);
  rpm.write(0);
 
  delay(500);

  pixels.setPixelColor( LEFT_INDICATOR, verde);    // encendemos verde
  pixels.setPixelColor( RIGHT_INDICATOR, verde);    // encendemos verde
  pixels.setPixelColor( PARKING_BREAK, rojo);    // encendemos rojo
  pixels.setPixelColor( FUEL_WARNING, amarillo);    // encendemos amarillo
  pixels.show();
  delay(1000);
  pixels.clear();  // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.
  
 
  
  delay(500);
  
  speedo.write(180);
  rpm.write(180);
  
  
  lcd.clear();
  lcd.print("Wait");
  
  // Wait a second to ensure serial data isn't from re-programming 
  delay(1000);
  lcd.clear();
  lcd.print("Ready");
}



void read_serial_byte_set_servo(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180 : serial_byte);
  if (invert)
    servo.write(180 - serial_byte);
  else
    servo.write(serial_byte);
}

void skip_serial_byte()
{
  (void)Serial.read();
}

void digitalWriteFromBit(int port, int value, int shift, uint32_t color)
{
  if ((value >> shift) & 0x01){
    pixels.setPixelColor(port, color);
  } else {
    pixels.setPixelColor(port, negro);
  }
}

void loop()
{
  if (Serial.available() < 16)
    return;
  
  serial_byte = Serial.read();
  if (serial_byte != PACKET_SYNC)
    return;
    
  serial_byte = Serial.read();
  if (serial_byte != PACKET_VER)
  {
    lcd.clear();
    lcd.print("PROTOCOL VERSION ERROR");
    return;
  }
  
  read_serial_byte_set_servo(speedo, SERVO_DIR_INVERT); // Speed  
  read_serial_byte_set_servo(rpm, SERVO_DIR_INVERT); // RPM
  
  skip_serial_byte(); // Brake air pressure
  skip_serial_byte(); // Brake temperature
  skip_serial_byte(); // Fuel ratio
  skip_serial_byte(); // Oil pressure
  skip_serial_byte(); // Oil temperature
  skip_serial_byte(); // Water temperature
  skip_serial_byte(); // Battery voltage
    
  
  // Truck lights byte
  serial_byte = Serial.read();
  digitalWriteFromBit(LEFT_INDICATOR,  serial_byte, 5, verde);  
  digitalWriteFromBit(RIGHT_INDICATOR, serial_byte, 4, verde);
  
  // Warning lights bytes

  serial_byte = Serial.read();  
  digitalWriteFromBit(PARKING_BREAK, serial_byte, 7, rojo);
  digitalWriteFromBit(FUEL_WARNING, serial_byte, 3, amarillo);  
 
  // Enabled flags
  serial_byte = Serial.read();
  
  // Text length
  int text_len = Serial.read();
  
  // Followed by text
  if (0 < text_len && text_len < 127)
  {
    lcd.clear();
    for (int i = 0; i < text_len; ++i)
    {
      while (Serial.available() == 0) // Wait for data if slow
      {
        delay(2);
      }
      serial_byte = Serial.read();
      if (serial_byte < 0 && serial_byte > 127)
        return;
      
      if (serial_byte == '\n')
        lcd.setCursor(0, 1);
      else
        lcd.print(char(serial_byte));
//      delay(2);
    }
  }
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(300);  
  
}
