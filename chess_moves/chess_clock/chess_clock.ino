// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// Use layout from 
// http://learn.adafruit.com/character-lcds/using-a-character-lcd
LiquidCrystal lcd(12, 8, 9, 10, 11, 13);

//////////////

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
///////////////////



// 
long start_time;
long last_check_time;
long pause_time;
long board1_w_clock; //time spent: from 0 to max_time (loss)
long board1_b_clock;
long board2_w_clock;
long board2_b_clock;
long max_time = 60 * 3 * 1000L ; //in millis
//long max_time = 60 * 1000L ; //in millis

const int WHITE_MOVE = 0;
const int BLACK_MOVE = 1;
int board1move = WHITE_MOVE; //0 - white, 1 - black
int board2move = WHITE_MOVE; //0 - white, 1 - black
boolean pause = false; //pause doesn't advance clocks
int victor = 0;

void show_clock();

void reset_game(){
  reset_clock();
  victor = 0;
  board1move = WHITE_MOVE;
  board2move = WHITE_MOVE;
  lcd.clear();
}

void reset_clock(){
  start_time = millis();
  last_check_time = start_time;
  pause_time = start_time;
  pause = true;
  board1_w_clock = 0;
  board1_b_clock = 0;
  board2_w_clock = 0;
  board2_b_clock = 0;
  lcd.clear();
  show_clock();
}

void pause_clock(){
  pause_time = millis();
}

void resume_clock(){
  last_check_time += (millis() - pause_time);
}

void increment_clock(){
  if(pause) return;
  long timenow = millis();
  long increment = timenow - last_check_time;
  if( board1move == WHITE_MOVE ){
    board1_w_clock += increment;
  }else{
    board1_b_clock += increment;
  }
  
  if( board2move == WHITE_MOVE ){
    board2_w_clock += increment;
  }else{
    board2_b_clock += increment;
  }
  last_check_time = timenow;
}

void show_ttl( long time_cap, long clock ){
  long ttl = (time_cap - clock) / 1000;
  lcd.print(ttl / 60);
  lcd.print(":");
  long sec = ttl % 60;
  if( sec < 10 ){
    lcd.print("0");
  }
  lcd.print(sec);
  
}

void show_clock(){
  lcd.clear();
  if( ! game_over() ){
    if(board1move == WHITE_MOVE){
      lcd.setCursor(0, 0);
      lcd.print(">");
    }else{
      lcd.setCursor(15, 0);
      lcd.print("<");
    }
    if(board2move == WHITE_MOVE){
      lcd.setCursor(15, 1);
      lcd.print("<");
    }else{
      lcd.setCursor(0, 1);
      lcd.print(">");
    }
  }
  
  lcd.setCursor(3, 0);
  show_ttl( max_time, board1_w_clock );

  lcd.setCursor(9, 0);
  show_ttl( max_time, board1_b_clock );

  lcd.setCursor(3, 1);
  show_ttl( max_time, board2_b_clock );
  // print the number of seconds since reset:
  lcd.setCursor(9, 1);
  show_ttl( max_time, board2_w_clock );
}

void print_victory(){
  if(victor == 1){
    lcd.setCursor(0, 0);
    lcd.print("WON");
    lcd.setCursor(0, 1);
    lcd.print("WON");
  }else{
    lcd.setCursor(13, 0);
    lcd.print("WON");
    lcd.setCursor(13, 1);
    lcd.print("WON");
  }
}

boolean check_victory(){
  if( (board1_w_clock >= max_time) || (board2_b_clock >= max_time) ){
    victor = 2; //side 1
    return true;
  }
  if( (board2_w_clock >= max_time) || (board1_b_clock >= max_time) ){
    victor = 1; //side 1
    return true;
  }
  return false;
}


///////////////////

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

void serial_print_buttons(){
  Serial.print("[");
  for(int i=0;i<num_buttons;i++){
    Serial.print(button_hits[i], DEC);
    if(i<num_buttons-1){
      Serial.print(",");
    }else{
      Serial.println("]");
    }
  }
}

boolean game_over(){
  return victor > 0;
}


void check_button_actions(){
  serial_print_buttons();
  if(button_hits[0]){
    //pause/unpause
    pause = !pause;
    if(pause){
      pause_clock();
    }else{
      resume_clock();
    }
  }
  if(button_hits[1]){
    //reset
    if(pause){
      reset_game();
    }
  }
  if( game_over() ) return;
  
  if( board1move == WHITE_MOVE ){
    if(button_hits[2]){
      board1move = BLACK_MOVE;
    }
  }else{
    if(button_hits[3]){
      board1move = WHITE_MOVE;
    }
  }
  if( board2move == WHITE_MOVE ){
    if(button_hits[4]){
      board2move = BLACK_MOVE;
    }
  }else{
    if(button_hits[5]){
      board2move = WHITE_MOVE;
    }
  }
}

void setup() {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");

  reset_game();
}


void loop() {
  if( r % 10 == 0 ){
    // high level loop happens on every 100th tick 
    show_clock();
    if(victor>0){
      print_victory();
    }
    increment_clock();
    if(!pause && check_victory()){
      pause = true;
      print_victory();
    }
    check_button_actions();
    reset_buttons();
    r = 0;
    delay(100);
  }
  check_buttons();
  r+=1;
}

