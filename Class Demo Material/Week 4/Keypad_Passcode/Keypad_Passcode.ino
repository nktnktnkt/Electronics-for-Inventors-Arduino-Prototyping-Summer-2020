#include <Servo.h>
#include <Keypad.h>


const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};


char passCode[] = {'0', '5', 'A', '2'}; //an array containing the passcode
char enterCode[sizeof(passCode)]; //an array containing the entered code
int keyCount = 0;
bool passSuccess = false;
int ledCorrect = 11;
int ledWrong = 10;
int servoPin = 12;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(ledCorrect, OUTPUT);
  pinMode(ledWrong, OUTPUT);
  myServo.attach(servoPin);
  myServo.write(0);
}

void loop() {
  
  char enterKey = customKeypad.getKey(); //reads the last key entered

  if (enterKey) {
    Serial.println(enterKey);
    //add the entered key to the indexed slot in the array 
    //corresponding to the value of keyCount:
    enterCode[keyCount] = enterKey; 
    keyCount++; //increase keyCount to move to the next slot
  }
  
  //if the number of keys entered is greater or equal to those 
  //of the passCode, compare codes:
  if (keyCount >= sizeof(passCode)) {

    //compare each indexed slot in the two codes one by one, for the length of passCode:
    for (int i = 0; i < sizeof(passCode); i++) {
      
      if (enterCode[i] == passCode[i]) { 
        passSuccess = true; //if correct, set passSuccess 'true' and continue checking
        continue;
      } else {
        passSuccess = false; //if wrong, set passSucess 'false'
        break; //ends the for() loop prematurely, since it's wrong
      }
      
    }

    //if passSuccess remains 'true' after the code is analyzed above, 
    //do the thing and blink green:
    if (passSuccess == true) {
      digitalWrite(ledCorrect, HIGH);
      delay(100);
      digitalWrite(ledCorrect, LOW);
      delay(100);
      digitalWrite(ledCorrect, HIGH);
      delay(100);
      digitalWrite(ledCorrect, LOW);
      myServo.write(90); //rotate the servo to 90 degrees


    } else { //if not, don't do the thing and blink red:
      digitalWrite(ledWrong, HIGH);
      delay(100);
      digitalWrite(ledWrong, LOW);
      delay(100);
      digitalWrite(ledWrong, HIGH);
      delay(100);
      digitalWrite(ledWrong, LOW);
      myServo.write(0); //set servo to 0 degrees
    }

    //reset the keyCount and the enterCode for next time:
    keyCount = 0;
    char enterCode[sizeof(passCode)];
  }

  //if the '*' key is pressed, reset everything and blink LEDs:
  if (enterKey == '*') {
    myServo.write(0);
    char enterCode[sizeof(passCode)];
    keyCount = 0;
    digitalWrite(ledCorrect, HIGH);
    delay(100);
    digitalWrite(ledCorrect, LOW);
    delay(100);
    digitalWrite(ledWrong, HIGH);
    delay(100);
    digitalWrite(ledWrong, LOW);
  }

}
