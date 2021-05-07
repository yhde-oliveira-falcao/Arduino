const int btnPin = 8;                                     // Number of the pushbutton pin
const int ledPin = 5;                                    // Number of the LED pin

int currentLedState;                                      // Current and previous states of output LED pin
int previousLedState;
int currentBtnState;                                      // Current and previous states of input Button pin
int previousBtnState;


unsigned int count;                                       // Rising edge count of LED state
unsigned int lastDebounceTime;
unsigned int debounceDelay;                               // Delay time

void setup() {

    pinMode(btnPin, INPUT);
    pinMode(ledPin, OUTPUT);

    currentLedState = LOW;
    previousLedState = LOW;
    currentBtnState = LOW;
    previousBtnState = LOW;

    count = 0;
    lastDebounceTime = 0;
    debounceDelay = 50;

    Serial.begin(9600);

}

void loop() {

    currentBtnState = digitalRead(btnPin);

    if (currentBtnState != previousBtnState) {

        lastDebounceTime = millis();
        // every time the button state changes, get the time of that change
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {

        /*
        *if the difference between the last time the button changed is greater
                *than the delay period, it is safe to say
                *the button is in the final steady state, so set the LED state to
                *button state.
        */
        currentLedState = currentBtnState;

    }



    // ********************* start functional code **************************************





    // verification code, and a button press counter

    if ((previousLedState == LOW) && (currentLedState == HIGH)) {
        //count rising edges
        count++;
        Serial.println(count);
    }




    // ********************* end functional code **************************************



    // set current states to previous states
    digitalWrite(ledPin, currentLedState);
    previousBtnState = currentBtnState;
    previousLedState = currentLedState;
}
