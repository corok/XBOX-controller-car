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
int headLightsPin = 22; // Example pin for headlights
int reverseLightsPin = 23; // Example pin for reverse lights
int brakeLightsPin = 25; // Example pin for brake lights
int turnSignalLeftPin = 26; // Example pin for left turn signal
int turnSignalRightPin = 27; // Example pin for right turn signal

float steering =0.0;
float throttle = 0.0;

bool leftTurn = false;
bool rightTurn = false;
bool headLights = false;
bool reverseLights = false;
bool brakeLights = false;
XboxControlsState s;

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
    if(s.rightBumper){
      printf("Right Bumper Pressed\n");
    }
    Serial.printf("Steering: %.2f, Throttle: %.2f\n",
      steering, throttle);
  } else {
    Serial.println("controller not connected");
  }
  lights();
}
// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

void lights(){
    if(throttle==0){
      brakeLights = true;
    }else{
      brakeLights = false;
    }

    if(s.dpadLeft&&leftTurn==false){
      leftTurn = !leftTurn;
    }

    if(s.dpadRight&&rightTurn==false){
      rightTurn = !rightTurn;
    }

    if(s.buttonA){
      headLights = !headLights;
    }


  digitalWrite(brakeLightsPin, brakeLights ? HIGH : LOW);
  
  digitalWrite(turnSignalLeftPin, leftTurn ? HIGH : LOW);
  
  digitalWrite(turnSignalRightPin, rightTurn ? HIGH : LOW);
  
  digitalWrite(headLightsPin, headLights ? HIGH : LOW);

  digitalWrite(reverseLightsPin, reverseLights ? HIGH : LOW);
}