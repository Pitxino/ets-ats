/*
    Autor Pitxino
    programa para salpicadero arduino
*/

#include <Adafruit_NeoPixel.h>
#include <SwitecX25.h>
#include "TM1637.h"


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
TM1637 tm1637(CLK,DIO);

SwitecX25 speedo(STEPS,6,7,8,9);
SwitecX25 rpm(STEPS,10,11,12,13);
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

//variables para relojes
int serial_byte;
int resultado;
int cuentakilometros;
int contenido_oiltemp;
int contenido_batteryvolt;
int contenido_oilpress;
int contenido_rpm;
int contenido_fuel;
int contenido_speedo;
int contenido_adblue;
int contenido_watertemp;
int contenido_braketemp;
int contenido_brakeairpress;

// variables para luces
bool contenido_light_beacon_led;
bool contenido_light_parking_led;
bool contenido_light_lblinker_led;
bool contenido_light_rblinker_led;
bool contenido_light_low_beam_led;
bool contenido_light_High_beam_led;
bool contenido_light_brake_led;
bool contenido_light_reverse_led;

bool contenido_parking_brake_led;
bool contenido_motor_brake_led;
bool contenido_brake_air_pressure_warning_led;
bool contenido_brake_air_pressure_emergency_led;
bool contenido_fuel_warning_led;
bool contenido_battery_voltage_warning_led;
bool contenido_oil_pressure_warning_led;
bool contenido_water_temperature_warning_led; 

bool contenido_diferencial;
bool contenido_subir_eje_trailer_led;
bool contenido_subir_eje_camion_led;
bool contenido_dashboard_backlight;
bool contenido_wipers_led;
bool contenido_adblue_warning_led;
bool contenido_electric_enabled;
bool contenido_engine_enabled; 

bool contenido_luces_peligro_led;

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


  //inicializo los motores a cero
  oiltemp.zero();
  batteryvolt.zero();
  oilpress.zero();
  rpm.zero();
  fuel.zero();
  speedo.zero();
  adblue.zero();
  watertemp.zero();
  braketemp.zero();
  brakeairpress.zero();


  // Initialise LEDs
  pixels.fill(blanco);
  pixels.show();
  
  // delay(500);
  
    oiltemp.setPosition(749);
    oiltemp.updateBlocking();
    batteryvolt.setPosition(749);
    batteryvolt.updateBlocking();
    oilpress.setPosition(749);
    oilpress.updateBlocking();
    rpm.setPosition(749);
    rpm.updateBlocking();
    fuel.setPosition(749);
    fuel.updateBlocking();
    speedo.setPosition(749);
    speedo.updateBlocking();
    adblue.setPosition(749);
    adblue.updateBlocking();
    watertemp.setPosition(749);
    watertemp.updateBlocking();
    braketemp.setPosition(749);
    braketemp.updateBlocking();
    brakeairpress.setPosition(749);
    brakeairpress.updateBlocking();


  brakeairpress.zero();
  braketemp.zero();
  watertemp.zero();
  adblue.zero();
  speedo.zero();
  fuel.zero();
  rpm.zero();
  oilpress.zero();
  batteryvolt.zero();
  oiltemp.zero();


  

  pixels.fill(rojo);
  pixels.show();
  delay(500);
  pixels.fill(verde);
  pixels.show();
  delay(500);
  pixels.fill(azul);
  pixels.show();
  delay(500);
  pixels.fill(negro);
  pixels.show();
  digitalWrite(LUZ,  LOW); 
// mostrar algo en 7 segmentos
  for(int i = 0; i <= 9; i++)
  {
    tm1637.display(2, i);
    tm1637.display(1, i);
    tm1637.display(0, i);
    tm1637.display(5, i);
    tm1637.display(4, i);
    tm1637.display(3, i);
    delay(50);
  }   
  

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
  contenido_speedo = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  speedo.setPosition(serial_byte*3);
  

  serial_byte = Serial.read();
  contenido_rpm = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  rpm.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  contenido_brakeairpress = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  brakeairpress.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  contenido_braketemp = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  braketemp.setPosition(serial_byte*3);

// luz temperatura frenos
  if (contenido_braketemp > 230)  // braketemp lee el valor del servo y como es inverso hay que 
     pixels.setPixelColor(BRAKE_TEMPERATURE_LED, rojo);  
  else if (contenido_light_parking_led)
          pixels.setPixelColor(BRAKE_TEMPERATURE_LED, blanco);
        else
          pixels.setPixelColor(BRAKE_TEMPERATURE_LED, negro);

  serial_byte = Serial.read();
  contenido_fuel = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  fuel.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  contenido_oilpress = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  oilpress.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  contenido_oiltemp = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  oiltemp.setPosition(serial_byte*3);

// luz temperatura aceite
  if (contenido_oiltemp > 230)  // oiltemp lee el valor del servo y como es inverso hay que 
    pixels.setPixelColor(OIL_TEMPERATURE_LED, rojo);  
  else if (contenido_light_parking_led)
          pixels.setPixelColor(OIL_TEMPERATURE_LED, blanco);
       else
           pixels.setPixelColor(OIL_TEMPERATURE_LED, negro);  

  serial_byte = Serial.read();
  contenido_watertemp = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  watertemp.setPosition(serial_byte*3);


  serial_byte = Serial.read();
  contenido_batteryvolt = serial_byte;
  serial_byte = (serial_byte < 0) ? 0 : ((serial_byte > 250) ? 250 : serial_byte);
  batteryvolt.setPosition(serial_byte*3);


  serial_byte = Serial.read();// para leer control de crucero

  serial_byte = Serial.read();
  contenido_adblue = serial_byte;
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

  
  // Truck lights byte
  serial_byte = Serial.read();
  contenido_light_beacon_led = serial_byte >> 7;
  contenido_light_parking_led = serial_byte >> 6;
  contenido_light_lblinker_led = serial_byte >> 5;
  contenido_light_rblinker_led = serial_byte >> 4;
  contenido_light_low_beam_led = serial_byte >> 3;
  contenido_light_High_beam_led = serial_byte >> 2;
  contenido_light_brake_led = serial_byte >> 1;
  contenido_light_reverse_led = serial_byte >> 0;
  digitalWriteFromBit(LIGHT_BEACON_LED, serial_byte, 7, amarillo);
  digitalWriteFromBit(LIGHT_LBLINKER_LED,  serial_byte, 5, verde);  
  digitalWriteFromBit(LIGHT_RBLINKER_LED, serial_byte, 4, verde);
  digitalWriteFromBit(LIGHT_LOW_BEAM_LED,  serial_byte, 3, amarillo);  
  digitalWriteFromBit(LIGHT_HIGH_BEAM_LED, serial_byte, 2, azul);
  digitalWriteFromBit(LIGHT_BRAKE_LED, serial_byte, 1, rojo);

// luz encendido salpicadero
  if (contenido_light_parking_led)  // lee el valor de serial byte 6 y mira si esta activado para encender las luces
  { 
    digitalWrite(LUZ,  HIGH);
    pixels.setPixelColor(BOCINA_LED, blanco);
    pixels.setPixelColor(BOCINA_AIRE_LED, blanco);
    pixels.setPixelColor(DESACOPLAR_REMOLQUE_LED, blanco);
    pixels.setPixelColor(AUMENTAR_RETARDER, blanco);
    pixels.setPixelColor(DISMINUIR_RETARDER_LED, blanco);
    pixels.setPixelColor(SUBIR_VENTANILLA_IZQUIERDA_LED, blanco);
    pixels.setPixelColor(SUBIR_VENTANILLA_DERECHA_LED, blanco);
    pixels.setPixelColor(CAMBIAR_ORDENADOR_LED, blanco);
    pixels.setPixelColor(CAMBIAR_GPS_LED, blanco);
    pixels.setPixelColor(MAPA_LED, blanco);
    pixels.setPixelColor(BAJAR_VENTANILLA_DERECHA_LED, blanco);
    pixels.setPixelColor(BAJAR_VENTANILLA_IZQUIERDA_LED, blanco);
    pixels.setPixelColor(RAFAGA_LED, blanco);
    pixels.setPixelColor(CANCION_ANTERIOR_LED, blanco);
    pixels.setPixelColor(CANCION_SIGUIENTE_LED, blanco);
    pixels.setPixelColor(RADIO_LED, blanco);
    pixels.setPixelColor(CONTROL_CRUCERO_LED, blanco);
    pixels.setPixelColor(VOLVER_CONTROL_CRUCERO_LED, blanco);
    pixels.setPixelColor(RAMPA_LED, blanco);
    pixels.setPixelColor(PUERTA_5_LED, blanco);
    pixels.setPixelColor(SUBIR_VELOCIDAD_CRUCERO_LED, blanco);
    pixels.setPixelColor(BAJAR_VELOCIDAD_CRUCERO_LED, blanco);
    pixels.setPixelColor(PUERTA_4_LED, blanco);
    pixels.setPixelColor(PUERTA_3_LED, blanco);
    pixels.setPixelColor(PUERTA_2_LED, blanco);
    pixels.setPixelColor(PUERTA_1_LED, blanco);
  }
  else  
  { 
    digitalWrite(LUZ,  LOW); 
    pixels.setPixelColor(BOCINA_LED, negro);
    pixels.setPixelColor(BOCINA_AIRE_LED, negro);
    pixels.setPixelColor(DESACOPLAR_REMOLQUE_LED, negro);
    pixels.setPixelColor(AUMENTAR_RETARDER, negro);
    pixels.setPixelColor(DISMINUIR_RETARDER_LED, negro);
    pixels.setPixelColor(SUBIR_VENTANILLA_IZQUIERDA_LED, negro);
    pixels.setPixelColor(SUBIR_VENTANILLA_DERECHA_LED, negro);
    pixels.setPixelColor(CAMBIAR_ORDENADOR_LED, negro);
    pixels.setPixelColor(CAMBIAR_GPS_LED, negro);
    pixels.setPixelColor(MAPA_LED, negro);
    pixels.setPixelColor(BAJAR_VENTANILLA_DERECHA_LED, negro);
    pixels.setPixelColor(BAJAR_VENTANILLA_IZQUIERDA_LED, negro);
    pixels.setPixelColor(RAFAGA_LED, negro);
    pixels.setPixelColor(CANCION_ANTERIOR_LED, negro);
    pixels.setPixelColor(CANCION_SIGUIENTE_LED, negro);
    pixels.setPixelColor(RADIO_LED, negro);
    pixels.setPixelColor(CONTROL_CRUCERO_LED, negro);
    pixels.setPixelColor(VOLVER_CONTROL_CRUCERO_LED, negro);
    pixels.setPixelColor(RAMPA_LED, negro);
    pixels.setPixelColor(PUERTA_5_LED, negro);
    pixels.setPixelColor(SUBIR_VELOCIDAD_CRUCERO_LED, negro);
    pixels.setPixelColor(BAJAR_VELOCIDAD_CRUCERO_LED, negro);
    pixels.setPixelColor(PUERTA_4_LED, negro);
    pixels.setPixelColor(PUERTA_3_LED, negro);
    pixels.setPixelColor(PUERTA_2_LED, negro);
    pixels.setPixelColor(PUERTA_1_LED, negro);
  }
 
   


  // Warning lights bytes

  serial_byte = Serial.read();
  contenido_parking_brake_led = serial_byte >> 7;
  contenido_motor_brake_led = serial_byte >> 6;
  contenido_brake_air_pressure_warning_led = serial_byte >> 5;
  contenido_brake_air_pressure_emergency_led = serial_byte >> 4;
  contenido_fuel_warning_led = serial_byte >> 3;
  contenido_battery_voltage_warning_led = serial_byte >> 2;
  contenido_oil_pressure_warning_led = serial_byte >> 1;
  contenido_water_temperature_warning_led = serial_byte >> 0;    
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
  contenido_diferencial = serial_byte >> 7;
  contenido_subir_eje_trailer_led = serial_byte >> 6;
  contenido_subir_eje_camion_led = serial_byte >> 5;
  contenido_dashboard_backlight = serial_byte >> 4;
  contenido_wipers_led = serial_byte >> 3;
  contenido_adblue_warning_led = serial_byte >> 2;
  contenido_electric_enabled = serial_byte >> 1;
  contenido_engine_enabled = serial_byte >> 0; 
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
  contenido_luces_peligro_led = serial_byte >> 0; 
  if (contenido_light_lblinker_led and contenido_light_rblinker_led)
     digitalWriteFromBit(LUCES_PELIGRO_LED, serial_byte, 0, rojo);
  else if (contenido_light_parking_led)
         {
            pixels.setPixelColor(LUCES_PELIGRO_LED, azul);
            pixels.show();
         }  
       else
          {
            pixels.setPixelColor(LUCES_PELIGRO_LED, negro);  
            pixels.show();
          }


// odometer
  tm1637.display(2, Serial.read());
  tm1637.display(1, Serial.read());
  tm1637.display(0, Serial.read());
  tm1637.display(5, Serial.read());
  tm1637.display(4, Serial.read());
  tm1637.display(3, Serial.read());

  
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




void skip_serial_byte()
{
  (void)Serial.read();
}


void digitalWriteFromBit(int port, int value, int shift, uint32_t color)
{
  if ((value >> shift) & 0x01)
    {
    pixels.setPixelColor(port, color);
    }
  else if (contenido_light_parking_led)
          {
          pixels.setPixelColor(port, blanco);
          }
       else 
          {
          pixels.setPixelColor(port, negro);
          }
}
