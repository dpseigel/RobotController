#include "controller.hpp"
#include "drivetrain.hpp"


Controller controller(A1);
Drivetrain drivetrain(controller, 3, 5, 6, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  controller.loop();
  drivetrain.drive();
}

