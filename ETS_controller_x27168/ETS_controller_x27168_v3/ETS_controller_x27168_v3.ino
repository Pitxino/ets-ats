/*
    Autor: Pitxino
    Programa para salpicadero Arduino
*/

// -----------------------------------------------------------------
// Inclusión de librerías necesarias
#include <Adafruit_NeoPixel.h>
#include <SwitecX25.h>
#include "TM1637.h"

// -----------------------------------------------------------------
// Definiciones de LEDs según la numeración original
// Grupo 1
#define ENGINE_ENABLED_LED          0    // LED indicador de motor encendido
#define BOCINA_LED                  1    // Bocina (no se usa en este ejemplo)
#define BOCINA_AIRE_LED             2    // Se usará para light_reverse
#define LIGHT_BEACON_LED            3    // Luz de baliza
#define LIGHT_HIGH_BEAM_LED         4    // Luz alta
#define LIGHT_LOW_BEAM_LED          5    // Luz baja
#define DESACOPLAR_REMOLQUE_LED     6    // Indicador para desacoplar remolque
#define LIMPIA_LENTO_LED            7    // Limpiaparabrisas lento
#define LIMPIA_RAPIDO_LED           8    // Limpiaparabrisas rápido

// Grupo 2
#define OIL_PRESSURE_WARNING_LED    9    // Alerta de presión de aceite
#define BATTERY_VOLTAGE_WARNING_LED 10   // Alerta de voltaje de batería
#define OIL_TEMPERATURE_LED         11   // Alerta de temperatura del aceite
#define FUEL_WARNING_LED            12   // Alerta de combustible
#define LIGHT_LBLINKER_LED          13   // Intermitente izquierdo
#define BRAKE_AIR_PRESSURE_EMERGENCY_LED 14  // Peligro: presión de aire en frenos
#define ADBLUE_WARNING_LED          15   // Alerta de AdBlue
#define LIGHT_RBLINKER_LED          16   // Intermitente derecho
#define BRAKE_AIR_PRESSURE_WARNING_LED 17 // Alerta de presión de aire en frenos
#define BRAKE_TEMPERATURE_LED       18   // Alerta de temperatura de frenos
#define WATER_TEMPERATURE_WARNING_LED 19 // Alerta de temperatura del agua

// Grupo 3
#define PARKING_BRAKE_LED           20   // LED freno estacionamiento
#define DIFERENCIAL                 21   // LED diferencial
#define AUMENTAR_RETARDER           22   // LED aumentar retarder
#define MOTOR_BRAKE_LED             23   // LED freno motor
#define LIGHT_BRAKE_LED             24   // LED luz de freno
#define DISMINUIR_RETARDER_LED      25   // LED disminuir retarder

// Grupo 4
#define SUBIR_VENTANILLA_IZQUIERDA_LED 26 // LED subir ventanilla izquierda
#define SUBIR_VENTANILLA_DERECHA_LED   27 // LED subir ventanilla derecha
#define CAMBIAR_ORDENADOR_LED          28 // LED cambiar ordenador
#define CAMBIAR_GPS_LED                29 // LED cambiar GPS
#define MAPA_LED                       30 // LED mapa
#define LUCES_PELIGRO_LED              31 // LED luces de peligro
#define BAJAR_VENTANILLA_DERECHA_LED   32 // LED bajar ventanilla derecha
#define BAJAR_VENTANILLA_IZQUIERDA_LED 33 // LED bajar ventanilla izquierda
#define RAFAGA_LED                     34 // LED rafaga largas
#define CANCION_ANTERIOR_LED           35 // LED canción anterior
#define CANCION_SIGUIENTE_LED          36 // LED canción siguiente
#define RADIO_LED                      37 // LED radio
#define CONTROL_CRUCERO_LED            38 // LED control crucero
#define VOLVER_CONTROL_CRUCERO_LED     39 // LED rearmar control crucero
#define SUBIR_EJE_CAMION_LED           40 // LED subir eje camión
#define SUBIR_EJE_TRAILER_LED          41 // LED subir eje trailer
#define RAMPA_LED                      42 // LED rampa
#define PUERTA_5_LED                   43 // LED puerta 5
#define SUBIR_VELOCIDAD_CRUCERO_LED    44 // LED subir velocidad crucero
#define BAJAR_VELOCIDAD_CRUCERO_LED    45 // LED bajar velocidad crucero
#define PUERTA_4_LED                   46 // LED puerta 4
#define PUERTA_3_LED                   47 // LED puerta 3
#define PUERTA_2_LED                   48 // LED puerta 2
#define PUERTA_1_LED                   49 // LED puerta 1

// -----------------------------------------------------------------
// Configuración de motores (10 motores)
// Se define el número de motores y se crea un arreglo de objetos SwitecX25.
// Cada motor se configura con 750 pasos y los pines correspondientes.
#define MOTOR_COUNT 10
SwitecX25 motors[MOTOR_COUNT] = {
  SwitecX25(750, 6, 7, 8, 9),     
  SwitecX25(750, 10, 11, 12, 13),  
  SwitecX25(750, 22, 23, 24, 25),  
  SwitecX25(750, 26, 27, 28, 29),  
  SwitecX25(750, 30, 31, 32, 33),  
  SwitecX25(750, 34, 35, 36, 37),  
  SwitecX25(750, 38, 39, 40, 41),  
  SwitecX25(750, 42, 43, 44, 45),  
  SwitecX25(750, 46, 47, 48, 49),  
  SwitecX25(750, 50, 51, 52, 53)   
};

// -----------------------------------------------------------------
// Configuración del display TM1637 (7 segmentos)
// Se crea un objeto TM1637 usando los pines 5 (CLK) y 4 (DIO)
TM1637 tm1637(5, 4);

// -----------------------------------------------------------------
// Configuración de la tira de LEDs direccionables (NeoPixel)
// Se crea un objeto Adafruit_NeoPixel para 50 LEDs en el pin 3.
Adafruit_NeoPixel pixels(50, 3, NEO_GRB + NEO_KHZ800);

// -----------------------------------------------------------------
// Pin del relé que controla los LEDs SMD (por ejemplo, luces de parking)
const int LUZ_PIN = 2;

// -----------------------------------------------------------------
// Variables para la recepción del paquete serial
// El paquete tiene un tamaño fijo de 54 bytes:
// 2 bytes de cabecera + 12 floats (12 x 4 = 48 bytes) + 4 bytes booleanos.
#define PACKET_BUFFER_SIZE 100
static byte packetBuffer[PACKET_BUFFER_SIZE];
static int bufferIdx = 0;
static int expectedLength = 54;

// -----------------------------------------------------------------
// Estructura para almacenar el estado de telemetría recibido
struct TelemetryData {
  float speed;
  float engine_rpm;
  float brake_air_pressure;
  float brake_temperature;
  float fuel_ratio;
  float oil_pressure;
  float oil_temperature;
  float water_temperature;
  float battery_voltage;
  float cruise_control;
  float adblue_ratio;
  float odometer;
  byte boolGroup1;
  byte boolGroup2;
  byte boolGroup3;
  byte boolGroup4;
};

// Variable global para el estado actual
TelemetryData currentState;


// -----------------------------------------------------------------
// Función para procesar el paquete y almacenar los datos en currentState
void processPacketBuffered(byte* packet, int length) {
  currentState.speed            = readFloat(&packet[2]);
  currentState.engine_rpm       = readFloat(&packet[6]);
  currentState.brake_air_pressure = readFloat(&packet[10]);
  currentState.brake_temperature  = readFloat(&packet[14]);
  currentState.fuel_ratio        = readFloat(&packet[18]);
  currentState.oil_pressure      = readFloat(&packet[22]);
  currentState.oil_temperature   = readFloat(&packet[26]);
  currentState.water_temperature = readFloat(&packet[30]);
  currentState.battery_voltage   = readFloat(&packet[34]);
  currentState.cruise_control    = readFloat(&packet[38]);
  currentState.adblue_ratio      = readFloat(&packet[42]);
  currentState.odometer          = readFloat(&packet[46]);
  
  currentState.boolGroup1 = packet[50];
  currentState.boolGroup2 = packet[51];
  currentState.boolGroup3 = packet[52];
  currentState.boolGroup4 = packet[53];
}

// -----------------------------------------------------------------
// Función para actualizar salidas (motores, display, LEDs) en base a currentState.
void updateOutputs() {
  // Determinar si la electrónica está habilitada (bit 1 de boolGroup3)
  bool systemEnabled = ((currentState.boolGroup3 >> 1) & 0x01) != 0;
  
  // Se leen las señales críticas: de boolGroup1 (bits 6, 5 y 4) y de boolGroup4 (bit 0)
  bool criticalBlinkers = (((currentState.boolGroup1 >> 6) & 0x01) ||
                           ((currentState.boolGroup1 >> 5) & 0x01) ||
                           ((currentState.boolGroup1 >> 4) & 0x01));
  bool criticalHazard = ((currentState.boolGroup4 & 0x01) != 0);
  bool criticalActive = criticalBlinkers || criticalHazard;
  
  // Si la electrónica no está habilitada y no hay señales críticas, se apaga todo.
  if (!systemEnabled && !criticalActive) {
    systemShutdown();
  } else {
    // Si el sistema está habilitado, se actualizan motores y display
    if (systemEnabled) {
      setMotor(0, currentState.speed, 150);
      setMotor(1, currentState.engine_rpm, 3000);
      setMotor(2, currentState.brake_air_pressure, 150);
      setMotor(3, currentState.brake_temperature, 150);
      setMotor(4, currentState.fuel_ratio * 100, 100);
      setMotor(5, currentState.oil_pressure, 150);
      setMotor(6, currentState.oil_temperature, 150);
      setMotor(7, currentState.water_temperature, 150);
      setMotor(8, currentState.battery_voltage - 8, 10);
      setMotor(9, currentState.adblue_ratio * 100, 100);
      
      unsigned long odo_int = static_cast<unsigned long>(currentState.odometer) % 1000000;
      char formatted[7];
      sprintf(formatted, "%06lu", odo_int);
      // Actualización del display según cableado:
      tm1637.display(2, formatted[5] - '0'); // Dígito 6
      tm1637.display(1, formatted[4] - '0'); // Dígito 5
      tm1637.display(0, formatted[3] - '0'); // Dígito 4
      tm1637.display(5, formatted[2] - '0'); // Dígito 3
      tm1637.display(4, formatted[1] - '0'); // Dígito 2
      tm1637.display(3, formatted[0] - '0'); // Dígito 1
    } else {
      // Si el sistema no está habilitado, se fuerza el display a 0
      for (int i = 0; i < 6; i++) {
        tm1637.display(i, 0);
      }
    }
    
    // Actualización de LEDs:
    // Actualización crítica: blinkers y hazard se muestran siempre
    if ((currentState.boolGroup1 >> 5) & 0x01) {
      pixels.setPixelColor(LIGHT_LBLINKER_LED, 0x00FF00);
    } else {
      pixels.setPixelColor(LIGHT_LBLINKER_LED, 0);
    }
    if ((currentState.boolGroup1 >> 4) & 0x01) {
      pixels.setPixelColor(LIGHT_RBLINKER_LED, 0x00FF00);
    } else {
      pixels.setPixelColor(LIGHT_RBLINKER_LED, 0);
    }
    if (currentState.boolGroup4 & 0x01) {
      pixels.setPixelColor(LUCES_PELIGRO_LED, 0xFF0000);
    } else {
      pixels.setPixelColor(LUCES_PELIGRO_LED, 0);
    }
    
    // Para el resto de los LEDs, se actualizan solo si el sistema está habilitado.
    if (systemEnabled) {
      if ((currentState.boolGroup1 >> 7) & 0x01) pixels.setPixelColor(LIGHT_BEACON_LED, 0xFFFF00); else pixels.setPixelColor(LIGHT_BEACON_LED, 0);
      digitalWrite(LUZ_PIN, (currentState.boolGroup1 >> 6) & 0x01);
      if ((currentState.boolGroup1 >> 3) & 0x01) pixels.setPixelColor(LIGHT_LOW_BEAM_LED, 0xFFFF00); else pixels.setPixelColor(LIGHT_LOW_BEAM_LED, 0);
      if ((currentState.boolGroup1 >> 2) & 0x01) pixels.setPixelColor(LIGHT_HIGH_BEAM_LED, 0x0000FF); else pixels.setPixelColor(LIGHT_HIGH_BEAM_LED, 0);
      if ((currentState.boolGroup1 >> 1) & 0x01) pixels.setPixelColor(LIGHT_BRAKE_LED, 0xFF0000); else pixels.setPixelColor(LIGHT_BRAKE_LED, 0);
      if ((currentState.boolGroup1 >> 0) & 0x01) pixels.setPixelColor(BOCINA_AIRE_LED, 0xAAAAAA); else pixels.setPixelColor(BOCINA_AIRE_LED, 0);
      
      if ((currentState.boolGroup2 >> 7) & 0x01) pixels.setPixelColor(PARKING_BRAKE_LED, 0xFF0000); else pixels.setPixelColor(PARKING_BRAKE_LED, 0);
      if ((currentState.boolGroup2 >> 6) & 0x01) pixels.setPixelColor(MOTOR_BRAKE_LED, 0xFF0000); else pixels.setPixelColor(MOTOR_BRAKE_LED, 0);
      if ((currentState.boolGroup2 >> 5) & 0x01) pixels.setPixelColor(BRAKE_AIR_PRESSURE_WARNING_LED, 0xFF0000); else pixels.setPixelColor(BRAKE_AIR_PRESSURE_WARNING_LED, 0);
      if ((currentState.boolGroup2 >> 4) & 0x01) pixels.setPixelColor(BRAKE_AIR_PRESSURE_EMERGENCY_LED, 0xFF0000); else pixels.setPixelColor(BRAKE_AIR_PRESSURE_EMERGENCY_LED, 0);
      if ((currentState.boolGroup2 >> 3) & 0x01) pixels.setPixelColor(FUEL_WARNING_LED, 0xFFFF00); else pixels.setPixelColor(FUEL_WARNING_LED, 0);
      if ((currentState.boolGroup2 >> 2) & 0x01) pixels.setPixelColor(BATTERY_VOLTAGE_WARNING_LED, 0xFF0000); else pixels.setPixelColor(BATTERY_VOLTAGE_WARNING_LED, 0);
      if ((currentState.boolGroup2 >> 1) & 0x01) pixels.setPixelColor(OIL_PRESSURE_WARNING_LED, 0xFF0000); else pixels.setPixelColor(OIL_PRESSURE_WARNING_LED, 0);
      if ((currentState.boolGroup2 >> 0) & 0x01) pixels.setPixelColor(WATER_TEMPERATURE_WARNING_LED, 0xFF0000); else pixels.setPixelColor(WATER_TEMPERATURE_WARNING_LED, 0);
    }
    
    pixels.show();
  }
}

// -----------------------------------------------------------------
// Función readFloat: Copia 4 bytes de memoria e interpreta el resultado como float.
float readFloat(byte* data) {
  float value;
  memcpy(&value, data, sizeof(float));
  return value;
}

// -----------------------------------------------------------------
// Función setMotor: Mapea un valor (0 a 'max') a 0-750 pasos y asigna esa posición al motor.
void setMotor(int index, float value, float max) {
  int steps = map(value, 0, max, 0, 750);
  motors[index].setPosition(steps);
}

// -----------------------------------------------------------------
// Función processPacketBuffered: Procesa el paquete recibido y almacena el estado en currentState.
void processPacket(byte* packet, int length) {
  currentState.speed            = readFloat(&packet[2]);
  currentState.engine_rpm       = readFloat(&packet[6]);
  currentState.brake_air_pressure = readFloat(&packet[10]);
  currentState.brake_temperature  = readFloat(&packet[14]);
  currentState.fuel_ratio        = readFloat(&packet[18]);
  currentState.oil_pressure      = readFloat(&packet[22]);
  currentState.oil_temperature   = readFloat(&packet[26]);
  currentState.water_temperature = readFloat(&packet[30]);
  currentState.battery_voltage   = readFloat(&packet[34]);
  currentState.cruise_control    = readFloat(&packet[38]);
  currentState.adblue_ratio      = readFloat(&packet[42]);
  currentState.odometer          = readFloat(&packet[46]);
  
  currentState.boolGroup1 = packet[50];
  currentState.boolGroup2 = packet[51];
  currentState.boolGroup3 = packet[52];
  currentState.boolGroup4 = packet[53];
}

// -----------------------------------------------------------------
// Función systemShutdown: Apaga todo el sistema.
void systemShutdown() {
  for (int i = 0; i < MOTOR_COUNT; i++) {
    motors[i].setPosition(0);
    motors[i].updateBlocking();
  }
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 0);
  }
  pixels.show();
  for (int i = 0; i < 6; i++) {
    tm1637.display(i, 0);
  }
}

// -----------------------------------------------------------------
// Función runDiagnostics: Prueba los componentes en el setup.
void runDiagnostics() {
  digitalWrite(LUZ_PIN, HIGH);
  for (int i = 0; i < 6; i++) {
    tm1637.display(i, 0);
  }
  delay(200);
  for (int i = 0; i < MOTOR_COUNT; i++) {
    motors[i].zero();
  }
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, 0xFFFFFF);
  }
  pixels.show();
  delay(200);
  for (int i = 0; i < MOTOR_COUNT; i++) {
    motors[i].setPosition(750);
    motors[i].updateBlocking();
    delay(200);
  }
  delay(500);
  for (int i = MOTOR_COUNT - 1; i >= 0; i--) {
    motors[i].setPosition(0);
    motors[i].updateBlocking();
    delay(200);
  }
  uint32_t colors[4] = {0xFF0000, 0x00FF00, 0x0000FF, 0};
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, colors[j]);
    }
    pixels.show();
    delay(500);
  }
  digitalWrite(LUZ_PIN, LOW);
  for (int num = 0; num < 10; num++) {
    tm1637.display(2, num);
    tm1637.display(1, num);
    tm1637.display(0, num);
    tm1637.display(5, num);
    tm1637.display(4, num);
    tm1637.display(3, num);
    delay(100);
  }
  delay(500);
  systemShutdown();
}

// -----------------------------------------------------------------
// setup(): Inicialización del Arduino.
void setup() {
  Serial.begin(115200);
  pixels.begin();
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  pinMode(LUZ_PIN, OUTPUT);
  runDiagnostics();
  systemShutdown();
}

// -----------------------------------------------------------------
// loop(): Lectura del paquete serial y actualización de salidas.
void loop() {
  while (Serial.available()) {
    byte c = Serial.read();
    if (bufferIdx == 0 && c != 0xFF) continue;
    if (bufferIdx == 1 && c != 0x02) {
      bufferIdx = 0;
      continue;
    }
    packetBuffer[bufferIdx++] = c;
    if (bufferIdx >= expectedLength) {
      processPacketBuffered(packetBuffer, expectedLength);
      bufferIdx = 0;
      // Una vez actualizado el estado, se actualizan las salidas.
      updateOutputs();
    }
  }
  
  // Actualiza los motores para movimientos suaves.
  for (int i = 0; i < MOTOR_COUNT; i++) {
    motors[i].update();
  }
}
