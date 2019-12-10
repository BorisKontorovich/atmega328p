void init() {
  
/*
  ADMUX - ADC Multiplexer Selection Register

  bit          7           6          5         4        3         2          1          0
  name       REFS1       REFS0      ADLAR       -       MUX3      MUX2       MUX1       MUX0
  set to       0           1          1         0        0         1          0          1

  REFS1 = 0    use AVCC for reference voltage
  REFS0 = 1

  ADLAR = 1    left justify ADC result in ADCH/ADCL

  bit 4 = 0

  MUX3 = 0     use PC5/ADC5 (pin 28) for input
  MUX2 = 1
  MUX1 = 0
  MUX0 = 1
  */
  ADMUX = 0b01100101;

  /*
  ADCSRA - ADC Control and Status Register A

  bit          7           6            5          4          3            2           1           0
  name        ADEN        ADSC        ADATE       ADIF       ADIE        ADPS2       ADPS1       ADPS0
  set to       1           0            0          0          0            0           1           1

  ADEN = 1     enable ADC
  ADSC = 0     don't start ADC yet
  ADATE = 0    don't enable ADC auto trigger (i.e. use single conversion mode)
  ADIF = 0     don't set ADC interrupt flag
  ADIE = 0     don't set ADC interrupt enable

  ADPS2 = 0
  ADPS1 = 1    1 MHz clock / 8 = 125 kHz ADC clock
  ADPS0 = 1
  */
  ADCSRA = 0b10000011;

  /*
  ADCSRB - ADC Control and Status Register B

  bit         7           6           5           4           3         2           1           0
  name        -          ACME         -           -           -       ADTS2       ADTS1       ADTS0
  set to      0           0           0           0           0         0           0           0

  bit 7 = 0
  ACME = 0     don't enable analog comparator multiplexer
  bit 5 = 0
  bit 4 = 0
  bit 3 = 0
  ADTS2 = 0
  ADTS1 = 0    register ADCSRA bit ADATE set to 0 so these bits have no effect
  ADTS0 = 0
  */
  ADCSRB = 0b00000000;
  return(void);
}

unsigned int aquire(void) {
  ADCSRA |= (1<<ADSC);
  while (BIT_IS_SET(ADCSRA, ADSC)) {}
  return (ADCH);
}