int lightSensor = A0;
int tuner = A2;
int modulator = A1;
int lightLow = 400; //set the lowest value the light sensor (photocell) outputs
int lightHigh = 900; // set the highest value the light sensor outputs.
int button = 2;
int buzzer = 11;

void setup() {
  Serial.begin(57600); //must set set this baud rate in the serial monitor as well for propper function
  pinMode(buzzer, OUTPUT);
  pinMode(tuner, INPUT);
  pinMode(lightSensor, INPUT);
  pinMode(modulator, INPUT);
  pinMode(button, INPUT);
}

void loop() {
  //read the tuner pot to set the master pitch of the piezo speaker
  int tunerValue = analogRead(tuner);
  int delayed = map(tunerValue, 0, 1023, 0, 15000);

  //read the light sensor value to control the harmonic tuning of the audio waveform relative to the master tuning, creating simple melodies.
  int lightValue = analogRead(lightSensor);
  Serial.println(lightValue); //use this reading to determine lightHigh and lightLow values
  int melody = map(lightValue, lightLow , lightHigh, 0, 10);
  melody = constrain(melody, 0, 10);

  //read the modulator pot to modify the PWM state of the audio signal, creating a FM (frequency modulation) effect on the sound.
  int modValue = analogRead(modulator);
  int freqShift = map(modValue, 0 , 1023, 0, 100);

  //read the push button's state to turn on and off the piezo output. The piezo will only make noise when the button is pushed down.
  int buttonState = digitalRead(button);


  //Push the button to generate audio, with the "delayMicroseconds" controling the duty cycle length of the waveform, which changes the percieved pitch
  if (buttonState == HIGH) {
    analogWrite(buzzer, 255); //crest of the audio waveform
    delayMicroseconds(delayed / melody);

    analogWrite(buzzer, freqShift); //trough of the audio waveform
    delayMicroseconds(delayed / melody);
  } else {
    analogWrite(buzzer, 0);

  }

}
