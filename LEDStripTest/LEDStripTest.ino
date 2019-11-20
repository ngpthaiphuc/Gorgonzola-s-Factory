#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

int shiftR = 0;
int shiftG = 255;
int shiftB = 0;
int RGBChange;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  RGBChange = 700 / NUM_LEDS;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void loop() {
  blinkyGreen();
  Serial.println(shiftG);
}

void blinkyRed() {
//  shiftR = 255;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(shiftR, 0, 0);
  }
  if(shiftR == 255){
    shiftR = 0;
  } else{
    shiftR = 255;
  }
  FastLED.show();
  delay(100);
}

void blinkyGreen() {
//  shiftG = 255;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, shiftG, 0);
  }
  if(shiftG == 255){
    shiftG = 0;
  } else{
    shiftG = 255;
  }
  FastLED.show();
  delay(100);
}

void rainbowShift() {
  shiftR = 255;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(shiftR, shiftG, shiftB);
  }
  if (shiftR == 255 && shiftB == 0) {
    shiftG += 1;
    if (shiftG > 255) {
      shiftG = 255;
    }
  }
  if (shiftG == 255 && shiftB == 0) {
    shiftR -= 1;
    if (shiftR < 0) {
      shiftR = 0;
    }
  }
  if (shiftR == 0 && shiftG == 255) {
    shiftB += 1;
    if (shiftB > 255) {
      shiftB = 255;
    }
  }
  if (shiftR == 0 && shiftB == 255) {
    shiftG -= 1;
    if (shiftG < 0) {
      shiftG = 0;
    }
  }
  if (shiftG == 0 && shiftB == 255) {
    shiftR += 1;
    if (shiftR > 255) {
      shiftR = 255;
    }
  }
  if (shiftR == 255 && shiftG == 0) {
    shiftB -= 1;
    if (shiftB < 0) {
      shiftB = 0;
    }
  }
  FastLED.show();
  delay(1);
}

void rainbowSnake(int updateLEDS) {
  int r = 255;
  int g = 0;
  int b = 0;
  for (int i = 0; i < NUM_LEDS + updateLEDS; i++) {
    if (i < NUM_LEDS) {
      for (int j = i; j < i + updateLEDS; j++) {
        leds[j] = CRGB(r, g, b);
        if (r == 255 && b == 0) {
          g += RGBChange;
          if (g > 255) {
            g = 255;
          }
        }
        if (g == 255 && b == 0) {
          r -= RGBChange;
          if (r < 0) {
            r = 0;
          }
        }
        if (r == 0 && g == 255) {
          b += RGBChange;
          if (b > 255) {
            b = 255;
          }
        }
        if (r == 0 && b == 255) {
          g -= RGBChange;
          if (g < 0) {
            g = 0;
          }
        }
        if (g == 0 && b == 255) {
          r += RGBChange;
          if (r > 255) {
            r = 255;
          }
        }
        if (r == 255 && g == 0) {
          b -= RGBChange;
          if (b < 0) {
            b = 0;
          }
        }
      }
    }
    if (i >= updateLEDS) {
      leds[i - updateLEDS] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(1);
  }

  /*for (int i = NUM_LEDS - 1; i >= 0; i--) {
    for (int j = i; j >= i - updateLEDS; j--) {
      leds[j] = CRGB(0, 255, 255);
    }
    if (i < NUM_LEDS - updateLEDS - 1) {
      leds[i + updateLEDS] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(10);
    }*/

}
