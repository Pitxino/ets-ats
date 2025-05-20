#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

#define SD_CS      4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  
  if (!SD.begin(SD_CS)) {
    Serial.println("Error al inicializar la tarjeta SD");
    return;
  }
  
  Serial.println("Listo para recibir el nombre del archivo BMP por el puerto serie.");
}

void loop() {
  if (Serial.available()) {
    String filename = Serial.readStringUntil('\n');
    
    if (cargarYMostrarImagenDesdeSD(filename)) {
      Serial.println("Imagen cargada y mostrada con éxito.");
    } else {
      Serial.println("Error al cargar la imagen.");
    }
  }
}

boolean cargarYMostrarImagenDesdeSD(const String& filename) {
  File bmpFile = SD.open(filename);
  
  if (!bmpFile) {
    Serial.println("No se pudo abrir el archivo BMP.");
    return false;
  }
  
  if (!cargarImagenBMP(bmpFile)) {
    Serial.println("Error al cargar el archivo BMP.");
    bmpFile.close();
    return false;
  }
  
  bmpFile.close();
  return true;
}

boolean cargarImagenBMP(File file) {
  // Lógica para cargar y mostrar la imagen BMP
  // Esto sigue siendo similar a la versión anterior
}

// Las funciones read16() y read32() se mantienen igual que en la versión anterior.
