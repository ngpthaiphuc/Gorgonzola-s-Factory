#define LATCH 6
#define CLOCK 7
#define DATA 5

byte pattern[8] = {
 B00000000,
 B00000000,
 B00111100,
 B01000010,
 B01111110,
 B01000010,
 B01000010,
 B01000010
};

void setup() {
 pinMode (LATCH, OUTPUT);
 pinMode (CLOCK, OUTPUT);
 pinMode (DATA, OUTPUT);
}

void loop() {
 for (byte i=0; i<8; i++) {
   digitalWrite(LATCH, LOW);
   shiftOut(DATA, CLOCK, LSBFIRST, pattern[i]);
    shiftOut(DATA, CLOCK, LSBFIRST, 1<<i);
   digitalWrite(LATCH, HIGH);
   delay(64);
 }
}
