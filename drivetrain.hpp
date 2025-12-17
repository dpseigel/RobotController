#pragma once

#include <Arduino.h>

class Drivetrain {

  private:

  //each wheel pin
  const int Rwf;
  const int Rwb;
  const int Lwf;
  const int Lwb;

  //analog pin power max
  const int pwr = 255;

  //reference to controller
  Controller& controller;

  public:

  Drivetrain(Controller& controller, int Rwf, int Rwb, int Lwf, int Lwb) : controller(controller), Rwf(Rwf), Rwb(Rwb), Lwf(Lwf), Lwb(Lwb) {
    //setting all the pins to output
    pinMode(Rwf, OUTPUT);
    pinMode(Rwb, OUTPUT);
    pinMode(Lwf, OUTPUT);
    pinMode(Lwb, OUTPUT);
  }


  void drive() {
    //changing the controller to 0 to 1 not 0 to 100
    float y = float(controller.joyLeftY)/100.0;
    float x = float(controller.joyLeftX)/100.0;

    //stopping all the motors at the start of the frame
    analogWrite(Lwb, 0);
    analogWrite(Rwb, 0);
    analogWrite(Lwf, 0);
    analogWrite(Rwf, 0);

    //driving code
    //turns
    if (x > 0.4) {
      analogWrite(Lwb, pwr * abs(x));
      analogWrite(Rwf, pwr * abs(x));
    } else if (x < -0.4) {
      analogWrite(Lwf, pwr * abs(x));
      analogWrite(Rwb, pwr * abs(x));
    } else if (y > 0) { // forward and backward
      analogWrite(Lwf, pwr * abs(y));
      analogWrite(Rwf, pwr * abs(y));
    } else if (y < 0) {
      analogWrite(Lwb, pwr * abs(y));
      analogWrite(Rwb, pwr * abs(y));
    }
  }
};