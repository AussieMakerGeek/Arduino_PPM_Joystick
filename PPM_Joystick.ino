/*This program puts the servo values into an array,
 reagrdless of channel number, polarity, ppm frame length, etc...
 You can even change these while scanning!*/
 

#define PPM_Pin 3  //this must be 2 or 3
#define multiplier (F_CPU/8000000)  //leave this alone
int ppm[16];  //array for storing up to 16 servo signals

void setup()
{
  pinMode(A1, INPUT_PULLUP);  // Initialize the button pin
  
  //Serial.begin(115200);
  //Serial.println("ready");

  pinMode(PPM_Pin, INPUT);

  attachInterrupt(PPM_Pin - 2, read_ppm, CHANGE);

  TCCR1A = 0;  //reset timer1
  TCCR1B = 0;
  TCCR1B |= (1 << CS11);  //set timer1 to increment every 0,5 us
  Joystick.begin();  // init joystick with 'autosendvalues' enabled
}

void loop()
{
	  // CH 1 
    Joystick.setXAxis(map(ppm[0],1000,2000, -127, 127));
    // CH 2 
    Joystick.setYAxis(map(ppm[1],1000,2000, -127, 127));
    // CH 3 
    Joystick.setZAxis(map(ppm[2],1000,2000, -127, 127));
    // CH 4 (PIN 16)
    //Joystick.setXAxisRotation(map(rc_values[3],rc_min_values[3],rc_max_values[3], 0, 360));
    // CH 5 (PIN 14)
    Joystick.setThrottle(map(ppm[3],1000,2000, 0, 255));
    // CH 6 (PIN 15)
    Joystick.setRudder(map(ppm[4],1000,2000, 0, 255));
}



void read_ppm(){  //leave this alone
  static unsigned int pulse;
  static unsigned long counter;
  static byte channel;
  static unsigned long last_micros;

  counter = TCNT1;
  TCNT1 = 0;

  if(counter < 710*multiplier){  //must be a pulse if less than 710us
    pulse = counter;
  }
  else if(counter > 1910*multiplier){  //sync pulses over 1910us
    channel = 0;
  }
  else{  //servo values between 710us and 2420us will end up here
    ppm[channel] = (counter + pulse)/multiplier;
    channel++;
  }
}

