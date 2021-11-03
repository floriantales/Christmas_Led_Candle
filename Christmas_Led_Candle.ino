#include <FastLED.h>

#define DATA_PIN    2 // P2 of Digispark board
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    8
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          90
#define FRAMES_PER_SECOND  120
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

#define MOTOR_PIN   0 // P0 of Digispark board

void setup() {
  // Fast LED Setup
  delay(1000); // 1 second delay for recovery
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  // Motor Setup
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, HIGH);
}

void loop()
{
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);
  
  // do some periodic updates
  EVERY_N_MILLISECONDS( 800 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  fill_rainbow( leds, NUM_LEDS, gHue, 0);

  StartMotorPeriodically();
}

void StartMotorPeriodically()
{
  // Toutes les 30 secondes
  uint8_t secondHand = (millis() / 1000) % 30;
  static uint8_t lastSecond = 99;

  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    // Start Motor
    if( secondHand == 10)  { digitalWrite(MOTOR_PIN, LOW); }
    if( secondHand == 20)  { digitalWrite(MOTOR_PIN, HIGH); }
  }
}
