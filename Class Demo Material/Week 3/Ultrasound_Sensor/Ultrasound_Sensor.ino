int trigPin = 8; //define pin for sending out trigger pulses
int echoPin = 6; //define pin for listening to echo pulse
int LEDPin = 9; //PWM output to an LED
int tonePin = 10; //Audio output to a speaker 

float minDistance = 1; //minimum distance threshold (in approx. inches) for  ultrasound sensor
float maxDistance = 6; // maximum distance threshold

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
}

void loop() {
  float duration; //float allows decimal points up to 8 digits, rather than whole numbers like an integer. 
  float distance;

  //send out a quick pulse from the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //read how long it took to bounce back (in microseconds):
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 130; //Distance in inches. Calibrated from Serial monitor, 130 microseconds = approximately 1 inch

  //Map the LED PWM response exponentially, by squaring the input values and mapping that to the PWM output range:
  int LEDValue = map(sq(distance), sq(minDistance), sq(maxDistance), 0, 255); 

  //Control the LED and generate a tone if the ultrasound sensor detects something within the min and max distance range:
  if (distance >= minDistance && distance <= maxDistance) { 

    Serial.println(distance);
    analogWrite(LEDPin, LEDValue);

    //110 Hz is the pitch of note "A4" in western music theory. Multiplying this by an integer rounded value of "distance" 
    //allows for a stepped tuning of the notes into a harmonic series. Removing the int() function around "distance" allows it
    //to be a smooth transition between pitches, rather than stepped musical tones:
    tone(tonePin, 110 * int(distance)); 
    
  } else { //Do this if nothing is detected in the range:

    Serial.println("Out of Range");
    analogWrite(LEDPin, 0);
    noTone(tonePin); //Turn sound output off

  }



}
