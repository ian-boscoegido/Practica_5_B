#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables para animaciones
int frame = 0;
int olaOffset = 0;
int avionX = -30;
int moscaX = 50;
int moscaY = 32;
int direccionX = 1;
int direccionY = 1;
bool ojosAbiertos = true;
unsigned long ultimoParpadeo = 0;

// ========== FUNCIÓN: DIBUJAR SONRISA (alternativa a drawArc) ==========
void dibujarSonrisa(int x, int y, int radio) {
  for(int angulo = 180; angulo <= 360; angulo += 5) {
    float rad = angulo * 3.14159 / 180;
    int x1 = x + cos(rad) * radio;
    int y1 = y + sin(rad) * radio;
    display.drawPixel(x1, y1, SSD1306_BLACK);
  }
}

// ========== FUNCIÓN: DIBUJAR ELIPSE (alternativa a fillEllipse) ==========
void dibujarElipse(int x, int y, int rx, int ry, bool relleno) {
  for(int dy = -ry; dy <= ry; dy++) {
    for(int dx = -rx; dx <= rx; dx++) {
      if((dx*dx * ry*ry + dy*dy * rx*rx) <= (rx*rx * ry*ry)) {
        if(relleno) {
          display.drawPixel(x + dx, y + dy, SSD1306_WHITE);
        } else {
          // Solo borde
          if(abs(dx) == rx || abs(dy) == ry) {
            display.drawPixel(x + dx, y + dy, SSD1306_WHITE);
          }
        }
      }
    }
  }
}

// ========== ANIMACIÓN 1: BARCO NAVEGANDO ==========
void dibujarBarco() {
  display.clearDisplay();
  
  // Cielo azul (fondo)
  display.fillRect(0, 0, SCREEN_WIDTH, 40, SSD1306_WHITE);
  
  // Sol
  display.fillCircle(110, 10, 6, SSD1306_WHITE);
  // Rayos del sol
  for(int i = 0; i < 8; i++) {
    float angulo = i * 45 + frame * 5;
    int x2 = 110 + cos(angulo * 3.14159/180) * 12;
    int y2 = 10 + sin(angulo * 3.14159/180) * 12;
    display.drawLine(110, 10, x2, y2, SSD1306_WHITE);
  }
  
  // Nubes
  display.fillCircle(15, 15, 5, SSD1306_WHITE);
  display.fillCircle(22, 12, 6, SSD1306_WHITE);
  display.fillCircle(29, 15, 5, SSD1306_WHITE);
  
  // Mar (olas animadas)
  for(int i = 0; i < SCREEN_WIDTH; i += 4) {
    int alturaOla = 50 + sin((i + olaOffset) * 0.1) * 3;
    display.drawLine(i, alturaOla, i + 4, alturaOla, SSD1306_WHITE);
    // Rellenar agua debajo
    for(int y = alturaOla; y < SCREEN_HEIGHT; y++) {
      display.drawPixel(i, y, SSD1306_WHITE);
      display.drawPixel(i + 1, y, SSD1306_WHITE);
    }
  }
  
  // Cuerpo del barco
  display.fillRect(30, 45, 60, 6, SSD1306_WHITE);
  display.fillTriangle(25, 45, 45, 38, 45, 45, SSD1306_WHITE);
  display.fillTriangle(95, 45, 75, 38, 75, 45, SSD1306_WHITE);
  
  // Chimenea
  display.fillRect(55, 30, 8, 15, SSD1306_WHITE);
  
  // Humo
  int humoY = 25 - (frame % 20) / 4;
  display.fillCircle(59, humoY, 3, SSD1306_WHITE);
  display.fillCircle(55, humoY - 3, 2, SSD1306_WHITE);
  display.fillCircle(63, humoY - 2, 2, SSD1306_WHITE);
  
  display.display();
}

// ========== ANIMACIÓN 2: AVIÓN VOLANDO ==========
void dibujarAvion() {
  display.clearDisplay();
  
  // Cielo
  for(int i = 0; i < SCREEN_HEIGHT/2; i += 2) {
    display.drawLine(0, i, SCREEN_WIDTH, i, SSD1306_WHITE);
  }
  
  // Nubes en movimiento
  display.fillCircle(20 + (frame % 50), 20, 6, SSD1306_WHITE);
  display.fillCircle(30 + (frame % 50), 18, 8, SSD1306_WHITE);
  display.fillCircle(40 + (frame % 50), 20, 6, SSD1306_WHITE);
  
  display.fillCircle(80 - (frame % 40), 40, 5, SSD1306_WHITE);
  display.fillCircle(88 - (frame % 40), 38, 7, SSD1306_WHITE);
  
  // Avión
  int avionY = 30 + sin(frame * 0.05) * 5;
  avionX += 2;
  if(avionX > SCREEN_WIDTH + 30) avionX = -50;
  
  // Cuerpo
  display.fillRect(avionX, avionY, 35, 4, SSD1306_WHITE);
  
  // Alas
  display.fillTriangle(avionX + 10, avionY + 2, 
                       avionX + 20, avionY + 12, 
                       avionX + 25, avionY + 2, SSD1306_WHITE);
  display.fillTriangle(avionX + 10, avionY + 1, 
                       avionX + 20, avionY - 8, 
                       avionX + 25, avionY + 1, SSD1306_WHITE);
  
  // Cola
  display.fillTriangle(avionX + 30, avionY + 2, 
                       avionX + 38, avionY + 5, 
                       avionX + 38, avionY - 1, SSD1306_WHITE);
  
  // Ventanas
  display.fillCircle(avionX + 8, avionY + 2, 1, SSD1306_BLACK);
  display.fillCircle(avionX + 15, avionY + 2, 1, SSD1306_BLACK);
  display.fillCircle(avionX + 22, avionY + 2, 1, SSD1306_BLACK);
  
  // Estela
  for(int i = 1; i <= 3; i++) {
    int estelaX = avionX - i * 8;
    if(estelaX > 0 && estelaX < SCREEN_WIDTH) {
      display.fillCircle(estelaX, avionY + 2, 3 - i, SSD1306_WHITE);
    }
  }
  
  display.display();
}

// ========== ANIMACIÓN 3: EMOJI CON GAFAS ==========
void dibujarEmoji() {
  display.clearDisplay();
  
  // Cara
  display.fillCircle(SCREEN_WIDTH/2, 35, 28, SSD1306_WHITE);
  
  // Ojos
  if(ojosAbiertos) {
    display.fillCircle(52, 30, 5, SSD1306_BLACK);
    display.fillCircle(76, 30, 5, SSD1306_BLACK);
    int mirada = (frame % 60 < 30) ? 1 : -1;
    display.fillCircle(52 + mirada, 30, 2, SSD1306_WHITE);
    display.fillCircle(76 + mirada, 30, 2, SSD1306_WHITE);
  } else {
    display.drawLine(47, 30, 57, 30, SSD1306_BLACK);
    display.drawLine(71, 30, 81, 30, SSD1306_BLACK);
  }
  
  // Gafas de sol
  display.drawRect(44, 24, 18, 14, SSD1306_BLACK);
  display.drawRect(66, 24, 18, 14, SSD1306_BLACK);
  display.drawLine(62, 31, 66, 31, SSD1306_BLACK);
  display.drawLine(44, 28, 38, 26, SSD1306_BLACK);
  display.drawLine(84, 28, 90, 26, SSD1306_BLACK);
  
  // Sonrisa (usando puntos)
  for(int ang = 190; ang <= 350; ang += 8) {
    float rad = ang * 3.14159 / 180;
    int x1 = SCREEN_WIDTH/2 + cos(rad) * 12;
    int y1 = 45 + sin(rad) * 8;
    display.drawPixel(x1, y1, SSD1306_BLACK);
  }
  
  // Cejas
  display.drawLine(45, 20, 55, 18, SSD1306_BLACK);
  display.drawLine(73, 18, 83, 20, SSD1306_BLACK);
  
  // Reflejos
  display.fillCircle(48, 28, 1, SSD1306_WHITE);
  display.fillCircle(70, 28, 1, SSD1306_WHITE);
  
  display.display();
}

// ========== ANIMACIÓN 4: MOSCA ==========
void dibujarMosca() {
  display.clearDisplay();
  
  // Fondo (patrón de puntos)
  for(int i = 0; i < 50; i++) {
    display.drawPixel(random(SCREEN_WIDTH), random(SCREEN_HEIGHT), SSD1306_WHITE);
  }
  
  // Movimiento aleatorio
  if(random(100) < 10) {
    direccionX = random(-2, 3);
    direccionY = random(-2, 3);
  }
  
  moscaX += direccionX;
  moscaY += direccionY;
  
  // Limitar bordes
  if(moscaX < 5) moscaX = 5;
  if(moscaX > SCREEN_WIDTH - 5) moscaX = SCREEN_WIDTH - 5;
  if(moscaY < 10) moscaY = 10;
  if(moscaY > SCREEN_HEIGHT - 10) moscaY = SCREEN_HEIGHT - 10;
  
  // Cuerpo
  display.fillCircle(moscaX, moscaY, 4, SSD1306_WHITE);
  
  // Ojos
  display.fillCircle(moscaX - 3, moscaY - 1, 2, SSD1306_WHITE);
  display.fillCircle(moscaX + 3, moscaY - 1, 2, SSD1306_WHITE);
  display.fillCircle(moscaX - 3, moscaY - 1, 1, SSD1306_BLACK);
  display.fillCircle(moscaX + 3, moscaY - 1, 1, SSD1306_BLACK);
  
  // Alas (vibran)
  int vibracion = sin(frame * 0.3) * 2;
  display.fillTriangle(moscaX - 4, moscaY - 1, 
                       moscaX - 8 + vibracion, moscaY - 7, 
                       moscaX - 2, moscaY - 3, SSD1306_WHITE);
  display.fillTriangle(moscaX + 4, moscaY - 1, 
                       moscaX + 8 - vibracion, moscaY - 7, 
                       moscaX + 2, moscaY - 3, SSD1306_WHITE);
  
  // Patas
  display.drawLine(moscaX - 3, moscaY + 2, moscaX - 5, moscaY + 6, SSD1306_WHITE);
  display.drawLine(moscaX + 3, moscaY + 2, moscaX + 5, moscaY + 6, SSD1306_WHITE);
  display.drawLine(moscaX, moscaY + 3, moscaX, moscaY + 7, SSD1306_WHITE);
  
  // Texto
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("!MOSCA!");
  display.setCursor(0, 55);
  display.println("Atrapala!");
  
  display.display();
}

// ========== SETUP ==========
void setup() {
  Serial.begin(115200);
  delay(100);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Error: OLED no encontrado");
    for(;;);
  }
  
  Serial.println("OLED listo! Animaciones activadas");
  
  // Pantalla de bienvenida
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("ANIMACIONES");
  display.setTextSize(1);
  display.setCursor(15, 45);
  display.println("OLED I2C ESP32");
  display.display();
  delay(2000);
}

// ========== LOOP ==========
void loop() {
  // BARCO
  for(int i = 0; i < 150; i++) {
    olaOffset += 2;
    frame++;
    dibujarBarco();
    delay(50);
  }
  
  // AVIÓN
  for(int i = 0; i < 250; i++) {
    frame++;
    dibujarAvion();
    delay(40);
  }
  
  // EMOJI
  for(int i = 0; i < 200; i++) {
    frame++;
    if(millis() - ultimoParpadeo > 1500) {
      ojosAbiertos = false;
      delay(80);
      ojosAbiertos = true;
      ultimoParpadeo = millis();
    }
    dibujarEmoji();
    delay(60);
  }
  
  // MOSCA
  for(int i = 0; i < 300; i++) {
    frame++;
    dibujarMosca();
    delay(35);
  }
  
  delay(1000);
}