#include "mbed.h"

InterruptIn Am1(D2);
InterruptIn Am2(D11);

DigitalIn Bm1(D3);
DigitalIn Bm2(D10);

PwmOut motgauche(D6);
PwmOut motdroite(D8);

int16_t cpt1 = 0, cpt2 = 0;

void incrementationMot1();
void incrementationMot2();
void avance(int16_t);

double periode = 0.001;

int main() {

  motgauche.period(periode);
  motdroite.period(periode);

  Am1.rise(&incrementationMot1);
  Am2.rise(&incrementationMot2);
  while (1) {
    avance(100);
  }
}

void incrementationMot1(void) {
  if (Bm1.read() == 1) {
    cpt1++;
  } else {
    cpt1--;
  }
}

void incrementationMot2(void) {
  if (Bm2.read() == 0) {
    cpt2++;
  } else {
    cpt2--;
  }
}

void avance(int16_t dist) {
  do {
    if (cpt1 > cpt2) {
      motgauche.pulsewidth(periode * 0.22);
      motdroite.pulsewidth(periode * 0.32);
      printf("cpt1 : %d\n\r", cpt1);

    } else if (cpt1 <= cpt2) {
      motdroite.pulsewidth(periode * 0.22);
      motgauche.pulsewidth(periode * 0.32);
      printf("cpt 2 : %d\n\r", cpt2);
    }
    wait(0.01);
  } while (cpt1 > dist);
}
