void setupTimer1(void) {
  TCCR1A = 0;
  TCCR1B = 0;
}

void setTimer1InterrupFrequency(unsigned short hz) {
  unsigned long count = 16000000UL / hz;
  unsigned char prescalerBits = 1 << CS10;
  count--;

  if (count >= 65536) {
    count /= 8;
    prescalerBits = 1 << CS11;
  }

  cli();

  TCNT1  = 0;
  TCCR1B = (1 << WGM12) | prescalerBits;
  OCR1A = count;

  sei();
}

void enableTimer1Interrupt(void) {
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

