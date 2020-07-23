#include <IRremote.h>

int redPin = 6, greenPin = 5, bluePin = 3;
int recvPin = 2;
float counter = 0;
bool oscillation = false;
IRrecv irrecv(recvPin);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {

  if (irrecv.decode(&results)) {

    Serial.println(results.value, HEX);

    if (results.value == 0xFF30CF) { //if "1" is pressed, turn on red LED;
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
    }
    if (results.value == 0xFF18E7) { //if "2" is pressed, turn on green LED;
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
    }
    if (results.value == 0xFF7A85) { //if "3" is pressed, turn on blue LED;
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, HIGH);
    }
    if (results.value == 0xFF6897) { //if "4" is pressed, turn off all LEDs;
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      oscillation = false;
    }
    if (results.value == 0xFF9867) {
      oscillation = true;
    }
    irrecv.resume();
  }

  //If oscillation is set to true, create a pulsing light on the red channel:
  if (oscillation == true) {
    counter = counter + (TWO_PI / 360); //counter counting up in "radians" of a 360 degrees cycle
    if (counter > TWO_PI) {
      counter = 0;
    }
    Serial.println(counter);
    float oscil = sin(counter); //trigonomic function to ouput a sine wave with values between -1 and 1
    int oscilScaled = map(oscil * 360, -360, 360, 0, 255); //scale the sine function to our PWM range
    analogWrite(redPin, oscilScaled);

  }



}
