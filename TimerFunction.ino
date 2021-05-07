const int ledPin3 =  9;
int ledStater = LOW;             


struct Timer{
  unsigned long previousMillis = 0;

  bool timer(long timespan) {  
    bool result = false;
    unsigned long currentMillis = millis(); 
    if (currentMillis - previousMillis >= timespan) {
      previousMillis = currentMillis;
      result = true;
    } 
    return result;
  }  
};



struct Timer ledtimer;
struct Timer ledtimer2;

void setup() {
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  
  /*if (ledtimer.timer(1000)) {//////////////////////////////////    
      if (ledStater == LOW) {
        ledStater = HIGH;
      } else {
        ledStater = LOW;
      }
      digitalWrite(ledPin3, ledStater);
  }////////////////////////////////////////////////////////////
*/
  //or
  if(ledtimer.timer(1000)){
    ledStater = !ledStater;
    digitalWrite(ledPin3, ledStater);
  }
}
