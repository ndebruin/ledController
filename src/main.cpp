#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 14
#define BRIGHTNESS 100

#define FRAMES_PER_SECOND 120

CRGB leds[NUM_LEDS];

CRGB COLOR1 = CRGB::Green;

CRGB COLOR2 = CRGB::Yellow;

CRGB BLACK = CRGB::Black;

// effects
void rainbow();
void marquee();
void colorChase();
void tailColor1();
void color1Bounce();
void tailColor2();
void color2Bounce();

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, marquee, colorChase, tailColor1, tailColor2 };

// choose which pattern for above list
uint8_t patternNumber = 0;
// base hue for a number of patterns
uint8_t gHue = 0;

void setup() {
    SerialUSB.begin(9600);
    
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear(); 
}

void loop() {
  // if there's data in from the serial port
  if(SerialUSB.available() != 0){
    //String input = SerialUSB.readStringUntil("\n");


  }
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += COLOR1;
  

  FastLED.show();

  FastLED.delay(1000/FRAMES_PER_SECOND);
  delay(100);

  EVERY_N_MILLISECONDS( 10 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}



void rainbow(){
  // FastLED's built-in rainbow generator
  fill_rainbow_circular( leds, NUM_LEDS, gHue, 7);
}

// start color
uint8_t startColor = 0;
void marquee(){
  for (int i = 0; i <= NUM_LEDS; i++) {
    int color = (i + startColor) % 2;  // mod restricts the color number
    if(color == 0){
      leds[i] = COLOR1;
    }
    else{
      leds[i] = COLOR2;
    }
  }
  startColor = (startColor+1)%2;
}

void colorChase(){

}


void tailColor1(){
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += COLOR1;
  
}



void tailColor2(){
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += COLOR2;
}

