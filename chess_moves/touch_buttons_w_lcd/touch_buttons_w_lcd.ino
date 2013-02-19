#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 8, 9, 10, 11, 13);


// http://playground.arduino.cc/Code/CapacitiveSensor

// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
#include "pins_arduino.h" // Arduino pre-1.0 needs this
uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
  if (*pin & bitmask) { 
    cycles =  0;
  }
  else if (*pin & bitmask) { 
    cycles =  1;
  }
  else if (*pin & bitmask) { 
    cycles =  2;
  }
  else if (*pin & bitmask) { 
    cycles =  3;
  }
  else if (*pin & bitmask) { 
    cycles =  4;
  }
  else if (*pin & bitmask) { 
    cycles =  5;
  }
  else if (*pin & bitmask) { 
    cycles =  6;
  }
  else if (*pin & bitmask) { 
    cycles =  7;
  }
  else if (*pin & bitmask) { 
    cycles =  8;
  }
  else if (*pin & bitmask) { 
    cycles =  9;
  }
  else if (*pin & bitmask) { 
    cycles = 10;
  }
  else if (*pin & bitmask) { 
    cycles = 11;
  }
  else if (*pin & bitmask) { 
    cycles = 12;
  }
  else if (*pin & bitmask) { 
    cycles = 13;
  }
  else if (*pin & bitmask) { 
    cycles = 14;
  }
  else if (*pin & bitmask) { 
    cycles = 15;
  }
  else if (*pin & bitmask) { 
    cycles = 16;
  }

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}





int rate = 1;
int button_pins[] = {7,2,3,4,5,6};
int button_hits[] = {0,0,0,0,0,0};
int num_buttons = 6;
int r = 0;

void check_buttons(){
  for(int i=0;i<num_buttons;i++){
    uint8_t pin_value = readCapacitivePin(button_pins[i]); 
    if( pin_value>1 ){
      button_hits[i] = 1;
    }
  }
}
void reset_buttons(){
  for(int i=0;i<num_buttons;i++){
    button_hits[i] = 0;
  }
}

void lcd_print_buttons(){
  lcd.setCursor(0, 0);

  lcd.print("[");
  for(int i=0;i<num_buttons;i++){
    lcd.print(button_hits[i], DEC);
    if(i<num_buttons-1){
      lcd.print(",");
    }else{
      lcd.println("]");
    }
  }
}




void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);

}

void loop(){
  check_buttons();
  if( r % 100 == 0 ){
    lcd_print_buttons();
    reset_buttons();
    r = 0;
  }
  r += 1;
  //delay(rate);
}


