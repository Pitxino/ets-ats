#include <LiquidCrystal.h>
#include <Servo.h>

const int TACOMETRO_PIN   = 12;
const int VELOSIMETRO_PIN = 13;
const int PRECIONDEACEITE_PIN = A2;
const int DISEL_PIN        = 11;
const int DIRECCIONALDERECHA = A4;
const int DIRECCIONALIZQUIERDA  = A3;
const int FRENODEESTACIONAMIENTO   = A6;
const int BATERIA         = A7;
const int LUZ_ALTA        = A8;
const int LUZ_BAJA      = A9;
const int FRENODEMOTOR      = A10;
const int PRESSAOAR       = A11;
const int PRESSAOAREMER  = A14;
const int LUZ_TABLERO       = A13;
const int PRESSAOOLEO    = A12;
const int FUEL           = A15;
const int BRAKEAIR_PIN    =2;
const int BRAKETEMPERATURE_PIN =3;
const int OILTEMPERATURE_PIN  =4;
const int WATERTEMPERATURE_PIN =10;
const int BATTERYVOLTAGE_PIN =6;  

int pinA = 43;
int pinB = 45;
int pinC = 47;
int pinD = 49;
int pinE = 51;
int pinF = 53;
int pinG = 52;
int pinH = 50;
int pinK = 48;
int pinN = 46;
int pinU = 44;
int pinP = 42;
int pinR = 40;
 
int pinC1 = 16;
int pinD1 = 17;
 
int pinN1 = 15;
 
// Servo variables
Servo velosimetro;
Servo tacometro;
Servo preciondeaceite;
Servo disel;
Servo brakeair;
Servo braketemperature;
Servo oiltemperature;
Servo watertemperature;
Servo batteryvoltage;


#define PACKET_SYNC 0xFF
#define PACKET_VER  2

#define SERVO_DIR_NORMAL false
#define SERVO_DIR_INVERT true

int serial_byte;

LiquidCrystal lcd(31, 33, 35, 37, 39, 41);

void setup()
{
  Serial.begin(115200);
  
  // Initialise servos
  velosimetro.attach(VELOSIMETRO_PIN);
  velosimetro.write(180);
  
  tacometro.attach(TACOMETRO_PIN);
  tacometro.write(180);

  preciondeaceite.attach(PRECIONDEACEITE_PIN);
  preciondeaceite.write(75);
  
  disel.attach(DISEL_PIN);
  disel.write(75);

  brakeair.attach(BRAKEAIR_PIN);
  brakeair.write(75);

  braketemperature.attach(BRAKETEMPERATURE_PIN);
  braketemperature.write(75);

  oiltemperature.attach(OILTEMPERATURE_PIN);
  oiltemperature.write(75);

  watertemperature.attach(WATERTEMPERATURE_PIN);
  watertemperature.write(75);

  batteryvoltage.attach(BATTERYVOLTAGE_PIN);
  batteryvoltage.write(75);


  
  // Initialise LEDs
  pinMode(DIRECCIONALIZQUIERDA, OUTPUT);
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
   
  digitalWrite(pinN1, LOW);
   



  delay(1000);
  
  velosimetro.write(0);
  tacometro.write(0);

  
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
  digitalWrite(32, 1);

  delay(2000);
  
  velosimetro.write(180);
  tacometro.write(180);


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
  digitalWrite(32, 0);
 
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

  read_serial_byte_set_servo(velosimetro, SERVO_DIR_INVERT); // Velosimetro  
  read_serial_byte_set_servo(tacometro, SERVO_DIR_INVERT); // Tacometro
  read_serial_byte_set_servo(brakeair, SERVO_DIR_INVERT); //  Brake air pressure
  read_serial_byte_set_servo(braketemperature, SERVO_DIR_INVERT); // Brake temperature
  read_serial_byte_set_servo(disel, SERVO_DIR_INVERT); // disel
  read_serial_byte_set_servo(preciondeaceite, SERVO_DIR_INVERT); // Preciondeaceite
  read_serial_byte_set_servo(oiltemperature,SERVO_DIR_INVERT); // Oil temperature
  read_serial_byte_set_servo(watertemperature,SERVO_DIR_INVERT); // Water temperature
  read_serial_byte_set_servo(batteryvoltage,SERVO_DIR_INVERT); // Battery voltage
    
  
  // Truck lights byte
  serial_byte = Serial.read();
  digitalWriteFromBit(DIRECCIONALIZQUIERDA,  serial_byte, 5);  
  digitalWriteFromBit(DIRECCIONALDERECHA, serial_byte, 4);
  digitalWriteFromBit(LUZ_ALTA, serial_byte, 2);
  digitalWriteFromBit(LUZ_TABLERO , serial_byte, 6);
  digitalWriteFromBit(LUZ_BAJA, serial_byte, 3);
  digitalWriteFromBit(FRENODEMOTOR, serial_byte, 1);
  
  
  // Warning lights bytes

  serial_byte = Serial.read();  
  digitalWriteFromBit(PRESSAOOLEO, serial_byte, 1);
  digitalWriteFromBit(BATERIA, serial_byte, 2);
  digitalWriteFromBit(FUEL, serial_byte, 3);
  digitalWriteFromBit(PRESSAOAREMER, serial_byte, 5);
  digitalWriteFromBit(PRESSAOAR, serial_byte, 5);
  digitalWriteFromBit(FRENODEESTACIONAMIENTO, serial_byte, 7);


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
       
   
  
       









































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































