#include "controller.hpp"
#include "drivetrain.hpp"
#include <Servo.h>



Servo flappything;
Controller controller(A1);
Drivetrain drivetrain(controller, 3, 5, 6, 11);

void setup() {
  Serial.begin(9600);
  controller.setup();
  flappything.attach(10);
}

void loop() {
  controller.loop();
  drivetrain.drive();
  if (controller.btnRightRight) {
    flappything.write(180);
  } else {
    flappything.write(0);
  }
}

