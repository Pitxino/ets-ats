

#include <Adafruit_NeoPixel.h>
#include <SwitecX25.h>
//#include "TM1637_6D.h"
#include "TM1637.h"
//#include <TM1637TinyDisplay6.h>


// leds 1
const int ENGINE_ENABLED_LED        =  0;
const int BOCINA_LED                =  1;
const int BOCINA_AIRE_LED           =  2;
const int LIGHT_BEACON_LED          =  3;
const int LIGHT_HIGH_BEAM_LED       =  4;
const int LIGHT_LOW_BEAM_LED        =  5;
const int DESACOPLAR_REMOLQUE_LED   =  6;
const int LIMPIA_LENTO_LED          =  7;
const int LIMPIA_RAPIDO_LED         =  8;
// leds 2
const int OIL_PRESSURE_WARNING_LED  =  9;
const int BATTERY_VOLTAGE_WARNING_LED = 10;
const int OIL_TEMPERATURE_LED       = 11; //hay que calcularlo, no scs
const int FUEL_WARNING_LED          = 12;
const int LIGHT_LBLINKER_LED        = 13;
const int BRAKE_AIR_PRESSURE_EMERGENCY_LED = 14;
const int ADBLUE_WARNING_LED        = 15;
const int LIGHT_RBLINKER_LED        = 16;
const int BRAKE_AIR_PRESSURE_WARNING_LED = 17;
const int BRAKE_TEMPERATURE_LED     = 18; //hay que calcularlo, no scs
const int WATER_TEMPERATURE_WARNING_LED = 19;
// leds 3
const int PARKING_BRAKE_LED         =20;
const int DIFERENCIAL               =21;
const int AUMENTAR_RETARDER         =22;
const int MOTOR_BRAKE_LED           =23;
const int LIGHT_BRAKE_LED           =24;
const int DISMINUIR_RETARDER_LED    =25;
// leds 4
const int SUBIR_VENTANILLA_IZQUIERDA_LED =26;
const int SUBIR_VENTANILLA_DERECHA_LED   =27;
const int CAMBIAR_ORDENADOR_LED          =28;
const int CAMBIAR_GPS_LED                =29;
const int MAPA_LED                       =30;
const int LUCES_PELIGRO_LED              =31;
const int BAJAR_VENTANILLA_DERECHA_LED   =32;
const int BAJAR_VENTANILLA_IZQUIERDA_LED =33;
const int RAFAGA_LED                     =34;
const int CANCION_ANTERIOR_LED           =35;
const int CANCION_SIGUIENTE_LED          =36;
const int RADIO_LED                      =37;
const int CONTROL_CRUCERO_LED            =38;
const int VOLVER_CONTROL_CRUCERO_LED     =39;
const int SUBIR_EJE_CAMION_LED           =40;
const int SUBIR_EJE_TRAILER_LED          =41;
const int RAMPA_LED                      =42;
const int PUERTA_5_LED                   =43;
const int SUBIR_VELOCIDAD_CRUCERO_LED    =44;
const int BAJAR_VELOCIDAD_CRUCERO_LED    =45;
const int PUERTA_4_LED                   =46;
const int PUERTA_3_LED                   =47;
const int PUERTA_2_LED                   =48;
const int PUERTA_1_LED                   =49;

const int ELECTRIC_ENABLED               = 0; // switch encendido o apagado


/*// defines servo names
SwitecX25 rpm;
SwitecX25 speedo;
SwitecX25 oiltemp;
SwitecX25 batteryvolt;
SwitecX25 oilpress;
SwitecX25 fuel;
SwitecX25 adblue;
SwitecX25 watertemp;
SwitecX25 braketemp;
SwitecX25 brakeairpress;
SwitecX25 cruise;*/

#define PACKET_SYNC 0xFF
#define PACKET_VER  2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true

#define STEPS (255*3)
#define LUZ          2 // pin rele 
#define LEDS         3 // pin strip neopixel
#define NUMPIXELS   50 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, LEDS, NEO_GRB + NEO_KHZ800);

#define CLK 5 //pins definitions for TM1637 and can be changed to other ports
#define DIO 4
//TM1637_6D tm1637(CLK,DIO);
TM1637 tm1637(CLK,DIO);
//TM1637TinyDisplay6 display(CLK, DIO);

SwitecX25 rpm(STEPS,6,7,8,9);
SwitecX25 speedo(STEPS,10,11,12,13);
SwitecX25 oiltemp(STEPS,22,23,24,25);
SwitecX25 batteryvolt(STEPS,26,27,28,29);
SwitecX25 oilpress(STEPS,30,31,32,33);
SwitecX25 fuel(STEPS,34,35,36,37);
SwitecX25 adblue(STEPS,38,39,40,41);
SwitecX25 watertemp(STEPS,42,43,44,45);
SwitecX25 braketemp(STEPS,46,47,48,49);
SwitecX25 brakeairpress(STEPS,50,51,52,53);

const uint32_t rojo = pixels.Color(255, 0, 0);
const uint32_t verde = pixels.Color(0, 255, 0);
const uint32_t azul = pixels.Color(0, 0, 255);
const uint32_t amarillo = pixels.Color(255, 255, 0);
const uint32_t negro = pixels.Color(0, 0, 0);
const uint32_t blanco = pixels.Color(255, 255, 255);
const uint32_t morado = pixels.Color(127, 105, 255);


int serial_byte;
int resultado;
int cuentakilometros;
//char ODOMETER[6];



void setup()
{
  digitalWrite(LUZ,  HIGH);
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(255); // brillo de los led

  // inicizlizando pin LUZ salida
  pinMode(LUZ, OUTPUT);

  // inicializando 7 segmentos
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7; display.setBrightness(BRIGHT_HIGH);

  tm1637.display(2, 0);
  tm1637.display(1, 0);
  tm1637.display(0, 0);
  tm1637.display(5, 0);
  tm1637.display(4, 0);
  tm1637.display(3, 0);


  /*display.clear();
  display.showString("digits");
  delay(1000);
  display.showNumber(123456);
  delay(1000);
  display.showNumber(123.456);
  delay(1000);*/


  //inicializo los motores a cero
  rpm.zero();
  speedo.zero();
  oiltemp.zero();
  batteryvolt.zero();
  oilpress.zero();
  fuel.zero();
  adblue.zero();
  watertemp.zero();
  braketemp.zero();
  brakeairpress.zero();
  rpm.update();
  speedo.update();
  oiltemp.update();
  batteryvolt.update();
  oilpress.update();
  fuel.update();
  adblue.update();
  watertemp.update();
  braketemp.update();
  brakeairpress.update();

  // Initialise LEDs
  pixels.fill(blanco);
  pixels.show();
  
  delay(500);
  
/*  for (int s=0; s<STEPS;s++){
    rpm.setPosition(s);
    speedo.setPosition(s);
    oiltemp.setPosition(s);
    batteryvolt.setPosition(s);
    oilpress.setPosition(s);
    fuel.setPosition(s);
    adblue.setPosition(s);
    watertemp.setPosition(s);
    braketemp.setPosition(s);
    brakeairpress.setPosition(s);
    rpm.update();
    speedo.update();
    oiltemp.update();
    batteryvolt.update();
    oilpress.update();
    fuel.update();
    adblue.update();
    watertemp.update();
    braketemp.update();
    brakeairpress.update();
    delay(5);
  }*/
    rpm.setPosition(749);
    speedo.setPosition(749);
    oiltemp.setPosition(749);
    batteryvolt.setPosition(749);
    oilpress.setPosition(749);
    fuel.setPosition(749);
    adblue.setPosition(749);
    watertemp.setPosition(749);
    braketemp.setPosition(749);
    brakeairpress.setPosition(749);
    rpm.updateBlocking();
    speedo.updateBlocking();
    oiltemp.updateBlocking();
    batteryvolt.updateBlocking();
    oilpress.updateBlocking();
    fuel.updateBlocking();
    adblue.updateBlocking();
    watertemp.updateBlocking();
    braketemp.updateBlocking();
    brakeairpress.updateBlocking();
    delay(1000);




  delay(2000);
  
/*  for (int s=STEPS; s>0;s--){
    rpm.setPosition(s);
    speedo.setPosition(s);
    oiltemp.setPosition(s);
    batteryvolt.setPosition(s);
    oilpress.setPosition(s);
    fuel.setPosition(s);
    adblue.setPosition(s);
    watertemp.setPosition(s);
    braketemp.setPosition(s);
    brakeairpress.setPosition(s);
    rpm.update();
    speedo.update();
    oiltemp.update();
    batteryvolt.update();
    oilpress.update();
    fuel.update();
    adblue.update();
    watertemp.update();
    braketemp.update();
    brakeairpress.update();
    delay(5);
  }*/

  rpm.zero();
  speedo.zero();
  oiltemp.zero();
  batteryvolt.zero();
  oilpress.zero();
  fuel.zero();
  adblue.zero();
  watertemp.zero();
  braketemp.zero();
  brakeairpress.zero();
  rpm.update();
  speedo.update();
  oiltemp.update();
  batteryvolt.update();
  oilpress.update();
  fuel.update();
  adblue.update();
  watertemp.update();
  braketemp.update();
  brakeairpress.update();
  

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
  digitalWrite(LUZ,  LOW); 
// mostrar algo en 7 segmentos
  

}


void loop()
{
  speedo.update();
  rpm.update();
  brakeairpress.update();
  braketemp.update();
  fuel.update();
  oilpress.update();
  oiltemp.update();
  watertemp.update();
  batteryvolt.update();
  adblue.update();


  if (Serial.available() < 24)   
    return;
  
  serial_byte = Serial.read();
  if (serial_byte != PACKET_SYNC)
    return;
    
  serial_byte = Serial.read();
  if (serial_byte != PACKET_VER)
  {
    return;
  }




// movimiento motores

  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  speedo.setPosition(serial_byte*3);
  

  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  rpm.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  brakeairpress.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  braketemp.setPosition(serial_byte*3);

// luz temperatura frenos
  if (serial_byte > 230)  // braketemp lee el valor del servo y como es inverso hay que 
    pixels.setPixelColor(BRAKE_TEMPERATURE_LED, rojo);  
  else
    pixels.setPixelColor(BRAKE_TEMPERATURE_LED, negro);

  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  fuel.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  oilpress.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  oiltemp.setPosition(serial_byte*3);

// luz temperatura aceite
  if (serial_byte > 230)  // oiltemp lee el valor del servo y como es inverso hay que 
    pixels.setPixelColor(OIL_TEMPERATURE_LED, rojo);  
  else
    pixels.setPixelColor(OIL_TEMPERATURE_LED, negro);

  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  watertemp.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  batteryvolt.setPosition(serial_byte*3);


  serial_byte = Serial.read();// para leer control de crucero

  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  adblue.setPosition(serial_byte*3);



  speedo.update();
  rpm.update();
  brakeairpress.update();
  braketemp.update();
  fuel.update();
  oilpress.update();
  oiltemp.update();
  watertemp.update();
  batteryvolt.update();
  adblue.update();






/*read_serial_byte_set_servo(rpm, SERVO_DIR_INVERT); // RPM
  read_serial_byte_set_servo(speedo, SERVO_DIR_INVERT); // Speed  
  read_serial_byte_set_servo(oiltemp, SERVO_DIR_INVERT); // Oil temperature
  read_serial_byte_set_servo(batteryvolt, SERVO_DIR_INVERT); // Battery voltage
  read_serial_byte_set_servo(oilpress, SERVO_DIR_INVERT); // Oil pressure
  read_serial_byte_set_servo(fuel, SERVO_DIR_INVERT); // Fuel ratio
  read_serial_byte_set_servo(adblue, SERVO_DIR_INVERT); //adblue ratio
  read_serial_byte_set_servo(watertemp, SERVO_DIR_INVERT); // Water temperature
  read_serial_byte_set_servo(braketemp,SERVO_DIR_INVERT); // Brake temperature
  read_serial_byte_set_servo(brakeairpress,SERVO_DIR_INVERT); // Brake air pressure
  read_serial_byte_set_servo_cruise(cruise, SERVO_DIR_INVERT); // cruise speed, set to trip a light */ 


/*
  if (cruise.read() < 180)
      {
      digitalWrite(CRUISE_CONTROL, 1);
      }
  if (cruise.read() > 179)
      {
      digitalWrite(CRUISE_CONTROL, 0);
      }*/




  
  // Truck lights byte
  serial_byte = Serial.read();
  digitalWriteFromBit(LIGHT_BEACON_LED, serial_byte, 7, amarillo);
  digitalWriteFromBit(LIGHT_LBLINKER_LED,  serial_byte, 5, verde);  
  digitalWriteFromBit(LIGHT_RBLINKER_LED, serial_byte, 4, verde);
  digitalWriteFromBit(LIGHT_LOW_BEAM_LED,  serial_byte, 3, amarillo);  
  digitalWriteFromBit(LIGHT_HIGH_BEAM_LED, serial_byte, 2, azul);
  digitalWriteFromBit(LIGHT_BRAKE_LED, serial_byte, 1, rojo);

// luz encendido salpicadero
  if ((serial_byte >> 6) & 0x01)  // lee el valor de serial byte 6 y mira si esta activado para encender las luces
  { digitalWrite(LUZ,  HIGH);
    pixels.setPixelColor(1, blanco);
    pixels.setPixelColor(2, blanco);
    pixels.setPixelColor(22, blanco);
    pixels.setPixelColor(25, blanco);
    pixels.setPixelColor(26, blanco);
    pixels.setPixelColor(27, blanco);
    pixels.setPixelColor(28, blanco);
    pixels.setPixelColor(29, blanco);
    pixels.setPixelColor(30, blanco);
    pixels.setPixelColor(32, blanco);
    pixels.setPixelColor(33, blanco);
    pixels.setPixelColor(34, blanco);
    pixels.setPixelColor(35, blanco);
    pixels.setPixelColor(36, blanco);
    pixels.setPixelColor(37, blanco);
    pixels.setPixelColor(38, blanco);
    pixels.setPixelColor(39, blanco);
    pixels.setPixelColor(42, blanco);
    pixels.setPixelColor(43, blanco);
    pixels.setPixelColor(44, blanco);
    pixels.setPixelColor(45, blanco);
    pixels.setPixelColor(46, blanco);
    pixels.setPixelColor(47, blanco);
    pixels.setPixelColor(48, blanco);
    pixels.setPixelColor(49, blanco);
  }
  else  
  { digitalWrite(LUZ,  LOW); 
    pixels.setPixelColor(1, negro);
    pixels.setPixelColor(2, negro);
    pixels.setPixelColor(22, negro);
    pixels.setPixelColor(25, negro);
    pixels.setPixelColor(26, negro);
    pixels.setPixelColor(27, negro);
    pixels.setPixelColor(28, negro);
    pixels.setPixelColor(29, negro);
    pixels.setPixelColor(30, negro);
    pixels.setPixelColor(32, negro);
    pixels.setPixelColor(33, negro);
    pixels.setPixelColor(34, negro);
    pixels.setPixelColor(35, negro);
    pixels.setPixelColor(36, negro);
    pixels.setPixelColor(37, negro);
    pixels.setPixelColor(38, negro);
    pixels.setPixelColor(39, negro);
    pixels.setPixelColor(42, negro);
    pixels.setPixelColor(43, negro);
    pixels.setPixelColor(44, negro);
    pixels.setPixelColor(45, negro);
    pixels.setPixelColor(46, negro);
    pixels.setPixelColor(47, negro);
    pixels.setPixelColor(48, negro);
    pixels.setPixelColor(49, negro);
  }
   


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
  digitalWriteFromBit(DIFERENCIAL, serial_byte, 7, amarillo);
  digitalWriteFromBit(SUBIR_EJE_TRAILER_LED, serial_byte, 6, rojo);
  digitalWriteFromBit(SUBIR_EJE_CAMION_LED, serial_byte, 5, rojo);
  digitalWriteFromBit(LIMPIA_LENTO_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(LIMPIA_RAPIDO_LED, serial_byte, 3, amarillo);
  digitalWriteFromBit(ADBLUE_WARNING_LED, serial_byte, 2, amarillo);
  digitalWriteFromBit(ELECTRIC_ENABLED, serial_byte, 1, blanco);
  digitalWriteFromBit(ENGINE_ENABLED_LED, serial_byte, 0, verde);


  // Enabled flags
  serial_byte = Serial.read();
  digitalWriteFromBit(LUCES_PELIGRO_LED, serial_byte, 0, rojo);

// odometer
  tm1637.display(2, Serial.read());
  tm1637.display(1, Serial.read());
  tm1637.display(0, Serial.read());
  tm1637.display(5, Serial.read());
  tm1637.display(4, Serial.read());
  tm1637.display(3, Serial.read());

/*  display.setSegments(0, Serial.read());
  display.setSegments(1, Serial.read());
  display.setSegments(2, Serial.read());
  display.setSegments(3, Serial.read());
  display.setSegments(4, Serial.read());
  display.setSegments(5, Serial.read());*/

 /* // Text length
  int text_len = Serial.read();
  int digito[] = {2,1,0,5,4,3};
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
      if (serial_byte < 0 && serial_byte > 127)
        return;
      
      if (serial_byte != '\n')
        tm1637.display(digito[i], serial_byte);
//      delay(2);
    }
  }

  tm1637.display(2, ODOMETER[0]);
  tm1637.display(1, ODOMETER[1]);
  tm1637.display(0, ODOMETER[2]);
  tm1637.display(5, ODOMETER[3]);
  tm1637.display(4, ODOMETER[4]);
  tm1637.display(3, ODOMETER[5]);
  */
  /*tm1637.display(3, 0);
  tm1637.display(4, 1);
  tm1637.display(5, 2);
  tm1637.display(0, 3);
  tm1637.display(1, 4);
  tm1637.display(2, 6);*/


  // Text length
  //int text_len = Serial.read();
  
  pixels.show();




  speedo.update();
  rpm.update();
  brakeairpress.update();
  braketemp.update();
  fuel.update();
  oilpress.update();
  oiltemp.update();
  watertemp.update();
  batteryvolt.update();
  adblue.update();
}



/*
void read_serial_byte_set_servo(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  if (invert)
    SwitecX25.setPosition((250 - serial_byte)*3);
    SwitecX25.update();
  else
    SwitecX25.setPosition(serial_byte*3);
    SwitecX25.update();
}

void read_serial_byte_set_servo_cruise(Servo& servo, bool invert)
{
  serial_byte = Serial.read();
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 180) ? 180: serial_byte);
  if (invert)
    servo.write(180 - serial_byte); //set lower than the tach and speedo to limit movement.
  else
    servo.write(serial_byte);
}*/

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