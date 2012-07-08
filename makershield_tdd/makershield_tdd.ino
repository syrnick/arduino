
int POT = 1;
int LED1 = 2;
int LED2 = 3;
int BUTTON = 4;

int rate=100;

const int STATE_OFF = 0;
const int STATE_ON = 1;
int state = STATE_ON;


void setup(){
  Serial.begin(9600);

  pinMode(POT, INPUT);
  pinMode(BUTTON, INPUT);  
  digitalWrite(BUTTON, HIGH);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

int transition_counter = 0;

void loop(){
  int pot = 0;
  int button_value = digitalRead(BUTTON);
  Serial.print("button: ");
  Serial.println(button_value, DEC);
  if(button_value == 0){
    transition_counter += 1;
  }else{
    transition_counter = 0;
  }
  if(transition_counter > 1000 / rate){
    state = 1 - state; //ok for two states only
    transition_counter = 0;
  }
  switch( state ){
    case STATE_ON:
      pot = analogRead(POT);
      Serial.print("pot: ");
      Serial.println( pot, DEC );
      digitalWrite(LED1, HIGH); 
      analogWrite(LED2, pot/4);
      break;
    case STATE_OFF:
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, LOW); 
      break;
  }
  delay(rate);
}
