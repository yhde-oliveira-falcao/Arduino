//CODE BY YURI FALCAO

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 8;   // the number of the pushbutton pin
const int ledPin = 5;      // the number of the LED pin
const int ledPin2 = 4;
 
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;  // the previous reading from the input pin
int led2State = LOW;

bool action = false;
 
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers



const int ledPin3 =  LED_BUILTIN;// the number of the LED pin
int ledStater = LOW;             // ledState used to set the LED
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)


const int ledPin10 =  10;// the number of the LED pin
int ledStaterr = LOW;             // ledState used to set the LED
unsigned long previousMilliss = 0;        // will store last time LED was updated
const long intervall = 333; 


const int ledPin11 =  11;// the number of the LED pin
int ledStaterrr = LOW;             // ledState used to set the LED
unsigned long previousMillisss = 0;        // will store last time LED was updated
const long intervalll = 500; 

 
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin, ledState);


    pinMode(ledPin3, OUTPUT);

      pinMode(ledPin10, OUTPUT);

  pinMode(ledPin11, OUTPUT);


}
               
void loop() { //The debouncing is very "extremely very important" because it controls the buttons press time
               //making it less succeptible to errors. This is very important to change states with one button only! 
  //BEGIN OF DEBOUNCING
  int reading = digitalRead(buttonPin);//READ THE BUTTON
 
  if (reading != lastButtonState) { 
    lastDebounceTime = millis(); //START TO COUNT PRESS TIME... 
  }
 
  if ((millis()/*TIME RIGHT NOW*/ - lastDebounceTime/*CHECK ABOVE*/) > debounceDelay/*10*/) { //IF PRESS TIME IS BIGGER THAN 10ms

    if (reading != buttonState) { //Check the end of the debouncing to understand this condition.
      buttonState = reading; //Save the current state of the button
 
      if (buttonState == HIGH) { //check if the current state of the button is high
        ledState = !ledState; //turn on if off or the contrary if the button is high (this only happens if the time is > 10 ms
        action = !action; //This is a boolean flag I created for later use to call a function...(notice that a button can 
                          //do many tasks at the same time.
      }
    }
  }
 
  digitalWrite(ledPin, ledState);
 
  lastButtonState = reading; //Save the button state for the next reading... 
  //END OF DEBOUNCING

  if (action){ //here I called the boolean flag "action" to control a led... (but i could have called a menu, or a motor...
    digitalWrite(ledPin2, HIGH); 
  } else {
    digitalWrite(ledPin2, LOW);
  }

  //INTERESTING: since the MCU runs in a loop(goes through this code many times per second), if we put a variable++ operation
  //without locking it inside a "run-once" function it will keep adding forever and the operation won't make sence...
  //To avoind this try creating a condition that only operates if a number is acieved...(like: summer++; if(summer == 5){...}
  //but remember to reset the summer inside the condition so it can be called again...
  // it can also be done with a specific time after millis() : check the led blink to understand
//===============================================================


 unsigned long currentMillis = millis();//Function to blink led... It must have its own variable as every 
                                          //time division and led states are individual for each singular led

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledStater == LOW) {
      ledStater = HIGH;
    } else {
      ledStater = LOW;
    }
    digitalWrite(ledPin3, ledStater);
  }
  ///////////////////////////////////////////////////////////////////////////

// LED BLINK!!! <<<<< 
  unsigned long currentMilliss = millis(); //Function to blink led... It must have its own variable as every 
                                          //time division and led states are individual for each singular led

  if (currentMilliss - previousMilliss >= intervall) {
    previousMilliss = currentMilliss;

    if (ledStaterr == LOW) {
      ledStaterr = HIGH;
    } else {
      ledStaterr = LOW;
    }
    digitalWrite(ledPin10, ledStaterr);
  }
///---------------------------------------------------------------------------

  unsigned long currentMillisss = millis();//Function to blink led... It must have its own variable as every 
                                          //time division and led states are individual for each singular led
  if (currentMillisss - previousMillisss >= intervalll) {
    previousMillisss = currentMillisss;
    ledStaterrr = !ledStaterrr; //Same as IF ELSE statement above... (but only one code line :D)
    digitalWrite(ledPin11, ledStaterrr);
  }//Note that this function is very simple and only require 5 code lines...
}
