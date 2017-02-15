void setupAdc(void) {
  ADMUX &= B11011111; // clear ADLAR in ADMUX (0x7C) to right-adjust the result
  ADMUX |= B01000000; // Set REFS1..0 in ADMUX to change reference voltage to the proper source (01)
  ADMUX &= B11110000; // Clear MUX3..0 in ADMUX
  ADCSRA |= B10000000; // Set ADEN in ADCSRA (0x7A) to enable the ADC.
  ADCSRA |= B00000111; // Set the Prescaler to 128 (16000KHz/128 = 125KHz), bove 200KHz 10-bit results are not reliable.
}

#define ADC_PRESCALER_16 ((1 << ADPS2))
#define ADC_PRESCALER_32 ((1 << ADPS2) | (1 << ADPS0))
#define ADC_PRESCALER_64 ((1 << ADPS2) | (1 << ADPS1))
#define ADC_PRESCALER_128 ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))

int readAdc(void) {
  unsigned short analogVal;

  if (bit_is_set(ADCSRA, ADSC))
    return -1;

  analogVal = ADCL | (ADCH << 8);
  return analogVal;
}

void startAdc(unsigned char pin, unsigned char highres) {
  //
  // TODO: investigate why this isn't working 
  // 
  //ADCSRA &= ADC_PRESCALER_128;
  //if (highres)
  //  ADCSRA |= ADC_PRESCALER_128;
  //else
  //  ADCSRA |= ADC_PRESCALER_32;
  
  ADMUX &= B11110000;
  ADMUX |= B00001111 & pin;
  ADCSRA |=B01000000;
}
