#include <Arduino.h>
#include <BLEGamepadClient.h>
#include <ESP32Servo.h>
// put function declarations here:
int myFunction(int, int);
XboxController controller;
Servo Steering;
int steeringPin = 5; // Example pin for steering servo
int motorSpeedPin = 18; // Example pin for motor speed (PWM)
int motorDirPin = 19;   // Example pin for motor direction
int motorDirPin2 = 21;  // Example pin for motor direction
int LED = 16;
void setup() {
  controller.begin();
  Serial.begin(115200);
  pinMode(motorSpeedPin, OUTPUT);
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorDirPin2, OUTPUT);
  Steering.attach(steeringPin); // Example pin for steering servo
}

void loop() {
  delay(1000);
  if (controller.isConnected()) {
    XboxControlsState s;
    controller.read(&s);

    Serial.printf("lx: %.2f, ly: %.2f, rx: %.2f, ry: %.2f\n",
      s.leftStickX, s.leftStickY, s.rightStickX, s.rightStickY);
  } else {
    Serial.println("controller not connected");
  }
}
// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}