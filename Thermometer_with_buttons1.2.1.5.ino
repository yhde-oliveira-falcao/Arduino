
#include <LiquidCrystal.h>

//Defining the LCD ==================================================================
int tempPin = 0;
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//Defining the LCD ==================================================================
//-------------------------------------------------------------------------------------


//Defining a pin for LED ===========================================================
int ledPin = 6;
//Defining a pin for LED ===========================================================
//-------------------------------------------------------------------------------------

//Defining a pin for DC M===========================================================
#define ENABLE 5
#define DIRA 3
#define DIRB 4

int i;
int counter = 0;
//Defining a pin for DC M===========END=============================================
//-------------------------------------------------------------------------------------


//Defining the pin for the buttons===================================================
const int analogInPin = A5;
const int outPin = 13; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the buttons
int state = 0;              // used for storing what button was pressed
//Defining the pin for the buttons===================================================
//-------------------------------------------------------------------------------------


void setup()
{
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);         //Initialize the LCD from 2 to 16???
  Serial.begin(9600);       // initialize serial communications at 9600 bps
  pinMode(outPin, OUTPUT);  // set pin 13 as an output

  //DC MOTOR PART========
   //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}

void loop()//===========================================LOOP===========================================================================
{
  
  int tempReading = analogRead(tempPin);   //Create a variable to the tem reading pin

  //Calculating/Transforming the data from the thermometer sensor.====================
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
 
  //Calculating/Transforming the data from the thermometer sensor.====================

  // Display Temperature in C=========================================================
  lcd.setCursor(0, 0);
  lcd.print("Temp         C  ");
  // Display Temperature in F
  //lcd.print("Temp         F  ");
  lcd.setCursor(7, 0); //counts from 0 to 15.
  lcd.print(tempC);
  // Display Temperature in C=========================================================

  // HIGH TEMP LED INDICATOR =========================================================
  if (tempC > 30) {
    digitalWrite(ledPin, HIGH);
  }
  else if (tempC < 30) {
    digitalWrite(ledPin, LOW);
  }
  // HIGH TEMP LED INDICATOR =========================================================
  
  readSwitch();

  if (state == 0) {     //encapsulate this shit!!!+++++++++++++++++++++++++++++++++++++++++++                    
    //digitalWrite(outPin, LOW);
     lcd.setCursor(0, 1); 
     lcd.print("Oi butao 1!!!");
     digitalWrite(ledPin, HIGH);
      // digitalWrite(ENABLE,LOW); //MOTOR OFF
      // counter = 1;

    readSwitch();                        
  }

  if (state == 1) {                         
    lcd.setCursor(0, 1);  
    lcd.print("Oi butao 2!!!");
    digitalWrite(ledPin, HIGH);
  //  digitalWrite(ENABLE,LOW); //MOTOR OFF
    //counter = 2;
    readSwitch();
  }

  if (state == 2) {                         
    lcd.setCursor(0, 1);  
    lcd.print(counter);
    digitalWrite(ledPin, HIGH);
    //digitalWrite(ENABLE,LOW); //MOTOR OFF

    readSwitch();
  }

  if (state == 3) {                         
    lcd.setCursor(0, 1); 
    lcd.print("Oi butao 4!!!");
    digitalWrite(ledPin, HIGH);
    counter+=1;
  //==============MOTOR======================
    //digitalWrite(ENABLE,HIGH); // enable on
    //digitalWrite(DIRA,HIGH); //MOTOR HIGH!
    //digitalWrite(DIRB,LOW);
    motorState(counter); //The problem is because of the millisecond the button is pressed.... there is a video about
    //turning one button into many functions... super important.... then.... if the press is less than 5 secons (ex) then counter goes ++, if more than 5 seconds then do
    //some given special function.... super nice and dificult!
    //You can also see the example Ive saved of the Arduino websit about the buton state, if it is different from the previous than counter ++....
  //==============END OF MOTOR===============
    readSwitch();
  }
  
  if (state == 5)  {
    lcd.setCursor(0, 1); 
    lcd.print("Select Menu");
    readSwitch();
    digitalWrite(ledPin, LOW);
    //digitalWrite(ENABLE,LOW); //MOTOR OFF

  }//encapsulate this shit!!!+++++++++++++++++++++++++++++++++++++++++++++
  
}// end of the loop ==============================================LOOP================================================================


//Function to assign values for each button!!! ========================================================================================
void readSwitch () {                                  //creates the function to read the switch states
  sensorValue = analogRead(analogInPin);              //read the analog pin the switches are connected to 
  if (sensorValue < 800 && sensorValue > 750) {       //if the analog reading is within a certain range we know which button was pressed and set the state accordingly
    state = 0;
    //delay(10);                                       //delay for debounce purposes
  }
  if (sensorValue < 749 && sensorValue > 650) {       //if the analog reading is within a certain range we know which button was pressed and set the state accordingly
    state = 1;
    //delay(10);                                       //delay for debounce purposes
  }
  if (sensorValue < 649 && sensorValue > 425) {       //if the analog reading is within a certain range we know which button was pressed and set the state accordingly
    state = 2;
   // delay(10);                                       //delay for debounce purposes
  }
  if (sensorValue < 425 && sensorValue >= 0) {        //if the analog reading is within a certain range we know which button was pressed and set the state accordingly
    state = 3;
  //  delay(10);                                       //delay for debounce purposes
  }
  if (sensorValue >= 810) {        //if the analog reading is within a certain range we know which button was pressed and set the state accordingly
    state = 5;
   // delay(1);                                       //delay for debounce purposes
  }
 // delay(1);                                           //delay for timeing purposes
  
}
//Function to assign values for each button!!! ========================================================================================

void motorState(int counter){
  if (counter % 2 == 0){
     digitalWrite(ENABLE,HIGH); // enable on
    digitalWrite(DIRA,HIGH); //MOTOR HIGH!
    digitalWrite(DIRB,LOW);
  } else {
   
    digitalWrite(ENABLE,LOW); //MOTOR OFF
  }
}
