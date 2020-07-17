int photocell = A0;
int LED = 10;
int lightMax = 900;
int lightMin = 300;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(photocell, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {
  int photoValue = analogRead(photocell);
  int photoScaled = map(photoValue, lightMax, lightMin, 0, 255);
  photoScaled = constrain(photoScaled, 0, 255);
  if(photoScaled < 65){
    photoScaled = 0;
   
  }
  Serial.println(photoValue);

  analogWrite(LED, photoScaled);

}
