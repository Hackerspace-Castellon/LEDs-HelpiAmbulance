#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL 21
#define NUM_LEDS 4

Adafruit_NeoPixel leds(NUM_LEDS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Colores según normativa española
uint32_t colorAzul = leds.Color(0, 0, 255);    // Azul para emergencias
uint32_t colorBlanco = leds.Color(255, 255, 255); // Blanco como complemento
uint32_t colorApagado = leds.Color(0, 0, 0);

// Variables para control de tiempo
unsigned long tiempoAnterior = 0;
int paso = 0;
int modoActual = 0;
const int numModos = 3; // Usamos 3 modos diferentes

void setup() {
  leds.begin();
  leds.setBrightness(255);
  leds.show();
  
  // Secuencia de inicio
  for (int i = 0; i < NUM_LEDS; i++) {
    leds.setPixelColor(i, colorBlanco);
    leds.show();
    delay(200);
    leds.clear();
    leds.show();
  }
}

void loop() {
  // Cambiar de modo cada 10 segundos
  if (millis() % 10000 < 50) {
    modoActual = (modoActual + 1) % numModos;
    leds.clear();
    leds.show();
    paso = 0; // Reiniciar el paso para cada modo
    delay(200); // Pequeña pausa entre modos
  }
  
  // Ejecutar el modo actual
  switch (modoActual) {
    case 0:
      secuenciaAmbulanciaEspanola();
      break;
    case 1:
      efectoConvergenteDivergente();
      break;
    case 2:
      ninoNino();
      break;
    /*case 3:
      efectoZigzag();
      break;
    case 4:
      efectoCascada();
      break;
    case 5:
      efectoBarrido();
      */
  }
}

// MODO 0: Secuencia típica de ambulancia española
void secuenciaAmbulanciaEspanola() {
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior > 80) { // Más rápido: 80ms en lugar de 100ms
    tiempoAnterior = tiempoActual;
    
    switch (paso) {
      case 0: // Lado izquierdo azul, derecho apagado
        leds.setPixelColor(0, colorAzul);
        leds.setPixelColor(1, colorAzul);
        leds.setPixelColor(2, colorApagado);
        leds.setPixelColor(3, colorApagado);
        break;
      case 1: // Todo apagado (breve pausa)
        leds.setPixelColor(0, colorApagado);
        leds.setPixelColor(1, colorApagado);
        leds.setPixelColor(2, colorApagado);
        leds.setPixelColor(3, colorApagado);
        break;
      case 2: // Lado izquierdo apagado, derecho azul
        leds.setPixelColor(0, colorApagado);
        leds.setPixelColor(1, colorApagado);
        leds.setPixelColor(2, colorAzul);
        leds.setPixelColor(3, colorAzul);
        break;
      case 3: // Todo apagado (breve pausa)
        leds.setPixelColor(0, colorApagado);
        leds.setPixelColor(1, colorApagado);
        leds.setPixelColor(2, colorApagado);
        leds.setPixelColor(3, colorApagado);
        break;
      case 4: // Destello blanco simultáneo en todos
        leds.setPixelColor(0, colorBlanco);
        leds.setPixelColor(1, colorBlanco);
        leds.setPixelColor(2, colorBlanco);
        leds.setPixelColor(3, colorBlanco);
        break;
      case 5: // Todo apagado (breve pausa)
        leds.setPixelColor(0, colorApagado);
        leds.setPixelColor(1, colorApagado);
        leds.setPixelColor(2, colorApagado);
        leds.setPixelColor(3, colorApagado);
        break;
    }
    
    leds.show();
    paso = (paso + 1) % 6;
  }
}

// MODO 1: Barrido secuencial alternando colores
void efectoBarrido() {
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior > 90) { // Más rápido: 90ms en lugar de 120ms
    tiempoAnterior = tiempoActual;
    
    leds.clear();
    
    // Determinar color basado en ciclo (azul en ida, blanco en vuelta)
    uint32_t colorActual;
    if (paso < NUM_LEDS) {
      colorActual = colorAzul;
    } else {
      colorActual = colorBlanco;
      paso = paso % NUM_LEDS + NUM_LEDS; // Mantener en rango correcto
    }
    
    // Encender solo el LED actual
    leds.setPixelColor(paso % NUM_LEDS, colorActual);
    leds.show();
    
    paso = (paso + 1) % (NUM_LEDS * 2);
  }
}

// MODO 2: Efecto convergente/divergente
void efectoConvergenteDivergente() {
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior > 120) { // Más rápido: 120ms en lugar de 150ms
    tiempoAnterior = tiempoActual;
    
    leds.clear();
    
    switch (paso) {
      case 0: // Extremos azules
        leds.setPixelColor(0, colorAzul);
        leds.setPixelColor(3, colorAzul);
        break;
      case 1: // Centro azul
        leds.setPixelColor(1, colorAzul);
        leds.setPixelColor(2, colorAzul);
        break;
      case 2: // Extremos blancos
        leds.setPixelColor(0, colorBlanco);
        leds.setPixelColor(3, colorBlanco);
        break;
      case 3: // Centro blanco
        leds.setPixelColor(1, colorBlanco);
        leds.setPixelColor(2, colorBlanco);
        break;
    }
    
    leds.show();
    paso = (paso + 1) % 4;
  }
}

// MODO 3: Efecto zigzag
void efectoZigzag() {
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior > 100) { // Más rápido: 100ms en lugar de 140ms
    tiempoAnterior = tiempoActual;
    
    leds.clear();
    
    // Secuencia de encendido en zigzag
    int ledActual;
    switch (paso) {
      case 0: ledActual = 0; break;
      case 1: ledActual = 2; break;
      case 2: ledActual = 1; break;
      case 3: ledActual = 3; break;
    }
    
    // Alternancia de colores
    if (paso < 2) {
      leds.setPixelColor(ledActual, colorAzul);
    } else {
      leds.setPixelColor(ledActual, colorBlanco);
    }
    
    leds.show();
    paso = (paso + 1) % 4;
  }
}

// MODO 4: Efecto cascada
void efectoCascada() {
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior > 70) { // Más rápido: 70ms en lugar de 100ms
    tiempoAnterior = tiempoActual;
    
    // Desplazar todos los LEDs una posición
    for (int i = NUM_LEDS - 1; i > 0; i--) {
      uint32_t colorAnterior = leds.getPixelColor(i-1);
      leds.setPixelColor(i, colorAnterior);
    }
    
    // Introducir nuevo color en la posición 0
    if (paso % 4 == 0) {
      leds.setPixelColor(0, colorAzul);
    } else if (paso % 4 == 2) {
      leds.setPixelColor(0, colorBlanco);
    } else {
      leds.setPixelColor(0, colorApagado);
    }
    
    leds.show();
    paso = (paso + 1) % 8;
  }
}

// MODO 5: Efecto ninoNino - alternancia de luces azules
void ninoNino() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= 500) { // Intervalo de 500 ms
    tiempoAnterior = tiempoActual;

    if (paso % 2 == 0) {
      // Encender LEDs 0 y 1 (las dos primeras)
      leds.setPixelColor(0, colorAzul);
      leds.setPixelColor(1, colorAzul);
      leds.setPixelColor(2, colorApagado);
      leds.setPixelColor(3, colorApagado);
    } else {
      // Encender LEDs 2 y 3 (las dos últimas)
      leds.setPixelColor(0, colorApagado);
      leds.setPixelColor(1, colorApagado);
      leds.setPixelColor(2, colorAzul);
      leds.setPixelColor(3, colorAzul);
    }

    leds.show();
    paso++;
  }
}
