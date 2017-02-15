
unsigned char wc_gen(unsigned char x, unsigned char y, unsigned char z, unsigned char pdwave, unsigned char pdamount, unsigned char t);


#define TABLE_LED_PIN 13
#define BANK_LED_PIN 12
#define PDIST_SWITCH_PIN 11


#define WAVEBUFFER_SAMPLES 128

// ADC_10V_TO_INT_HZ is calculated using 128 samples per hz
#define ADC_10V_TO_INT_HZ (81.75f)
#define MINIMUM_INT_HZ (WAVEBUFFER_SAMPLES * 10)
#define ANALOG_PINS 6

#define PIN_CV 5
#define PIN_X 4
#define PIN_Y 3
#define PIN_Z 2
#define PIN_PDWAVE 1
#define PIN_PDAMOUNT 0

void printFullWaveTime(void);
void printDebug(void);


/********************************
 * Setup
 */
void setup() {
  int i;

  // DAC pins, 8 data & one WR^
  for (i = 2; i < 11; i++)
    pinMode(i, OUTPUT);

  // LEDS and switch
  pinMode(TABLE_LED_PIN, OUTPUT);
  pinMode(BANK_LED_PIN, OUTPUT);
  pinMode(PDIST_SWITCH_PIN, INPUT_PULLUP);

  // Debug
  Serial.begin(9600);

  // Timmer interupt for handling the DAC
  cli();
  setupTimer1();
  setTimer1InterrupFrequency(440UL * WAVEBUFFER_SAMPLES);
  enableTimer1Interrupt();

  // Configure and start the ADC
  setupAdc();
  startAdc(0, 0);
}

/***************************************
 * Wave buffer & interrupt functuin
 */
unsigned char waveBufferIdxReader = 0;
unsigned char waveBufferIdxFinished = 0;
unsigned char waveBuffer[2][WAVEBUFFER_SAMPLES] = {
  {127, 133, 139, 145, 151, 157, 163, 169,
   175, 181, 186, 192, 197, 202, 207, 212,
   216, 221, 225, 229, 232, 235, 239, 241,
   244, 246, 248, 250, 251, 252, 253, 253,
   254, 253, 253, 252, 251, 250, 248, 246,
   244, 241, 239, 235, 232, 229, 225, 221,
   216, 212, 207, 202, 197, 192, 186, 181,
   175, 169, 163, 157, 151, 145, 139, 133,
   126, 120, 114, 108, 102,  96,  90,  84,
    78,  72,  67,  61,  56,  51,  46,  41,
    37,  32,  28,  24,  21,  18,  14,  12,
     9,   7,   5,   3,   2,   1,   0,   0,
     0,   0,   0,   1,   2,   3,   5,   7,
     9,  12,  14,  18,  21,  24,  28,  32,
    37,  41,  46,  51,  56,  61,  67,  72,
    78,  84,  90,  96, 102, 108, 114, 120},
  {127, 133, 139, 145, 151, 157, 163, 169,
   175, 181, 186, 192, 197, 202, 207, 212,
   216, 221, 225, 229, 232, 235, 239, 241,
   244, 246, 248, 250, 251, 252, 253, 253,
   254, 253, 253, 252, 251, 250, 248, 246,
   244, 241, 239, 235, 232, 229, 225, 221,
   216, 212, 207, 202, 197, 192, 186, 181,
   175, 169, 163, 157, 151, 145, 139, 133,
   126, 120, 114, 108, 102,  96,  90,  84,
    78,  72,  67,  61,  56,  51,  46,  41,
    37,  32,  28,  24,  21,  18,  14,  12,
     9,   7,   5,   3,   2,   1,   0,   0,
     0,   0,   0,   1,   2,   3,   5,   7,
     9,  12,  14,  18,  21,  24,  28,  32,
    37,  41,  46,  51,  56,  61,  67,  72,
    78,  84,  90,  96, 102, 108, 114, 120}
};

// PORTB[1:0] contains lower 2 bits for the dac
// PORTD[7:2] contains upper 6 bits for the dac
// PORTB[2] is the falling edge triggerd WR pin of the dac
// CS for the dac is always set low in HW.
static inline void setDac(unsigned char v) {
    PORTB = (PORTB & B11111100) | (v & B00000011) | B00000100;
    PORTD = (PORTD & B00000011) | (v & B11111100);
    PORTB &= B11111011;
}

static unsigned long intCount = 0;
ISR(TIMER1_COMPA_vect){
  static unsigned char dacIdx = 0;

  intCount++;

  setDac(waveBuffer[waveBufferIdxReader][dacIdx]);
  dacIdx++;
  if (dacIdx == WAVEBUFFER_SAMPLES) {
    waveBufferIdxReader = waveBufferIdxFinished;
    dacIdx = 0;
  }
}

/*************************************
 * Wave form generation
 */
static unsigned long genCount = 0;
void generateWaveform(unsigned char x,
                      unsigned char y,
                      unsigned char z,
                      unsigned char pdwave,
                      unsigned char pdamount) {

  static unsigned char genIdx = 0;
  static unsigned char x_ = 0, y_ = 0, z_ = 0,
                       pdwave_ = 0, pdamount_ = 0;

  // Do not start rendering the new wave before the reader has
  // moved on to the previously finished buffer
  if (waveBufferIdxReader != waveBufferIdxFinished)
    return;

  //wc_gen expects 256 samples per cycle, but we only have time for 128
  waveBuffer[!waveBufferIdxFinished][genIdx] =
    wc_gen(x_, y_, z_, pdwave_, pdamount_, genIdx << 1);

  genIdx++;
  if (genIdx == WAVEBUFFER_SAMPLES) {
    genIdx = 0;
    waveBufferIdxFinished = !waveBufferIdxFinished;

    // Save params so that they remain consistent over the entire wave
    x_ = x;
    y_ = y;
    z_ = z;
    pdwave_ = pdwave;
    pdamount_ = pdamount;

    genCount++;
    //printFullWaveTime();
  }
}

/*****************************************
 * Analog input
 */
unsigned int analogReads = 0;
unsigned short analogIn[ANALOG_PINS] = { 0 };
void updateAnalogIn(void) {
  static unsigned char current = 0; 
  int result;

  result = readAdc();
  if (result < 0)
    return;

  analogReads++;

  analogIn[current] = result;

  current++;
  if (current >= ANALOG_PINS)
    current = 0;

  startAdc(current, current == PIN_CV);
}

/****************************************
 * Pitch and timer interrupt handling
 */
unsigned short getPitchCV(void) {
  static unsigned short last = 0;
  short diff;
  
  diff = last - analogIn[PIN_CV];
  if (diff < -1 || diff > 1)
    last = analogIn[PIN_CV];
  
  return last;
}

float AdcToIntHz(unsigned short adc) {
  return ADC_10V_TO_INT_HZ * adc;
}

void handlePitchCv(unsigned short pitchCv) {
  static unsigned short lastPitchCv = 1;
  float ihz;
    
  if (lastPitchCv == pitchCv)
    return;
         
  lastPitchCv = pitchCv;

  ihz = AdcToIntHz(pitchCv);
  if (ihz < MINIMUM_INT_HZ)
    ihz = MINIMUM_INT_HZ;

  setTimer1InterrupFrequency(ihz);
}

/********************************
 * LED handling
 */
static unsigned char bankled = 0xff,
                     tableled = 0xff;
void updateLeds(unsigned char y, unsigned char z) {
  y = !(0x0F & y);
  z = !(0x0F & z);

  if (y != tableled || z != bankled) {
    cli();
    digitalWrite(TABLE_LED_PIN, y ? HIGH : LOW);
    digitalWrite(BANK_LED_PIN, z ? HIGH : LOW);
    sei();

    tableled = y;
    bankled = z;
  }
}

/******************************************
 * Main loop
 */
unsigned char pd_switch;
void loop() {
  unsigned char x, y, z, pdwave, pdamount;
  unsigned short currentPitchCv;

  printDebug();

  /* Read input */
  {
    // Digital pin, Phase dist switch
    pd_switch = digitalRead(PDIST_SWITCH_PIN);

    // Analog pins
    updateAnalogIn();

    //Adc has uses 10 bit resolution
    currentPitchCv = getPitchCV();
    x = analogIn[PIN_X] >> 2;
    y = analogIn[PIN_Y] >> 2;
    z = analogIn[PIN_Z] >> 2;
    pdwave = analogIn[PIN_PDWAVE] >> 2;
    pdamount = analogIn[PIN_PDAMOUNT] >> 2;
  }

  handlePitchCv(currentPitchCv);

  generateWaveform(x, y, z, pdwave, pdamount);

  updateLeds(y, z);
}


/*************************************************
 * Debug functions
 */

#define DEBUG_S (10)
#define DEBUG_MS (DEBUG_S * 1000)

void printDebug(void) {
  static unsigned long lastStamp = 0;
  static unsigned long lastIntCount = 0;
  static unsigned long lastGenCount = 0;
  static unsigned long lastAnaCount = 0;

  //static unsigned long dotStamp = 0;
  //if ((millis() - dotStamp) > 1000) {
  //  Serial.print(".");
  //  dotStamp = millis();
  //}

  if ((millis() - lastStamp) > DEBUG_MS) {
    unsigned long diffInt = intCount - lastIntCount;
    unsigned long diffGen = genCount - lastGenCount;
    unsigned long diffAna = analogReads - lastAnaCount;
    float ihz = AdcToIntHz(getPitchCV());

    Serial.print("\n\n----------------\n");

    Serial.print("CV: ");
    Serial.print(ihz/WAVEBUFFER_SAMPLES);
    Serial.print("Hz, Int: ");
    Serial.print(ihz);
    Serial.print("Hz\n\n");
    
    Serial.print("Ints: ");
    Serial.print(diffInt, DEC);
    Serial.print(", ");
    Serial.print(diffInt / ((float) WAVEBUFFER_SAMPLES * DEBUG_S));
    Serial.print("Hz\n");
    Serial.print("Gen: ");
    Serial.print(diffGen, DEC);
    Serial.print(", ");
    Serial.print(diffGen / (float) DEBUG_S);
    Serial.print("Hz\n\n");

    Serial.print(" * AnalogPins *\n");
    int i;
    for (i = 0; i < ANALOG_PINS; i++) {
      Serial.print("[");
      Serial.print(i, DEC);
      Serial.print("]: ");
      Serial.print(analogIn[i], DEC);
      Serial.print(" (");
      Serial.print(analogIn[i] >> 6, DEC);
      Serial.print(")\n");
    }
    Serial.print("Reads: ");
    Serial.print(diffAna, DEC);
    Serial.print(", ");
    Serial.print(diffAna / 6, DEC);
    Serial.print("Hz\n\n");

    Serial.print(" * Leds *\nTable: ");
    Serial.print(tableled, DEC);
    Serial.print("\nBank: ");
    Serial.print(bankled, DEC);
    Serial.print("\n\n");

    Serial.print("Switch: ");
    Serial.print(pd_switch, DEC);
    Serial.print("\n\n");
                      

    lastStamp = millis();
    lastIntCount = intCount;
    lastGenCount = genCount;
    lastAnaCount = analogReads;
  }
}

void printFullWaveTime(void) {
  static unsigned int s = 0;
  unsigned int e = millis();

  Serial.print("Full wave:");
  Serial.print(e - s, DEC);
  Serial.print("ms\n");
  s = millis();
}
