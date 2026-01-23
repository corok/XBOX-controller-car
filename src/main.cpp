#include <Arduino.h>
#include <BLEGamepadClient.h>
#include <ESP32Servo.h>
// put function declarations here:
int myFunction(int, int);
XboxController controller;
Servo steerServo;
int steeringPin = 5; // Example pin for steering servo
int motorSpeedPin = 18; // Example pin for motor speed (PWM)
int motorDirPin = 19;   // Example pin for motor direction
int motorDirPin2 = 21;  // Example pin for motor direction
float steering =0.0;
float throttle = 0.0;
int LED = 16;
void setup() {
  controller.begin();
  Serial.begin(115200);
  pinMode(motorSpeedPin, OUTPUT);
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorDirPin2, OUTPUT);
  steerServo.attach(steeringPin); // Example pin for steering servo
}

void loop() {
  delay(10);
  if (controller.isConnected()) {
    XboxControlsState s;
    controller.read(&s);

    steering = s.leftStickX;
    
    throttle = s.rightTrigger-s.leftTrigger;

    if(throttle>0){
      digitalWrite(motorDirPin, HIGH);
      digitalWrite(motorDirPin2, LOW);
    }else{
      digitalWrite(motorDirPin, HIGH);
      digitalWrite(motorDirPin2, LOW);
    }
    analogWrite(motorSpeedPin, abs(throttle)*254);
    steerServo.write(steering*45);

    Serial.printf("Steering: %.2f, Throttle: %.2f\n",
      steering, throttle);
  } else {
    Serial.println("controller not connected");
  }
}
// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}