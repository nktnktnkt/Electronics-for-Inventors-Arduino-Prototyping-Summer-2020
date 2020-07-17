int photocell = A0;
int LED = 10;
int lightMax = 900; //calibrate the maximum photocell reading in your light conditions
int lightMin = 300; //minimum in your light conditions

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //make sure your serial monitor baud rate matches this value
  pinMode(photocell, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {
  int photoValue = analogRead(photocell); //read the raw data from the photocell
  Serial.println(photoValue); //display the input from the photocell to the serial monitor, to find the lightMin and Lightmax values

  int photoScaled = map(photoValue, lightMax, lightMin, 0, 255); //scale the photocell input to a new range, 0-255, and flip the polarity
  photoScaled = constrain(photoScaled, 0, 255); //constrain the values so they are never over or under 0-255

  //set the value to 0 if photoScaled reads less than 65
  if (photoScaled < 65) { 
    photoScaled = 0;

  }

  //control the brightness of the LED with the scaled input from the photocell, using PWM.
  analogWrite(LED, photoScaled);

}
