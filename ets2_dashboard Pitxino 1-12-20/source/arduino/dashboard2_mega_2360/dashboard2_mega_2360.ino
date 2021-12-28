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


// servos izquierda
const int OIL_TEMPERATURE_PIN       = A0;
const int BATTERY_VOLTAGE_PIN       = A1;
const int OIL_PRESSURE_PIN          = A2;
const int ENGINE_RPM_PIN            = A3;
const int ADBLUE_PIN                = A4;
const int FUEL_PIN                  = A5;
// servos derecha
const int SPEED_PIN                 = A6;
const int WATER_TEMPERATURE_PIN     = A7;
const int BRAKE_TEMPERATURE_PIN     = A8;
const int BRAKE_AIR_PRESSURE_PIN    = A9;

// leds 1
const int ENGINE_ENABLED_LED        =  0;
const int BOCINA_LED                =  1;
const int BOCINA_AIRE_LED           =  2;
const int LIGHT_HIGH_BEAM_LED       =  3;
const int LIGHT_LOW_BEAM_LED        =  4;
const int LIGHT_BEACON_LED          =  5;
const int DESACOPLAR_REMOLQUE_LED   =  6;
const int LIMPIA_LENTO_LED          =  7;
const int LIMPIA_RAPIDO_LED         =  8;
// leds 2
const int OIL_PRESSURE_WARNING_LED  =  9;
const int PRESION_ACEITE_LED        = 10;
const int BATTERY_VOLTAGE_WARNING_LED = 11;
const int BATERIA_LED               = 12;
const int OIL_TEMPERATURE_LED       = 13; //hay que calcularlo, no scs
const int TEMPERATURA_ACEITE_LED    = 14;
const int LIGHT_LBLINKER_LED        = 15;
const int FUEL_WARNING_LED          = 16;
const int FUEL_LED                  = 17;
const int ADBLUE_WARNING_LED        = 18;
const int ADBLUE_LED                = 19;
const int RPM1_LED                  = 20;
const int RPM2_LED                  = 21;
const int RPM3_LED                  = 22;
const int RPM4_LED                  = 23;
const int RPM5_LED                  = 24;
const int RPM6_LED                  = 25;
const int RPM7_LED                  = 26;
const int RPM_LED                   = 27;
const int BRAKE_AIR_PRESSURE_EMERGENCY_LED = 28;
const int SPEED1_LED                = 29;
const int SPEED2_LED                = 30;
const int SPEED3_LED                = 31;
const int SPEED4_LED                = 32;
const int SPEED5_LED                = 33;
const int SPEED6_LED                = 34;
const int SPEED7_LED                = 35;
const int SPEED8_LED                = 36;
const int SPEED_LED                 = 37;
const int LIGHT_RBLINKER_LED        = 38;
const int TEMPERATURA_AGUA_LED      = 39;
const int WATER_TEMPERATURE_WARNING_LED = 40;
const int TEMPERATURA_FRENOS_LED    = 41;
const int BRAKE_TEMPERATURE_LED     = 42; //hay que calcularlo, no scs
const int PRESION_FRENOS_LED        = 43;
const int BRAKE_AIR_PRESSURE_WARNING_LED = 44;
// leds 3
const int PARKING_BRAKE_LED         =45;
const int DIFERENCIAL               =46;
const int MOTOR_BRAKE_LED           =47;
const int AUMENTAR_RETARDER         =48;
const int LIGHT_BRAKE_LED           =49;
const int DISMINUIR_RETARDER_LED    =50;
// leds 4
const int SUBIR_VENTANILLA_IZQUIERDA_LED =51;
const int SUBIR_VENTANILLA_DERECHA_LED   =52;
const int CAMBIAR_ORDENADOR_LED          =53;
const int CAMBIAR_GPS_LED                =54;
const int BAJAR_VENTANILLA_IZQUIERDA_LED =55;
const int BAJAR_VENTANILLA_DERECHA_LED   =56;
const int LUCES_PELIGRO_LED              =57;
const int MAPA_LED                       =58;
const int RAFAGA_LED                     =59;
const int CANCION_ANTERIOR_LED           =60;
const int CANCION_SIGUIENTE_LED          =61;
const int RADIO_LED                      =62;

const int CONTROL_CRUCERO_LED            =63;
const int VOLVER_CONTROL_CRUCERO_LED     =64;
const int SUBIR_EJE_CAMION_LED           =65;
const int SUBIR_EJE_TRAILER_LED          =66;
const int BAJAR_VELOCIDAD_CRUCERO_LED    =67;
const int SUBIR_VELOCIDAD_CRUCERO_LED    =68;
const int PUERTA_5_LED                   =69;
const int RAMPA_LED                      =70;
const int PUERTA_4_LED                   =71;
const int PUERTA_3_LED                   =72;
const int PUERTA_2_LED                   =73;
const int PUERTA_1_LED                   =74;

const int ELECTRIC_ENABLED               = 0; // switch encendido o apagado


// Servo variables
Servo oiltemp;
Servo batteryvolt;
Servo oilpress;
Servo rpm;
Servo adblue;
Servo fuel;
Servo speed;
Servo watertemp;
Servo braketemp;
Servo brakeairpress;


#define PACKET_SYNC 0xFF
#define PACKET_VER  2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true

#define PIN         52
#define NUMPIXELS   74 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t rojo = pixels.Color(255, 0, 0);
const uint32_t verde = pixels.Color(0, 255, 0);
const uint32_t azul = pixels.Color(0, 0, 255);
const uint32_t amarillo = pixels.Color(255, 255, 0);
const uint32_t negro = pixels.Color(0, 0, 0);
const uint32_t blanco = pixels.Color(127, 127, 127);


int serial_byte;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);

void setup()
{
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  lcd.begin(16, 2);
  lcd.print("Self Test");
  
  // Initialise servos
  oiltemp.attach(OIL_TEMPERATURE_PIN);
  oiltemp.write(175);
  batteryvolt.attach(BATTERY_VOLTAGE_PIN);
  batteryvolt.write(175);
  oilpress.attach(OIL_PRESSURE_PIN);
  oilpress.write(175);
  rpm.attach(ENGINE_RPM_PIN);
  rpm.write(175);
  adblue.attach(ADBLUE_PIN);
  adblue.write(175);
  fuel.attach(FUEL_PIN);
  fuel.write(175);
  speed.attach(SPEED_PIN);
  speed.write(175);
  watertemp.attach(WATER_TEMPERATURE_PIN);
  watertemp.write(175);
  braketemp.attach(BRAKE_TEMPERATURE_PIN);
  braketemp.write(175);
  brakeairpress.attach(BRAKE_AIR_PRESSURE_PIN);
  brakeairpress.write(175);
  
  // Initialise LEDs
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, blanco);
    pixels.show();
    delay(10);
  }


  oiltemp.attach(OIL_TEMPERATURE_PIN);
  oiltemp.write(0);
  batteryvolt.attach(BATTERY_VOLTAGE_PIN);
  batteryvolt.write(0);
  oilpress.attach(OIL_PRESSURE_PIN);
  oilpress.write(0);
  rpm.attach(ENGINE_RPM_PIN);
  rpm.write(0);
  adblue.attach(ADBLUE_PIN);
  adblue.write(0);
  fuel.attach(FUEL_PIN);
  fuel.write(0);
  speed.attach(SPEED_PIN);
  speed.write(0);
  watertemp.attach(WATER_TEMPERATURE_PIN);
  watertemp.write(0);
  braketemp.attach(BRAKE_TEMPERATURE_PIN);
  braketemp.write(0);
  brakeairpress.attach(BRAKE_AIR_PRESSURE_PIN);
  brakeairpress.write(0);

  delay(500);
  
  oiltemp.attach(OIL_TEMPERATURE_PIN);
  oiltemp.write(175);
  batteryvolt.attach(BATTERY_VOLTAGE_PIN);
  batteryvolt.write(175);
  oilpress.attach(OIL_PRESSURE_PIN);
  oilpress.write(175);
  rpm.attach(ENGINE_RPM_PIN);
  rpm.write(175);
  adblue.attach(ADBLUE_PIN);
  adblue.write(175);
  fuel.attach(FUEL_PIN);
  fuel.write(175);
  speed.attach(SPEED_PIN);
  speed.write(175);
  watertemp.attach(WATER_TEMPERATURE_PIN);
  watertemp.write(175);
  braketemp.attach(BRAKE_TEMPERATURE_PIN);
  braketemp.write(175);
  brakeairpress.attach(BRAKE_AIR_PRESSURE_PIN);
  brakeairpress.write(175);

  
  pixels.setPixelColor( LIGHT_LBLINKER_LED, verde);    // encendemos verde
  pixels.setPixelColor( LIGHT_RBLINKER_LED, verde);    // encendemos verde
  pixels.setPixelColor( PARKING_BRAKE_LED, rojo);    // encendemos rojo
  pixels.setPixelColor( FUEL_WARNING_LED, amarillo);    // encendemos amarillo
  pixels.show();
  delay(5000);
  
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
    pixels.setPixelColor(port, blanco);
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
  
  read_serial_byte_set_servo(speed, SERVO_DIR_INVERT); // Speed  
  read_serial_byte_set_servo(rpm, SERVO_DIR_INVERT); // RPM
  read_serial_byte_set_servo(brakeairpress, SERVO_DIR_INVERT); // Brake air pressure
  read_serial_byte_set_servo(braketemp, SERVO_DIR_INVERT); // Brake temperature
  read_serial_byte_set_servo(fuel, SERVO_DIR_INVERT); // Fuel ratio
  read_serial_byte_set_servo(oilpress, SERVO_DIR_INVERT); // Oil pressure
  read_serial_byte_set_servo(oiltemp, SERVO_DIR_INVERT); // Oil temperature
  read_serial_byte_set_servo(watertemp, SERVO_DIR_INVERT); // Water temperature
  read_serial_byte_set_servo(batteryvolt, SERVO_DIR_INVERT); // Battery voltage
    
  
  // Truck lights byte
  serial_byte = Serial.read();
  digitalWriteFromBit(LIGHT_LBLINKER_LED,  serial_byte, 5, verde);  
  digitalWriteFromBit(LIGHT_RBLINKER_LED, serial_byte, 4, verde);
  digitalWriteFromBit(LIGHT_LOW_BEAM_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(LIGHT_HIGH_BEAM_LED, serial_byte, 2, azul);
  digitalWriteFromBit(LIGHT_BRAKE_LED, serial_byte, 1, rojo);
  
  // Warning lights bytes

  serial_byte = Serial.read();  
  digitalWriteFromBit(PARKING_BRAKE_LED, serial_byte, 7, rojo);
  digitalWriteFromBit(MOTOR_BRAKE_LED, serial_byte, 6, rojo);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_WARNING_LED, serial_byte, 5, rojo);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_EMERGENCY_LED, serial_byte, 4, rojo);
  digitalWriteFromBit(FUEL_WARNING_LED, serial_byte, 3, amarillo);  
  digitalWriteFromBit(BATTERY_VOLTAGE_WARNING_LED, serial_byte, 2, rojo);  
  digitalWriteFromBit(OIL_PRESSURE_WARNING_LED, serial_byte, 1, rojo);  
  digitalWriteFromBit(WATER_TEMPERATURE_WARNING_LED, serial_byte, 0, rojo);  

  // Enabled flags
  serial_byte = Serial.read();
  digitalWriteFromBit(ENGINE_ENABLED_LED, serial_byte, 0, verde);  
  
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
