void timer0init(void) {
    /*
	TCCR0A - Timer/Counter 0 Control Register A
	
	bit           7         6         5         4        3       2        1        0
	name        COM0A1    COM0A0    COM0B1    COM0B0     -       -      WGM01    WGM00
	set to        0         0         0         0        0       0        1        0
	
	COM0A1 = 0    normal port operation, OC0A disconnected
	COM0A0 = 0
	
	COM0B1 = 0    normal port operation, OC0B disconnected
	COM0B0 = 0
	
	bit 3 = 0
	bit 2 = 0
	
	WGM01 = 1     CTC (Clear Timer on Compare match) mode, see TCCR0B also
	WGM00 = 0     TCNT0 will count up to value in OCR0A, then signal timer 0 compare interrupt
    */
    TCCR0A = 0b00000010;
	
    /*
	TCCR0B - Timer/Counter 0 Control Register B
	
	bit           7          6        5       4         3         2         1        0
	name        FOC0A      FOC0B      -       -       WGM02      CS02      CS01     CS00
	set to        0          0        0       0         0         1         0        1
	
	FOC0A = 0     don't use Force Output Compare A
	FOC0B = 0
	
	bit 5 = 0
	bit 4 = 0
	
	WGM02 = 0     CTC (Clear Timer on Compare match) mode, see TCCR0A also
	
	CS02 = 1
	CS01 = 0      clock / 1024
	CS00 = 1
    */
    TCCR0B = 0b00000101;
	
	/*
	TIMSK0 - Timer/Counter 0 Interrupt Mask Register
	
	bit           7        6        5       4       3       2         1         0
	name          -        -        -       -       -     OCIE0B    OCIE0A    TOIE0
	set to        0        0        0       0       0       0         1         0
	
	bit 7 = 0     don't use Force Output Compare A
	bit 6 = 0
	bit 5 = 0
	bit 4 = 0
	bit 3 = 0
	OCIE0B = 0    don't enable Timer/Counter 0 Output Compare Match B Interrupt
	OCIE0A = 1    enable Timer/Counter 0 Output Compare Match A Interrupt Enable
	TOIE0 = 0     don't enable Timer/Counter 0 Overflow Interrupt
    */
    TIMSK0 = 0b00000010;
    
    OCR0A = 0b10000000;
    return(void);
}

