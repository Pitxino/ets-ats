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

//servos
//derecha
const int SPEEDO_PIN          = A0;
const int BRAKEAIRPRESS_PIN   = A1;
const int BRAKETEMP_PIN       = A2;
const int WATERTEMP_PIN       = A3;
//izquierda
const int RPM_PIN             = A4;
const int ADBLUE_PIN          = A5;
const int FUEL_PIN            = A6;
const int OILTEMP_PIN         = A7;
const int BATTERYVOLT_PIN     = A8;
const int OILPRESS_PIN        = A9;
const int CRUISE_CONTROL      = A10;


// Truck lights byte
const int ADBLUE_WARNING                  =  4;
const int LEFT_INDICATOR                  =  6;
const int RIGHT_INDICATOR                 =  7;
const int LOW_BEAM                        = 17;
const int HIGH_BEAM                       = 18;
const int LIGHT_BRAKE                     = 11;
const int LIGHT_BEACON                    = 19;

// Warning lights bytes
const int PARKING_BRAKE                   = 13;
const int MOTOR_BRAKE                     = 12;
const int BRAKE_AIR_PRESSURE_WARNING      =  8;
const int BRAKE_AIR_PRESSURE_EMERGENCY    =  5;
const int FUEL_WARNING                    =  3;
const int BATTERY_VOLTAGE_WARNING         = 14;
const int OIL_PRESSURE_WARNING            = 15;
const int WATER_TEMPERATURE_WARNING       = 10;

// Enabled flags
const int ELECTRIC_ENABLED                = 22;
const int ENGINE_ENABLED                  = 16;
const int BRAKE_TEMP_WARNING              =  9;
const int OIL_TEMP_WARNING                =  2;

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

// defines servo names
Servo speedo;
Servo rpm;
Servo braketemp;
Servo brakeairpress;
Servo fuel;
Servo watertemp;
Servo oiltemp;
Servo batteryvolt;
Servo oilpress;
Servo cruise;
Servo adblue;

#define PACKET_SYNC 0xFF
#define PACKET_VER  2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true

int serial_byte;

void setup()
{
  Serial.begin(115200);

  speedo.attach(SPEEDO_PIN);
  speedo.write(180);
  rpm.attach(RPM_PIN);
  rpm.write(180);
  braketemp.attach(BRAKETEMP_PIN);
  braketemp.write(180);
  brakeairpress.attach(BRAKEAIRPRESS_PIN);
  brakeairpress.write(180);
  fuel.attach(FUEL_PIN);
  fuel.write(180);
  adblue.attach(ADBLUE_PIN);
  adblue.write(180);
  watertemp.attach(WATERTEMP_PIN);
  watertemp.write(180);
  oiltemp.attach(OILTEMP_PIN);
  oiltemp.write(180);
  batteryvolt.attach(BATTERYVOLT_PIN);
  batteryvolt.write(180);
  oilpress.attach(OILPRESS_PIN);
  oilpress.write(180);
  cruise.write(180);

  pinMode(LEFT_INDICATOR, OUTPUT);
  pinMode(RIGHT_INDICATOR, OUTPUT);
  pinMode(LOW_BEAM, OUTPUT);
  pinMode(HIGH_BEAM, OUTPUT);
  pinMode(LIGHT_BRAKE,OUTPUT);
  pinMode(PARKING_BRAKE, OUTPUT);
  pinMode(MOTOR_BRAKE, OUTPUT);
  pinMode(BRAKE_AIR_PRESSURE_WARNING, OUTPUT);
  pinMode(BRAKE_AIR_PRESSURE_EMERGENCY, OUTPUT);
  pinMode(FUEL_WARNING, OUTPUT);
  pinMode(ADBLUE_WARNING, OUTPUT);
  pinMode(BATTERY_VOLTAGE_WARNING, OUTPUT); 
  pinMode(OIL_PRESSURE_WARNING, OUTPUT); 
  pinMode(WATER_TEMPERATURE_WARNING, OUTPUT);
  pinMode(ELECTRIC_ENABLED, OUTPUT);
  pinMode(ENGINE_ENABLED, OUTPUT);
  pinMode(CRUISE_CONTROL, OUTPUT);
  pinMode(LIGHT_BEACON, OUTPUT);
  pinMode(BRAKE_TEMP_WARNING, OUTPUT);
  pinMode(OIL_TEMP_WARNING, OUTPUT);


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
  
  digitalWrite(LEFT_INDICATOR, 0);
  digitalWrite(RIGHT_INDICATOR, 0);
  digitalWrite(LOW_BEAM, 0);
  digitalWrite(HIGH_BEAM, 0);
  digitalWrite(LIGHT_BRAKE,0);
  digitalWrite(PARKING_BRAKE, 0);
  digitalWrite(MOTOR_BRAKE, 0);
  digitalWrite(BRAKE_AIR_PRESSURE_WARNING, 0);
  digitalWrite(BRAKE_AIR_PRESSURE_EMERGENCY, 0);
  digitalWrite(FUEL_WARNING, 0);
  digitalWrite(ADBLUE_WARNING, 0);
  digitalWrite(BATTERY_VOLTAGE_WARNING, 0); 
  digitalWrite(OIL_PRESSURE_WARNING, 0); 
  digitalWrite(WATER_TEMPERATURE_WARNING, 0);
  digitalWrite(ELECTRIC_ENABLED, 0);
  digitalWrite(ENGINE_ENABLED, 0);
  digitalWrite(CRUISE_CONTROL, 0);
  digitalWrite(LIGHT_BEACON, 0);
  digitalWrite(BRAKE_TEMP_WARNING, 0);
  digitalWrite(OIL_TEMP_WARNING, 0);


  
  delay(500);
  
  for (int i=180; i>=0;i--){
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
    delay(50);
  }
/*
  speedo.write(0);
  rpm.write(0);
  braketemp.write(5);
  brakeairpress.write(5);
  fuel.write(5);
  adblue.write(5);
  watertemp.write(5);
  oiltemp.write(5);
  batteryvolt.write(5);
  oilpress.write(5);
*/

  digitalWrite(LEFT_INDICATOR, 1);
  digitalWrite(RIGHT_INDICATOR, 1);
  digitalWrite(LOW_BEAM, 1);
  digitalWrite(HIGH_BEAM, 1);
  digitalWrite(LIGHT_BRAKE,1);
  digitalWrite(PARKING_BRAKE, 1);
  digitalWrite(MOTOR_BRAKE, 1);
  digitalWrite(BRAKE_AIR_PRESSURE_WARNING, 1);
  digitalWrite(BRAKE_AIR_PRESSURE_EMERGENCY, 1);
  digitalWrite(FUEL_WARNING, 1);
  digitalWrite(ADBLUE_WARNING, 1);
  digitalWrite(BATTERY_VOLTAGE_WARNING, 1); 
  digitalWrite(OIL_PRESSURE_WARNING, 1); 
  digitalWrite(WATER_TEMPERATURE_WARNING, 1);
  digitalWrite(ELECTRIC_ENABLED, 1);
  digitalWrite(ENGINE_ENABLED, 1);
  digitalWrite(CRUISE_CONTROL, 1);
  digitalWrite(LIGHT_BEACON, 1);
  digitalWrite(BRAKE_TEMP_WARNING, 1);
  digitalWrite(OIL_TEMP_WARNING, 1);

  digitalWrite(Marcha1, 1);
  digitalWrite(Marcha2, 1);
  digitalWrite(Marcha3, 1);
  
  delay(2000);
  
  for (int i=0; i<=180;i++){
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
    delay(50);
  }
/*
  speedo.write(180);
  rpm.write(180);
  braketemp.write(175);
  brakeairpress.write(175);
  fuel.write(175);
  adblue.write(175);
  watertemp.write(175);
  oiltemp.write(175);
  batteryvolt.write(175);
  oilpress.write(175);  
*/
  digitalWrite(LEFT_INDICATOR, 0);
  digitalWrite(RIGHT_INDICATOR, 0);
  digitalWrite(LOW_BEAM, 0);
  digitalWrite(HIGH_BEAM, 0);
  digitalWrite(LIGHT_BRAKE,0);
  digitalWrite(PARKING_BRAKE, 0);
  digitalWrite(MOTOR_BRAKE, 0);
  digitalWrite(BRAKE_AIR_PRESSURE_WARNING, 0);
  digitalWrite(BRAKE_AIR_PRESSURE_EMERGENCY, 0);
  digitalWrite(FUEL_WARNING, 0);
  digitalWrite(ADBLUE_WARNING, 0);
  digitalWrite(BATTERY_VOLTAGE_WARNING, 0); 
  digitalWrite(OIL_PRESSURE_WARNING, 0); 
  digitalWrite(WATER_TEMPERATURE_WARNING, 0);
  digitalWrite(ELECTRIC_ENABLED, 0);
  digitalWrite(ENGINE_ENABLED, 0);
  digitalWrite(CRUISE_CONTROL, 0);
  digitalWrite(LIGHT_BEACON, 0);
  digitalWrite(BRAKE_TEMP_WARNING, 0);
  digitalWrite(OIL_TEMP_WARNING, 0);


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

  delay(1000);
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

void read_serial_byte_set_servo_fuel(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 5) ? 5 : ((serial_byte > 175) ? 175 : serial_byte);
  if (invert)
    servo.write(175 - serial_byte); //set lower than the tach and speedo to limit movement.
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

void digitalWriteFromBit(int port, int value, int shift)
{
  digitalWrite(port, (value >> shift) & 0x01);
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
//    lcd.clear();
 //   lcd.print("PROTOCOL VERSION ERROR");
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
      digitalWrite(BRAKE_TEMP_WARNING, 1);
    }    
    else
      {
        digitalWrite(BRAKE_TEMP_WARNING, 0);
      }

  // Truck lights byte
  serial_byte = Serial.read();
  digitalWriteFromBit(LIGHT_BEACON, serial_byte, 7);
  digitalWriteFromBit(LEFT_INDICATOR,  serial_byte, 5);  
  digitalWriteFromBit(RIGHT_INDICATOR, serial_byte, 4);
  digitalWriteFromBit(LOW_BEAM,  serial_byte, 3);  
  digitalWriteFromBit(HIGH_BEAM, serial_byte, 2);
  digitalWriteFromBit(LIGHT_BRAKE, serial_byte, 1);
  
  
  // Warning lights bytes

  serial_byte = Serial.read();  
  digitalWriteFromBit(PARKING_BRAKE, serial_byte, 7);
  digitalWriteFromBit(MOTOR_BRAKE, serial_byte, 6);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_WARNING, serial_byte, 5);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_EMERGENCY, serial_byte, 4);
  digitalWriteFromBit(FUEL_WARNING, serial_byte, 3);
  digitalWriteFromBit(BATTERY_VOLTAGE_WARNING, serial_byte, 2); 
  digitalWriteFromBit(OIL_PRESSURE_WARNING, serial_byte, 1); 
  digitalWriteFromBit(WATER_TEMPERATURE_WARNING, serial_byte, 0);

 
  // Enabled flags
  serial_byte = Serial.read();
  digitalWriteFromBit(ADBLUE_WARNING, serial_byte, 2);
  digitalWriteFromBit(ELECTRIC_ENABLED, serial_byte, 1);
  digitalWriteFromBit(ENGINE_ENABLED, serial_byte, 0);
 

  // Text length
  int text_len = Serial.read();
  
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

    }
  }
}


