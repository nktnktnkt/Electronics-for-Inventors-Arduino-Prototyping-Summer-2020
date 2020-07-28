#include <Servo.h>
#include <IRremote.h>

int recvPin = 10;
int servoPos = 0;

IRrecv irrecv(recvPin);
decode_results results;

Servo myservo;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  myservo.attach(3);
  myservo.write(servoPos);

}

void loop() {

  if (irrecv.decode(&results)) {

    Serial.println(results.value, HEX);
    irrecv.resume();

    if(results.value == 0xFF30CF){ //1 button
      servoPos = 45; //servo position in degrees
    }
    
    if(results.value == 0xFF18E7){ //2 button
      servoPos = 100;
    }
    if(results.value == 0xFF7A85){ //3 button
      servoPos = 180;
    }
    
    if(results.value == 0xFF6897){ //0 button
      servoPos = 0;
    }
    if(results.value == 0xFF906F){ //+ button
      servoPos += 10;
    }
    if(results.value == 0xFFA857){ //- button
      servoPos -= 10;
    }
    
  }
  myservo.write(servoPos); //can be degrees between 0 and 180
  
}
