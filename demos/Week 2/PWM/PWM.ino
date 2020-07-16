int Red = 11;
int Green = 10;
int Blue = 9;
int POT = A0; // analog input for potentiometer
int ButtonRed = 4;
int ButtonGreen = 3;
int ButtonBlue = 2;
int colorSelect = 9; // initialize on Red channel


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // initialize the LED output pins
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);
  // initialize the potentiometer's analog input pin
  pinMode(POT, INPUT); 

  // initialize the button inputs
  pinMode(ButtonRed, INPUT);
  pinMode(ButtonGreen, INPUT);
  pinMode(ButtonBlue, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(POT);
  int potScaled = map(potValue, 0, 1023, 0, 255);
  Serial.println(potScaled);

  int buttonStateRed = digitalRead(ButtonRed);
  int buttonStateGreen = digitalRead(ButtonGreen);
  int buttonStateBlue = digitalRead(ButtonBlue);
  
  if(buttonStateRed == HIGH){
    colorSelect = Red;
    Serial.println(buttonStateRed);
  }
  if(buttonStateGreen == HIGH){
    colorSelect = Green;
    Serial.println(buttonStateGreen);
  }
  if(buttonStateBlue == HIGH){
    colorSelect = Blue;
    Serial.println(buttonStateBlue);
  }

  analogWrite(colorSelect, potScaled);
  
}
