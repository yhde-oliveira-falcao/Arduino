//CODE BY YURI FALCAO (You won't find something similar...)
//Ongoing project (This is just the bone structure to hold the functionalities of an intrument.
//Please, if you are going to use, aknowledge me as the source, it took some weeks to make (again, you won't find this anywere else).
//Feel free to improve and send me feedback. 

//Also, if there are many funcitons running or even in the current situation, implement a watchdog (IMPORTANT)

#include <LiquidCrystal.h>

struct buttonPin { //Just the buttonPin variables. =================================== BEGIN 1 
  const int buttonPin;
  int buttonState;
  int lastButtonState;
  int stater;
  int counter;

  unsigned long lastDebounceTime;
  unsigned long debounceDelay;

  int buttonFunc(){
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == HIGH) {
          stater = !stater; //----------------
          counter++;
        }
      }
    }
    lastButtonState = reading;
    return stater;
  };
}; //THIS FUNCTION GOES TO THE LIBRARY =============================================   END 1


struct Timer{ //THIS FUNCTION GOES TO THE LIBRARY =============================================   BEGIN 2
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
};//THIS FUNCTION GOES TO THE LIBRARY =============================================   END 2

struct Timer ledtimer;

struct Timer countTimer;
struct Timer welcomeTimer;

struct buttonPin button1 = {8, LOW, HIGH, HIGH, 0, 0, 10};
struct buttonPin button2 = {7, LOW, HIGH, HIGH, 0, 0, 10};
struct buttonPin button3 = {6, LOW, HIGH, HIGH, 0, 0, 10};
struct buttonPin button4 = {5, LOW, HIGH, HIGH, 0, 0, 10};

const int led = 9/*LED_BUILTIN*/;
int ledState = LOW;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(47, 48, 49, 50, 51, 52);

int flag = 0;

bool ledTest = false;

void setup() {
  pinMode(button1.buttonPin, INPUT_PULLUP);
  pinMode(button2.buttonPin, INPUT_PULLUP);
  pinMode(button3.buttonPin, INPUT_PULLUP);
  pinMode(button4.buttonPin, INPUT_PULLUP);
  //pinMode(led, OUTPUT);
  //digitalWrite(led, ledState);
  //Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {

  Intro();
  
  int reader1 = button1.buttonFunc();
  int reader2 = button2.buttonFunc();
  int reader3 = button3.buttonFunc();
  int reader4 = button4.buttonFunc();
  
  mainMenu();
  //
  ledBlinker();
  
  //HERE WE CALL THE TEMP AND RPM FUNCTION
  //HERE WE CALL ALL OTHER AUTOMATIC FUNCTIONS (IF THEY ARE ACTIVATED THEY WILL BE DONE, IF NOT, NO.)
  //HERE WE CALL BATTERY AND SAFETY CHECKS
  //HERE WE CALL INTERNET REQUEST CHECK
  //HERE WE CALL TIME (UPDATE WITH INTERNET???)

  //ALL THE ACTION FUNCTIONS SHOULD BE CALLED HERE <-------------------<<<
  //YES, IT WILL BE TOO MANY, BUT YES... ALL SHOULD BE CALLED HERE. TAKE A LOOK AT THE 
  //LEDBLINKER FUNCION TO SEE HOW IT WORKS....

}

void Intro(){
  while(millis() < 1000){ //Welcome message!!! use while!!!
    lcd.setCursor(0,0);
    lcd.print("  Welcome to"); 
    lcd.setCursor(0,1);       
    lcd.print("Menu Debugger");  
  }//================================================================
}

void mainMenu(){
  
    switch (button1.counter){ //   FUNTION MAIN MENU!!!  This is the down arrow button (to go down (through) in the menu)
      case 1: {
        button1.counter = 1;
        button3.counter = 1;
        lcd.setCursor(0,0);
        lcd.print("Temp:          "); //HERE WE PRINT THE TEMP AND RPM READINGS
        lcd.setCursor(0,1);        //HERE WE CALL THE MENU OFFER.
        lcd.print("RPM:          ");  
        break;
      }
      case 2: {
        tempRPM();
        lcd.setCursor(0,1);
        lcd.print("pH Tester   ");
        break;
      }
      case 3: {
        tempRPM();
        lcd.setCursor(0,1);
        lcd.print("Conductivity");
        break;
      }
      case 4: {
        tempRPM();
        lcd.setCursor(0,1);
        lcd.print("Potentiometry");
        break;
      }
      case 5:{
        tempRPM();
        lcd.setCursor(0,1);
        lcd.print("Timer         ");
        break;
      }
      case 6: {
        tempRPM();
        lcd.setCursor(0,1);
        lcd.print("Temp Ramp  ");
        break;
      }
      case 7: {
        tempRPM();
        lcd.setCursor(0,1);
        lcd.print("Settings    ");
        break;
      }
      case 8: {
        tempRPM();
        lcd.setCursor(0,1);
        lcd.print("Alarm set  ");
        break;
      }//Add the internet menu case...
      case 9: {
        button1.counter = 1;
        break;
      }
      case 10: {
        lcd.setCursor(0,0);
        lcd.print("Calibrate  ");
        lcd.setCursor(0,1);
        lcd.print("Start Analysis");
        break;
      }
      case 11: {
        lcd.setCursor(0,0);
        lcd.print("Start Analysis");
        lcd.setCursor(0,1);
        lcd.print("Timer Set");
        break;
      }
      case 12: {
        lcd.setCursor(0,0);
        lcd.print("Blink led?");
        lcd.setCursor(0,1);
        lcd.print("Return MainMenu ");
        break;
      }
      case 13: {
        lcd.setCursor(0,0);
        lcd.print("Return MainMenu ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        break;
      }
      case 14: {
        button1.counter = 10;
        break;
      }
      case 15: {                       //Action activator case ********
        ledTest = true;
        button1.counter = 10;
        break;
      }
    }    
    
    if(button2.counter > 1 && button1.counter > 1){ //This is the up arrow (to go back (up) in the menu)
      button1.counter--;
      button2.counter = 1; //This function is buggy!!!
    }

    
    if(button3.counter > 1 && button1.counter == 2){
      button1.counter = 10;
      button3.counter = 1;
    } else 
    if(button3.counter > 1 && button1.counter == 13){
      button1.counter = 1;
      button3.counter = 1;
    } 
    if(button3.counter > 1 && button1.counter == 12){ //Blink LED
      button1.counter = 15;
      button3.counter = 1;
    } else
    {
      button3.counter = 1;
    }
}

void tempRPM(){
  lcd.setCursor(0,0);
  lcd.print("Temp:    RPM:   "); //HERE WE PRINT THE TEMP AND RPM READINGS
}


void ledBlinker(){
  if(ledTest){
    if(ledtimer.timer(1000)){
      ledState = !ledState;
      digitalWrite(led, ledState);
    }
  }
}








  
