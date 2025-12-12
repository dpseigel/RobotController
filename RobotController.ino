#include "controller.hpp"
#include "drivetrain.hpp"


Controller controller(10, 9);
Drivetrain drivetrain(controller, 3, 5, 6, 11);

void setup() {
  Serial.begin(9600);
  Serial.println("wassup");
  controller.controller_setup();
}

void loop() {
  controller.controller_loop();
  drivetrain.drive_with_controls();
}
