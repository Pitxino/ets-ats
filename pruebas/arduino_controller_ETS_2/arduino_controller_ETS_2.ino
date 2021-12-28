#include <LiquidCrystal.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

//PINES SERVOS
const int OILTEMPERATURE_PIN  =2;
const int BATTERYVOLTAGE_PIN =3;  
const int OIL_PRESSURE_PIN = 4;
const int ENGINE_RPM_PIN   = 5;
const int ADBLUE_PIN =6;
const int FUEL_LED_PIN        = 7;
const int SPEED_PIN = 8;
const int WATERTEMPERATURE_PIN =9;
const int BRAKETEMPERATURE_PIN =10;
const int brakeairpress_PIN    =11;

//secuencial leds
const int ENGINE_ENABLED_LED        =  0;
const int BOCINA_LED                =  1;
const int BOCINA_AIRE_LED           =  2;
const int LIGHT_HIGH_BEAM_LED       =  3;
const int LIGHT_LOW_BEAM_LED        =  4;
const int LIGHT_BEACON_LED          =  5;
const int DESACOPLAR_REMOLQUE_LED   =  6;
const int LIMPIA_LENTO_LED          =  7;
const int LIMPIA_RAPIDO_LED         =  8;

const int LIGHT_RBLINKER_LED = 38;
const int LIGHT_LBLINKER_LED  = 15;
const int PARKING_BRAKE_LED   = 45;
const int BATTERY_VOLTAGE_WARNING_LED         = 11;
const int MOTOR_BRAKE_LED      = 47;
const int BRAKE_AIR_PRESSURE_WARNING_LED       = 44;
const int BRAKE_AIR_PRESSURE_EMERGENCY_LED  = 28;
const int LUZ_TABLERO       = 74;
const int OIL_PRESSURE_WARNING_LED    = 9;
const int FUEL_LED           = 16;



const int WATER_TEMPERATURE_WARNING_LED = 40;


// Servo variables
Servo oiltemperature;
Servo batteryvoltage;
Servo oilpress;
Servo rpm;
Servo adblue;
Servo fuel;
Servo speed;
Servo watertemperature;
Servo braketemperature;
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

void setup()
{
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
  // Initialise servos
  oiltemperature.attach(OILTEMPERATURE_PIN);
  oiltemperature.write(175);
  batteryvoltage.attach(BATTERYVOLTAGE_PIN);
  batteryvoltage.write(175);
  oilpress.attach(OIL_PRESSURE_PIN);
  oilpress.write(175);
  rpm.attach(ENGINE_RPM_PIN);
  rpm.write(175);
  adblue.attach(ADBLUE_PIN);
  adblue.write(175);
  fuel.attach(FUEL_LED_PIN);
  fuel.write(175);
  speed.attach(SPEED_PIN);
  speed.write(175);
  watertemperature.attach(WATERTEMPERATURE_PIN);
  watertemperature.write(175);
  braketemperature.attach(BRAKETEMPERATURE_PIN);
  braketemperature.write(175);
  brakeairpress.attach(brakeairpress_PIN);
  brakeairpress.write(175);


  // Initialise LEDs
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, blanco);
    pixels.show();
  }

  pixels.setPixelColor(LIGHT_LBLINKER_LED, verde);
  pixels.setPixelColor(LIGHT_RBLINKER_LED, verde);
  pixels.setPixelColor(PARKING_BRAKE_LED, rojo);
  pixels.setPixelColor(BATTERY_VOLTAGE_WARNING_LED, rojo);
  pixels.setPixelColor(LIGHT_HIGH_BEAM_LED, azul);
  pixels.setPixelColor(LUZ_TABLERO , blanco);
  pixels.setPixelColor(MOTOR_BRAKE_LED, rojo);
  pixels.setPixelColor(BRAKE_AIR_PRESSURE_WARNING_LED, rojo);
  pixels.setPixelColor(BRAKE_AIR_PRESSURE_EMERGENCY_LED, rojo);
  pixels.setPixelColor(OIL_PRESSURE_WARNING_LED, rojo);
  pixels.setPixelColor(LIGHT_LOW_BEAM_LED, amarillo);
  pixels.setPixelColor(FUEL_LED, amarillo);
  pixels.setPixelColor(WATER_TEMPERATURE_WARNING_LED, rojo);
  pixels.setPixelColor(ENGINE_ENABLED_LED, verde);
  pixels.setPixelColor(LIGHT_BEACON_LED, amarillo);

  pixels.show();
  delay(1000);
  
  oiltemperature.write(5);
  batteryvoltage.write(5);
  oilpress.write(5);
  rpm.write(5);
  adblue.write(5);
  fuel.write(5);
  speed.write(5);
  watertemperature.write(5);
  braketemperature.write(5);
  brakeairpress.write(5);
  delay(2000);
  
  oiltemperature.write(175);
  batteryvoltage.write(175);
  oilpress.write(175);
  rpm.write(175);
  adblue.write(175);
  fuel.write(175);
  speed.write(175);
  watertemperature.write(175);
  braketemperature.write(175);
  brakeairpress.write(175);

  pixels.clear();
  pixels.show();
}


void read_serial_byte_set_servo(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 5) ? 5 : ((serial_byte > 175) ? 175 : serial_byte);
  if (invert)
    servo.write(175 - serial_byte);
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
    return;
  }

  read_serial_byte_set_servo(speed, SERVO_DIR_INVERT); // speed  
  read_serial_byte_set_servo(rpm, SERVO_DIR_INVERT); // rpm
  read_serial_byte_set_servo(brakeairpress, SERVO_DIR_INVERT); //  Brake air pressure
  read_serial_byte_set_servo(braketemperature, SERVO_DIR_INVERT); // Brake temperature
  read_serial_byte_set_servo(fuel, SERVO_DIR_INVERT); // fuel
  read_serial_byte_set_servo(oilpress, SERVO_DIR_INVERT); // oilpress
  read_serial_byte_set_servo(oiltemperature,SERVO_DIR_INVERT); // Oil temperature
  read_serial_byte_set_servo(watertemperature,SERVO_DIR_INVERT); // Water temperature
  read_serial_byte_set_servo(batteryvoltage,SERVO_DIR_INVERT); // Battery voltage

    
  
  // Truck lights byte
  serial_byte = Serial.read();
  //digitalWriteFromBit(LIGHT_BEACON_LED, serial_byte, 7, amarillo);
  digitalWriteFromBit(LUZ_TABLERO , serial_byte, 6, azul);
  digitalWriteFromBit(LIGHT_LBLINKER_LED,  serial_byte, 5, verde);  
  digitalWriteFromBit(LIGHT_RBLINKER_LED, serial_byte, 4, verde);
  digitalWriteFromBit(LIGHT_LOW_BEAM_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(LIGHT_HIGH_BEAM_LED, serial_byte, 2, azul);
  digitalWriteFromBit(MOTOR_BRAKE_LED, serial_byte, 1, rojo);
  
  
  // Warning lights bytes

  serial_byte = Serial.read();  
  digitalWriteFromBit(PARKING_BRAKE_LED, serial_byte, 7, rojo);
  digitalWriteFromBit(MOTOR_BRAKE_LED, serial_byte, 6, rojo);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_WARNING_LED, serial_byte, 5, rojo);
  digitalWriteFromBit(BRAKE_AIR_PRESSURE_EMERGENCY_LED, serial_byte, 4, rojo);
  digitalWriteFromBit(FUEL_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(BATTERY_VOLTAGE_WARNING_LED, serial_byte, 2, rojo);
  digitalWriteFromBit(OIL_PRESSURE_WARNING_LED, serial_byte, 1, rojo);
  digitalWriteFromBit(WATER_TEMPERATURE_WARNING_LED, serial_byte, 0, rojo);  



  // Enabled flags
  serial_byte = Serial.read();
  digitalWriteFromBit(ENGINE_ENABLED_LED, serial_byte, 0, verde);  

 
  // Text length
  int text_len = Serial.read();

  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(10);
}

       
  
