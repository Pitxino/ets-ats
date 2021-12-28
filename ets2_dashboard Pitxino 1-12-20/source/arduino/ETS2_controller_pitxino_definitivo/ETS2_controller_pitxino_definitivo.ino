

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


// display 2 digitos
int pinA = 25;
int pinB = 26;
int pinC = 27;
int pinD = 28;
int pinE = 29;
int pinF = 30;
int pinG = 31;
int pinH = 32;

int Marcha1 = 50;
int Marcha2 = 51;
int Marcha3 = 52;

#define PIN         52 
#define NUMPIXELS   74 // Popular NeoPixel ring size
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


const uint32_t rojo = strip.Color(255, 0, 0);
const uint32_t verde = strip.Color(0, 255, 0);
const uint32_t azul = strip.Color(0, 0, 255);
const uint32_t amarillo = strip.Color(255, 255, 0);
const uint32_t negro = strip.Color(0, 0, 0);
const uint32_t blanco = strip.Color(255, 255, 255);


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

//
//
//                variables lectura com
//
//
int serial_byte                   = 0;
int servo_velocimetro             = 0;
int servo_tacometro               = 0;
int servo_temperatura_frenos      = 0;
int servo_presion_frenos          = 0;
int servo_gasoleo                 = 0;
int servo_temperatura_agua        = 0;
int servo_temperatura_aceite      = 0;
int servo_voltaje_bateria         = 0;
int servo_presion_aceite          = 0;
int control_crucero               = 0;
int servo_adblue                  = 0;
bool light_beacon                 = 0;
bool light_parking                = 0;
bool left_indicator               = 0;
bool right_indicator              = 0;
bool low_beam                     = 0;
bool high_beam                    = 0;
bool light_brake                  = 0;
bool parking_brake                = 0;
bool motor_brake                  = 0;
bool brake_air_pressure_warning   = 0;
bool brake_air_pressure_emergency = 0;
bool fuel_warning                 = 0;
bool battery_voltage_warning      = 0;
bool oil_pressure_warning         = 0;
bool water_temperature_warning    = 0;
bool adblue_warning               = 0;
bool electric_enabled             = 0;
bool engine_enabled               = 0;
int text_len                      = 0;
int marchas                       = 0;

bool primera_vez                  = 1;
bool estado_anterior              = 0;




//
//
//
//
//                            PROGRAMA PRINCIPAL
//
//

void setup()
{
  Serial.begin(115200);
//  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  
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
  speedo.attach(SPEED_PIN);
  speedo.write(175);
  watertemp.attach(WATER_TEMPERATURE_PIN);
  watertemp.write(175);
  braketemp.attach(BRAKE_TEMPERATURE_PIN);
  braketemp.write(175);
  brakeairpress.attach(BRAKE_AIR_PRESSURE_PIN);
  brakeairpress.write(175);
  cruise.write(175);
  
  /*
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinH, OUTPUT); 

  //range-splitter LED's
  pinMode(Marcha1, OUTPUT);
  pinMode(Marcha2, OUTPUT);
  pinMode(Marcha3, OUTPUT);
  */

  todo_encendido();
  delay(2000);
  todo_apagado();
  delay(1000);
}


//                  void loop que funciona
void loop()
{
  if (Serial.available() < 20)
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
  
  read_serial_byte_set_servo_fuel(brakeairpress,SERVO_DIR_INVERT); // Brake air pressure
  read_serial_byte_set_servo_fuel(braketemp,SERVO_DIR_INVERT); // Brake temperature
  read_serial_byte_set_servo_fuel(fuel, SERVO_DIR_INVERT); // Fuel ratio
  read_serial_byte_set_servo_fuel(oilpress, SERVO_DIR_INVERT); // Oil pressure
  read_serial_byte_set_servo_fuel(oiltemp, SERVO_DIR_INVERT); // Oil temperature
  read_serial_byte_set_servo_fuel(watertemp, SERVO_DIR_INVERT); // Water temperature
  read_serial_byte_set_servo_fuel(batteryvolt, SERVO_DIR_INVERT); // Battery voltage
  read_serial_byte_set_servo_cruise(cruise, SERVO_DIR_INVERT); // cruise speed, set to trip a light  
  read_serial_byte_set_servo_fuel(adblue, SERVO_DIR_INVERT); //adblue ratio



  if (cruise.read() < 180)
      {
      digitalWrite(CRUISE_CONTROL, 1);
      }
  if (cruise.read() > 179)
      {
      digitalWrite(CRUISE_CONTROL, 0);
      }

  if (braketemp.read() < 20)  // braketemp lee el valor del servo y como es inverso hay que 
    {
      strip.setPixelColor(BRAKE_TEMPERATURE_LED, rojo);

    }    
    else
      {
        strip.setPixelColor(BRAKE_TEMPERATURE_LED, blanco);
      }

  if (oiltemp.read() < 20)  // braketemp lee el valor del servo y como es inverso hay que 
    {
      strip.setPixelColor(OIL_TEMPERATURE_LED, rojo);

    }    
    else
      {
        strip.setPixelColor(OIL_TEMPERATURE_LED, blanco);
      }


  // Truck lights byte
  serial_byte = Serial.read();
/*  digitalWriteFromBit(LIGHT_BEACON_LED, serial_byte, 7, amarillo);
  digitalWriteFromBit(LIGHT_LBLINKER_LED,  serial_byte, 5,verde);  
  digitalWriteFromBit(LIGHT_RBLINKER_LED, serial_byte, 4,verde);
  digitalWriteFromBit(LIGHT_LOW_BEAM_LED,  serial_byte, 3,amarillo);  
  digitalWriteFromBit(LIGHT_HIGH_BEAM_LED, serial_byte, 2, azul);
  digitalWriteFromBit(LIGHT_BRAKE_LED, serial_byte, 1, rojo);*/
  
  
  // Warning lights bytes

  serial_byte = Serial.read();  
/*  digitalWriteFromBit(PARKING_BRAKE_LED, serial_byte, 7, rojo);
  digitalWriteFromBit(MOTOR_BRAKE_LED, serial_byte, 6, rojo);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_WARNING_LED, serial_byte, 5, rojo);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_EMERGENCY_LED, serial_byte, 4, rojo);
  digitalWriteFromBit(FUEL_WARNING_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(BATTERY_VOLTAGE_WARNING_LED, serial_byte, 2, rojo); 
  digitalWriteFromBit(OIL_PRESSURE_WARNING_LED, serial_byte, 1, rojo); 
  digitalWriteFromBit(WATER_TEMPERATURE_WARNING_LED, serial_byte, 0, rojo);*/

 
  // Enabled flags
  serial_byte = Serial.read();
/*  digitalWriteFromBit(ADBLUE_WARNING_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(ENGINE_ENABLED_LED, serial_byte, 0, verde);*/
 

    // Text length
    text_len = Serial.read();
    
    // Followed by text
    if (0 < text_len && text_len < 127)
    {
      for (int i = 0; i < text_len; ++i)
      {
        
        while (Serial.available() == 0) // Wait for data if slow
        {
          delay(2);
        }
        serial_byte = Serial.read();
        marchas = serial_byte;
        if (serial_byte == 'a')
        {
          //1
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'b')
        {
          //2
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'c')
        {
          //3
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'd')
        {
          //4
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'e')
        {
          //5
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'f')
        {
          //6
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'g')
        {
          //7
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'h')
        {
          //8
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'i')
        {
          //9
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'j')
        {
          //10
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'k')
        {
          //11
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'l')
        {
          //12
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'm')
        {
          //13
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'n')
        {
          //14
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'o')
        {
          //15
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'p')
        {
          //16
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'q')
        {
          //17
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 'r')
        {
          //18
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, LOW);
        }
        else  if (serial_byte == 's')
        {
          // R1
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, HIGH);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 't')
        {
          //R2
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, HIGH);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'u')
        {
          //R3
          digitalWrite(pinA, LOW);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, LOW);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'v')
        {
          //R4
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, HIGH);
          digitalWrite(pinC, LOW);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, LOW);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        else  if (serial_byte == 'w')
        {
          // Neutral
          digitalWrite(pinA, HIGH);
          digitalWrite(pinB, LOW);
          digitalWrite(pinC, HIGH);
          digitalWrite(pinD, HIGH);
          digitalWrite(pinE, HIGH);
          digitalWrite(pinF, LOW);
          digitalWrite(pinG, LOW);
          digitalWrite(pinH, HIGH);
        }
        //sets range splitter LED's
        if (serial_byte == 'a' || serial_byte == 'd' || serial_byte == 'g' || serial_byte == 'j' || serial_byte == 'm' || serial_byte == 'p' || serial_byte == 's' || serial_byte == 'v')
          {
            digitalWrite(Marcha1, 1);
          }
        else
          {
            digitalWrite(Marcha1, 0);
          }
        if (serial_byte == 'b' || serial_byte == 'e' || serial_byte == 'h' || serial_byte == 'k' || serial_byte == 'n' || serial_byte == 'q' || serial_byte == 't')
          {
            digitalWrite(Marcha2, 1);
          }
        else
          {
            digitalWrite(Marcha2, 0);
          }
        if (serial_byte == 'c' || serial_byte == 'f' || serial_byte == 'i' || serial_byte == 'l' || serial_byte == 'o' || serial_byte == 'r' || serial_byte == 'u')
          {
            digitalWrite(Marcha3, 1);
          }
        else
          {
            digitalWrite(Marcha3, 0);
          }
      } // for
    }
//    pixels.show();   // Send the updated pixel colors to the hardware.
    strip.show();   // Send the updated pixel colors to the hardware.

    delay(300);  

}


//
//
//
//
//
//                  PROCESOS
//
//
//
//
//
//
//
//


void read_serial_byte_set_servo(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180 : serial_byte);
  if (invert)
    servo.write(180 - serial_byte);
  else
    servo.write(serial_byte);
}

void read_serial_byte_set_servo_fuel(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180 : serial_byte);
  if (invert)
    servo.write(180 - serial_byte); //set lower than the tach and speedo to limit movement.
  else
    servo.write(serial_byte);
}

void read_serial_byte_set_servo_cruise(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180 : serial_byte);
  if (invert)
    servo.write(180 - serial_byte); //set lower than the tach and speedo to limit movement.
  else
    servo.write(serial_byte);
}

void skip_serial_byte()
{
  (void)Serial.read();
}

/* orifinal
void digitalWriteFromBit(int port, int value, int shift)
{
  digitalWrite(port, (value >> shift) & 0x01);
}
*/

void digitalWriteFromBit(int port, int value, int shift, uint32_t color)
{
  if ((value >> shift) & 0x01){
//    pixels.setPixelColor(port, color);
    strip.setPixelColor(port, color);
  } else {
//    pixels.setPixelColor(port, negro);
    strip.setPixelColor(port, blanco);
  }
}



void todo_encendido()
{
  for (int i=175; i>=5;i--){
    speedo.write(i);
    rpm.write(i);
    braketemp.write(i);
    brakeairpress.write(i);
    fuel.write(i);
    adblue.write(i);
    watertemp.write(i);
    oiltemp.write(i);
    batteryvolt.write(i);
    oilpress.write(i);
//    delay(25);
  }

  /*
  digitalWrite(Marcha1, 1);
  digitalWrite(Marcha2, 1);
  digitalWrite(Marcha3, 1);
  */
/*
  pixels.setPixelColor( 0, verde);    // encendemos verde encendido
  pixels.setPixelColor( 1, amarillo); // encendemos amarillo luces cortas
  pixels.setPixelColor( 2, azul);     // encendemos azul luces largas
  pixels.setPixelColor( 3, amarillo); // encendemos amarillo balizas
  pixels.setPixelColor( 4, rojo);     // encendemos rojo peligro presion aceite
  pixels.setPixelColor( 5, amarillo); // encendemos amarillo nivel diesel  
  pixels.setPixelColor( 6, amarillo); // encendemos amarillo nivel adblue   
  pixels.setPixelColor( 7, rojo);     // encendemos rojo peligro bateria  
  pixels.setPixelColor( 8, rojo);     // encendemos rojo peligro temperatura aceite
  pixels.setPixelColor( 9, verde);    // encendemos verde intermitente izquierdo
  pixels.setPixelColor(10, rojo);     // encendemos rojo peligro generico
  pixels.setPixelColor(11, verde);    // encendemos verde intermitente derecho
  pixels.setPixelColor(12, rojo);     // encendemos rojo peligro temperatura
  pixels.setPixelColor(13, rojo);     // encendemos rojo peligro temperatura frenos 
  pixels.setPixelColor(14, rojo);     // encendemos rojo peligro presion frenos
  pixels.setPixelColor(15, rojo);     // encendemos rojo freno
  pixels.setPixelColor(16, rojo);     // encendemos rojo freno motor
  pixels.setPixelColor(17, rojo);     // encendemos rojo freno estacionamiento
  pixels.show();   // Send the updated pixel colors to the hardware.*/
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue

}

void todo_apagado()
{    
  for (int i=5; i<=175;i++){
    speedo.write(i);
    rpm.write(i);
    braketemp.write(i);
    brakeairpress.write(i);
    fuel.write(i);
    adblue.write(i);
    watertemp.write(i);
    oiltemp.write(i);
    batteryvolt.write(i);
    oilpress.write(i);
//    delay(25);
  }

  /*
  digitalWrite(Marcha1, 0);
  digitalWrite(Marcha2, 0);
  digitalWrite(Marcha3, 0);

  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  */  

//  pixels.clear(); // Set all pixel colors to 'off'
  strip.clear(); // Set all pixel colors to 'off'
//  pixels.show();   // Send the updated pixel colors to the hardware.
  strip.show();   // Send the updated pixel colors to the hardware.
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
