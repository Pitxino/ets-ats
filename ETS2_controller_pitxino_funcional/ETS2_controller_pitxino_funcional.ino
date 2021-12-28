/*Copyright (c) 2013, Silas Parker
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
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

//servos
//izquierda
const int OILTEMP_PIN         = 2;
const int BATTERYVOLT_PIN     = 3;
const int OILPRESS_PIN        = 4;
const int RPM_PIN             = 5;
const int ADBLUE_PIN          = 6;
const int FUEL_PIN            = 7;
//derecha
const int SPEEDO_PIN          = 8;
const int WATERTEMP_PIN       = 9;
const int BRAKETEMP_PIN       = 10;
const int BRAKEAIRPRESS_PIN   = 11;

const int CRUISE_CONTROL      = A10;

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


// defines servo names
Servo oiltemp;
Servo batteryvolt;
Servo oilpress;
Servo rpm;
Servo adblue;
Servo fuel;
Servo speedo;
Servo watertemp;
Servo braketemp;
Servo brakeairpress;
Servo cruise;

#define PACKET_SYNC 0xFF
#define PACKET_VER  2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true

#define PIN         52
#define NUMPIXELS   75 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t rojo = pixels.Color(255, 0, 0);
const uint32_t verde = pixels.Color(0, 255, 0);
const uint32_t azul = pixels.Color(0, 0, 255);
const uint32_t amarillo = pixels.Color(255, 255, 0);
const uint32_t negro = pixels.Color(0, 0, 0);
const uint32_t blanco = pixels.Color(127, 127, 127);

int serial_byte;

void setup()
{
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(50);
  oiltemp.attach(OILTEMP_PIN);
  oiltemp.write(180);
  batteryvolt.attach(BATTERYVOLT_PIN);
  batteryvolt.write(180);
  oilpress.attach(OILPRESS_PIN);
  oilpress.write(180);
  rpm.attach(RPM_PIN);
  rpm.write(180);
  adblue.attach(ADBLUE_PIN);
  adblue.write(180);
  fuel.attach(FUEL_PIN);
  fuel.write(180);
  speedo.attach(SPEEDO_PIN);
  speedo.write(180);
  watertemp.attach(WATERTEMP_PIN);
  watertemp.write(180);
  braketemp.attach(BRAKETEMP_PIN);
  braketemp.write(180);
  brakeairpress.attach(BRAKEAIRPRESS_PIN);
  brakeairpress.write(180);
  cruise.write(180);

  // Initialise LEDs
  pixels.fill(blanco);
  pixels.show();
  
  delay(500);
  
  for (int s=180; s>=0;s--){
    oiltemp.write(s);
    batteryvolt.write(s);
    oilpress.write(s);
    rpm.write(s);
    adblue.write(s);
    fuel.write(s);
    speedo.write(s);
    watertemp.write(s);
    braketemp.write(s);
    brakeairpress.write(s);
    delay(10);
  }
  
  delay(2000);
  
  for (int s=0; s<=180;s++){
    oiltemp.write(s);
    batteryvolt.write(s);
    oilpress.write(s);
    rpm.write(s);
    adblue.write(s);
    fuel.write(s);
    speedo.write(s);
    watertemp.write(s);
    braketemp.write(s);
    brakeairpress.write(s);
    delay(10);
  }
  delay(1000);
  pixels.fill(rojo);
  pixels.show();
  delay(1000);
  pixels.fill(verde);
  pixels.show();
  delay(1000);
  pixels.fill(azul);
  pixels.show();
  delay(1000);
  pixels.fill(negro);
  pixels.show();

}


void loop()
{
  if (Serial.available() < 17)
    return;
  
  serial_byte = Serial.read();
  if (serial_byte != PACKET_SYNC)
    return;
    
  serial_byte = Serial.read();
  if (serial_byte != PACKET_VER)
  {
    return;
  }
  
  read_serial_byte_set_servo(speedo, SERVO_DIR_INVERT); // Speed  
  read_serial_byte_set_servo(rpm, SERVO_DIR_INVERT); // RPM
  read_serial_byte_set_servo(brakeairpress,SERVO_DIR_INVERT); // Brake air pressure
  read_serial_byte_set_servo(braketemp,SERVO_DIR_INVERT); // Brake temperature
  read_serial_byte_set_servo(fuel, SERVO_DIR_INVERT); // Fuel ratio
  read_serial_byte_set_servo(oilpress, SERVO_DIR_INVERT); // Oil pressure
  read_serial_byte_set_servo(oiltemp, SERVO_DIR_INVERT); // Oil temperature
  read_serial_byte_set_servo(watertemp, SERVO_DIR_INVERT); // Water temperature
  read_serial_byte_set_servo(batteryvolt, SERVO_DIR_INVERT); // Battery voltage
  read_serial_byte_set_servo_cruise(cruise, SERVO_DIR_INVERT); // cruise speed, set to trip a light  
  read_serial_byte_set_servo(adblue, SERVO_DIR_INVERT); //adblue ratio



  if (cruise.read() < 180)
      {
      digitalWrite(CRUISE_CONTROL, 1);
      }
  if (cruise.read() > 179)
      {
      digitalWrite(CRUISE_CONTROL, 0);
      }

// luz temperatura frenos
  if (braketemp.read() < 20)  // braketemp lee el valor del servo y como es inverso hay que 
    pixels.setPixelColor(BRAKE_TEMPERATURE_LED, rojo);  
  else
    pixels.setPixelColor(BRAKE_TEMPERATURE_LED, negro);

// luz temperatura aceite
  if (oiltemp.read() < 20)  // oiltemp lee el valor del servo y como es inverso hay que 
    pixels.setPixelColor(OIL_TEMPERATURE_LED, rojo);  
  else
    pixels.setPixelColor(OIL_TEMPERATURE_LED, negro);

// luces cuentarevoluciones
  if (rpm.read() < 175 & rpm.read() > 165 )
  {
    pixels.fill(blanco,  RPM1_LED, 7);
    pixels.setPixelColor(RPM1_LED, verde);
  }
  else if (rpm.read() < 165 & rpm.read() > 135 )
  {
    pixels.fill(blanco,  RPM1_LED, 7);
    pixels.fill(verde, RPM1_LED, 2);
  }
  else if (rpm.read() < 135 & rpm.read() > 105 )  
  {
    pixels.fill(blanco,  RPM1_LED, 7);
    pixels.fill(verde,RPM1_LED, 3);
  }
  else if (rpm.read() < 105 & rpm.read() > 75 )
  {
    pixels.fill(blanco,  RPM1_LED, 7);
    pixels.fill(verde, RPM1_LED, 4);
  }
  else if (rpm.read() < 75 & rpm.read() > 45 )
  {
    pixels.fill(blanco,  RPM1_LED, 7);
    pixels.fill(verde, RPM1_LED, 4);
    pixels.setPixelColor(RPM5_LED, rojo);
  }
  else if (rpm.read() < 45 & rpm.read() > 15 )
  {
    pixels.fill(blanco,  RPM1_LED, 7);
    pixels.fill(verde, RPM1_LED, 4);
    pixels.fill(rojo, RPM5_LED, 2);
  }  
  else if (rpm.read() < 15)
  {
    pixels.fill(blanco,  RPM1_LED, 7);
    pixels.fill(verde, RPM1_LED, 4);
    pixels.fill(rojo, RPM5_LED, 3);
  }
  else
    pixels.fill(blanco,RPM1_LED,7);

// luces cuentakilometros
  if (speedo.read() < 170 & speedo.read() > 150 )
   {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.setPixelColor(SPEED1_LED, verde);
   }
  else if (speedo.read() < 150 & speedo.read() > 130 )
  {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.fill(verde, SPEED1_LED, 2);
  }
  else if (speedo.read() < 130 & speedo.read() > 110 )  
  {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.fill(verde,SPEED1_LED, 3);
  }
  else if (speedo.read() < 110 & speedo.read() > 90)
  {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.fill(verde, SPEED1_LED, 4);
  }
  else if (speedo.read() < 90 & speedo.read() > 70 )
  {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.fill(verde, SPEED1_LED, 4);
    pixels.setPixelColor(SPEED5_LED, rojo);
  }
  else if (speedo.read() < 70 & speedo.read() > 50 )
  {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.fill(verde, SPEED1_LED, 4);
    pixels.fill(rojo, SPEED5_LED, 2);
  }  
  else if (speedo.read() < 50 & speedo.read() > 30 )
  {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.fill(verde, SPEED1_LED, 4);
    pixels.fill(rojo, SPEED5_LED, 3);
  }
  else if (speedo.read() < 30)
  {
    pixels.fill(blanco,  SPEED1_LED, 8);
    pixels.fill(verde, SPEED1_LED, 4);
    pixels.fill(rojo, SPEED5_LED, 4);
  }
  else
    pixels.fill(blanco,SPEED1_LED,8);
  
  // Truck lights byte
  serial_byte = Serial.read();
  digitalWriteFromBit(LIGHT_BEACON_LED, serial_byte, 7, amarillo);
  digitalWriteFromBit(LIGHT_LBLINKER_LED,  serial_byte, 5, verde);  
  digitalWriteFromBit(LIGHT_RBLINKER_LED, serial_byte, 4, verde);
  digitalWriteFromBit(LIGHT_LOW_BEAM_LED,  serial_byte, 3, amarillo);  
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
  digitalWriteFromBit(LIMPIA_LENTO_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(LIMPIA_RAPIDO_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(ADBLUE_WARNING_LED, serial_byte, 2, amarillo);
  digitalWriteFromBit(ELECTRIC_ENABLED, serial_byte, 1, blanco);
  digitalWriteFromBit(ENGINE_ENABLED_LED, serial_byte, 0, verde);
 

  // Text length
  int text_len = Serial.read();
  
  pixels.show();
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

void read_serial_byte_set_servo_cruise(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180: serial_byte);
  if (invert)
    servo.write(180 - serial_byte); //set lower than the tach and speedo to limit movement.
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
