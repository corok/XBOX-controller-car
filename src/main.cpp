#include <Arduino.h>
#include <BLEGamepadClient.h>
// put function declarations here:
int myFunction(int, int);
XboxController controller;
void setup() {
  controller.begin();
  Serial.begin(115200);
}

void loop() {
  if(controller.isConnected()) {
    XboxControlsState state;
    controller.read(&state);
    Serial.print("Left Stick X: ");
    Serial.print(state.leftStickX);
    Serial.print(" Left Stick Y: ");
    Serial.print(state.leftStickY);
    Serial.print(" Right Stick X: ");
    Serial.print(state.rightStickX);
    Serial.print(" Right Stick Y: ");
    Serial.print(state.rightStickY);
    Serial.print(" Left Trigger: ");
    Serial.print(state.leftTrigger);
    Serial.print(" Right Trigger: ");
    Serial.println(state.rightTrigger);
  } else {
    Serial.println("Controller not connected");
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}