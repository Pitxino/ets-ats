
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


// Servo variables
Servo oiltemperature;
Servo batteryvoltage;
Servo oilpressure;
Servo enginerpm;
Servo adblue;
Servo fuel;
Servo speed;
Servo watertemperature;
Servo braketemperature;
Servo brakeairpressure;


#define PACKET_SYNC 0xFF
#define PACKET_VER  2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true

int serial_byte;

#define PIN         6 
#define NUMPIXELS   75 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t rojo = pixels.Color(255, 0, 0);
const uint32_t verde = pixels.Color(0, 255, 0);
const uint32_t azul = pixels.Color(0, 0, 255);
const uint32_t amarillo = pixels.Color(255, 255, 0);
const uint32_t negro = pixels.Color(0, 0, 0);
const uint32_t blanco = pixels.Color(255, 255, 255);

void setup()
{
  Serial.begin(115200);

  for ()
  
  oiltemperature.attach(OIL_TEMPERATURE_PIN);
  oiltemperature.write(180);
  batteryvoltage.attach(BATTERY_VOLTAGE_PIN);
  batteryvoltage.write(180);
  oilpressure.attach(OIL_PRESSURE_PIN);
  oilpressure.write(180);
  enginerpm.attach(ENGINE_RPM_PIN);
  enginerpm.write(180);
  adblue.attach(ADBLUE_PIN);
  adblue.write(180);
  fuel.attach(FUEL_PIN);
  fuel.write(180);
  speed.attach(SPEED_PIN);
  speed.write(180);
  watertemperature.attach(WATER_TEMPERATURE_PIN);
  watertemperature.write(180);
  braketemperature.attach(BRAKE_TEMPERATURE_PIN);
  braketemperature.write(180);
  brakeairpressure.attach(BRAKE_AIR_PRESSURE_PIN);
  brakeairpressure.write(180);

  
// Initialise LEDs
/*pinMode(DIRECCIONALIZQUIERDA, OUTPUT);
  pinMode(DIRECCIONALDERECHA, OUTPUT);
  pinMode(FRENODEESTACIONAMIENTO, OUTPUT);
  pinMode(BATERIA, OUTPUT);
  pinMode(LUZ_ALTA, OUTPUT);
  pinMode(LUZ_TABLERO , OUTPUT);
  pinMode(FRENODEMOTOR, OUTPUT);
  pinMode(PRESSAOAR, OUTPUT);
  pinMode(PRESSAOAREMER, OUTPUT);
  pinMode(PRESSAOOLEO, OUTPUT);
  pinMode(LUZ_BAJA, OUTPUT);
  pinMode(FUEL, OUTPUT);
  
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinH, OUTPUT);
  pinMode(pinK, OUTPUT);
  pinMode(pinN, OUTPUT);
  pinMode(pinU, OUTPUT);
  pinMode(pinP, OUTPUT);
  pinMode(pinR, OUTPUT);
   
  pinMode(pinC1, OUTPUT);
  pinMode(pinD1, OUTPUT);
   
  pinMode(pinN1, OUTPUT);

//range-splitter LED's
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);

  digitalWrite(DIRECCIONALIZQUIERDA, 0);
  digitalWrite(DIRECCIONALDERECHA, 0);
  digitalWrite(FRENODEESTACIONAMIENTO, 0);
  digitalWrite(BATERIA, 0);
  digitalWrite(LUZ_ALTA, 0);
  digitalWrite(LUZ_TABLERO , 0);
  digitalWrite(FRENODEMOTOR, 0); 
  digitalWrite(PRESSAOAR, 0);
  digitalWrite(PRESSAOAREMER, 0);
  digitalWrite(PRESSAOOLEO, 0);
  digitalWrite(LUZ_BAJA, 0);
  digitalWrite(FUEL, 0);
  digitalWrite(FUEL, 0);
  digitalWrite(22, 0);
  digitalWrite(24, 0);
  digitalWrite(26, 0);
  digitalWrite(28, 0);
  digitalWrite(30, 0);
  digitalWrite(32, 0);

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, LOW);
  digitalWrite(pinP, LOW);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);*/
   



  delay(1000);
  
//  velosimetro.write(0);
//  tacometro.write(0);

oiltemperature.write(0);
batteryvoltage.write(0);
oilpressure.write(0);
enginerpm.write(0);
adblue.write(0);
fuel.write(0);
speed.write(0);
watertemperature.write(0);
braketemperature.write(0);
brakeairpressure.write(0);

/*
  digitalWrite(DIRECCIONALIZQUIERDA, 1);
  digitalWrite(DIRECCIONALDERECHA, 1);
  digitalWrite(FRENODEESTACIONAMIENTO, 1);
  digitalWrite(BATERIA, 1);
  digitalWrite(LUZ_ALTA, 1);
  digitalWrite(LUZ_TABLERO , 1);
  digitalWrite(FRENODEMOTOR, 1); 
  digitalWrite(PRESSAOAR, 1);
  digitalWrite(PRESSAOAREMER, 1);
  digitalWrite(PRESSAOOLEO, 1);
  digitalWrite(LUZ_BAJA, 1);
  digitalWrite(FUEL, 1);
  
  digitalWrite(22, 1);
  digitalWrite(24, 1);
  digitalWrite(26, 1);
  digitalWrite(28, 1);
  digitalWrite(30, 1);
  digitalWrite(32, 1);*/

  delay(2000);
  
//  velosimetro.write(180);
//  tacometro.write(180);


oiltemperature.write(180);
batteryvoltage.write(180);
oilpressure.write(180);
enginerpm.write(180);
adblue.write(180);
fuel.write(180);
speed.write(180);
watertemperature.write(180);
braketemperature.write(180);
brakeairpressure.write(180);



/*
  digitalWrite(DIRECCIONALIZQUIERDA, 0);
  digitalWrite(DIRECCIONALDERECHA, 0);
  digitalWrite(FRENODEESTACIONAMIENTO, 0);
  digitalWrite(BATERIA, 0);
  digitalWrite(LUZ_ALTA, 0);
  digitalWrite(LUZ_TABLERO , 0);
  digitalWrite(FRENODEMOTOR, 0); 
  digitalWrite(PRESSAOAR, 0);
  digitalWrite(PRESSAOAREMER, 0);
  digitalWrite(PRESSAOOLEO, 0);
  digitalWrite(LUZ_BAJA, 0);
  digitalWrite(FUEL, 0);
  
  digitalWrite(22, 0);
  digitalWrite(24, 0);
  digitalWrite(26, 0);
  digitalWrite(28, 0);
  digitalWrite(30, 0);
  digitalWrite(32, 0);*/
 
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

void digitalWriteFromBit(int port, int value, int shift)
{
  digitalWrite(port, (value >> shift) & 0x01);
}

void loop()
{
    
  if (Serial.available() < 19)
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

  read_serial_byte_set_servo(speed, SERVO_DIR_INVERT); // Velosimetro  
  read_serial_byte_set_servo(enginerpm, SERVO_DIR_INVERT); // Tacometro
  read_serial_byte_set_servo(brakeairpressure, SERVO_DIR_INVERT); //  Brake air pressure
  read_serial_byte_set_servo(braketemperature, SERVO_DIR_INVERT); // Brake temperature
  read_serial_byte_set_servo(fuel, SERVO_DIR_INVERT); // disel
  read_serial_byte_set_servo(oilpressure, SERVO_DIR_INVERT); // Preciondeaceite
  read_serial_byte_set_servo(oiltemperature,SERVO_DIR_INVERT); // Oil temperature
  read_serial_byte_set_servo(watertemperature,SERVO_DIR_INVERT); // Water temperature
  read_serial_byte_set_servo(batteryvoltage,SERVO_DIR_INVERT); // Battery voltage
  read_serial_byte_set_servo(adblue, SERVO_DIR_INVERT); // adblue
    
  
  // Truck lights byte
  serial_byte = Serial.read();
/*  digitalWriteFromBit(DIRECCIONALIZQUIERDA,  serial_byte, 5);  
  digitalWriteFromBit(DIRECCIONALDERECHA, serial_byte, 4);
  digitalWriteFromBit(LUZ_ALTA, serial_byte, 2);
  digitalWriteFromBit(LUZ_TABLERO , serial_byte, 6);
  digitalWriteFromBit(LUZ_BAJA, serial_byte, 3);
  digitalWriteFromBit(FRENODEMOTOR, serial_byte, 1);*/
  
  
  // Warning lights bytes

  serial_byte = Serial.read();  
/*  digitalWriteFromBit(PRESSAOOLEO, serial_byte, 1);
  digitalWriteFromBit(BATERIA, serial_byte, 2);
  digitalWriteFromBit(FUEL, serial_byte, 3);
  digitalWriteFromBit(PRESSAOAREMER, serial_byte, 5);
  digitalWriteFromBit(PRESSAOAR, serial_byte, 5);
  digitalWriteFromBit(FRENODEESTACIONAMIENTO, serial_byte, 7);*/


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
 //    delay(2);

 
            if (serial_byte == 'a')
       {
        //1
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, HIGH);
  digitalWrite(pinU, LOW);
  digitalWrite(pinP, LOW);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
else  if (serial_byte == 'b')
       {
        //2
   digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 'c')
       {
  //3
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
   else  if (serial_byte == 'd')
       {
  //4
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 'e')
       {
  //5
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
  
      }
       else  if (serial_byte == 'f')
       {
  //6
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 'g')
       {
  //7
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, LOW);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 'h')
       {
 //8
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 'i')
       {
  //9
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 'j')
       {
  //10
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, LOW);
  digitalWrite(pinP, LOW);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 'k')
       {
  //11
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, HIGH);
  digitalWrite(pinU, LOW);
  digitalWrite(pinP, LOW);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 'l')
       {
  //12
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 'm')
       {
  //13
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 'n')
       {
  //14
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
   
      }
       else  if (serial_byte == 'o')
       {
  //15
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 'p')
       {
  //16
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 'q')
       {
  //17
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinH, LOW);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, LOW);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 'r')
       {
  //18
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, LOW);
   
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinD1, HIGH);
   
  digitalWrite(pinN1, HIGH);
   
      }
       else  if (serial_byte == 's')
       {
  // R1
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, HIGH);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 't')
       {
  //R2
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, HIGH);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
      }
       else  if (serial_byte == 'u')
       {
  //R3
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, HIGH);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
    
   
      }
       else  if (serial_byte == 'v')
       {
  //R4
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, LOW);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, HIGH);
  digitalWrite(pinP, HIGH);
  digitalWrite(pinR, HIGH);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
 
   
      }
       else  if (serial_byte == 'w')
       {
  // Neutral
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  digitalWrite(pinH, HIGH);
  digitalWrite(pinK, HIGH);
  digitalWrite(pinN, LOW);
  digitalWrite(pinU, LOW);
  digitalWrite(pinP, LOW);
  digitalWrite(pinR, HIGH);
   
  digitalWrite(pinC1, LOW);
  digitalWrite(pinD1, LOW);
   
  digitalWrite(pinN1, LOW);
   
        }   


//sets range splitter LED's
  if (serial_byte == 'a' || serial_byte == 'g' || serial_byte == 'm' || serial_byte == 's')
{
  digitalWrite(22, 1);
}


else
{
    digitalWrite(22, 0);
}
  if (serial_byte == 'b' || serial_byte == 'h' || serial_byte == 'n' || serial_byte == 't')
{
  digitalWrite(24, 1);
}
else
{
    digitalWrite(24, 0);
}
  if (serial_byte == 'c' || serial_byte == 'i' || serial_byte == 'o' || serial_byte == 'u')
{
  digitalWrite(26, 1);
}
else
{
    digitalWrite(26, 0);






 if (serial_byte == 'd' || serial_byte == 'j' || serial_byte == 'p' || serial_byte == 'v')
{
  digitalWrite(28, 1);
}
else
{
    digitalWrite(28, 0);
}
  if (serial_byte == 'e' || serial_byte == 'k' || serial_byte == 'q')
{
  digitalWrite(30, 1);
}
else
{
    digitalWrite(30, 0);
}
  if (serial_byte == 'f' || serial_byte == 'l' || serial_byte == 'r')
{
  digitalWrite(32, 1);
}
else
{
    digitalWrite(32, 0); 
        
           }

          }
        }
      }
     }
