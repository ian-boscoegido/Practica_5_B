# 🎨 Animaciones Gráficas en OLED SSD1306 (ESP32)

Animaciones dinámicas y funciones de dibujo personalizadas para pantallas OLED (controlador SSD1306) usando ESP32 y la librería Adafruit GFX.

---

## ✨ Características Técnicas

- **Motor de Animación:** Lógica de fotogramas para animación de objetos (barco, mosca, etc.)
- **Primitivas Gráficas:** Renderizado de píxeles, líneas y formas con Adafruit GFX
- **Algoritmos Personalizados:** Funciones como `dibujarSonrisa` con trigonometría (cos/sin)
- **Gestión de Hardware:** Configuración I2C optimizada para ESP32

---

## 📋 Requisitos

| Componente | Especificación |
|-----------|---|
| **Microcontrolador** | ESP32 |
| **Display** | OLED 128x64, SSD1306, I2C (0x3C) |
| **Adafruit SSD1306** | v2.5.7+ |
| **Adafruit GFX Library** | v1.11.5+ |

---

## 🔌 Conexión de Hardware

| Función | Pin ESP32 |
|---------|-----------|
| **SDA** | GPIO 21 |
| **SCL** | GPIO 22 |
| **VCC** | 3.3V |
| **GND** | GND |

---

## 🚀 Compilación y Ejecución

Este proyecto utiliza **PlatformIO**:

1. Instala la extensión de PlatformIO en VS Code
2. Conecta tu ESP32 al puerto USB
3. Ejecuta: `pio run -t upload`
4. El monitor serie mostrará el estado de inicialización

---

## 📂 Estructura del Código

- **loop():** Gestiona la lógica de movimiento y actualización de pantalla
- **Actualización de coordenadas:** Cada ciclo actualiza (x, y) de objetos
- **Buffer:** Limpia y redibuja la pantalla en cada iteración

---

*Desarrollado para prácticas de sistemas embebidos y computación gráfica.*