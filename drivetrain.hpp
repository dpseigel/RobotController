#pragma once

#include <Arduino.h>

class Drivetrain {

  private:

  int Rwf;
  int Rwb;
  int Lwf;
  int Lwb;

  const int pwr = 255;

  Controller& controller;

  public:

  Drivetrain(Controller& controller, int Rwf, int Rwb, int Lwf, int Lwb) : controller(controller), Rwf(Rwf), Rwb(Rwb), Lwf(Lwf), Lwb(Lwb) {
    pinMode(Rwf, OUTPUT);
    pinMode(Rwb, OUTPUT);
    pinMode(Lwf, OUTPUT);
    pinMode(Lwb, OUTPUT);
  }


  void drive() {

    float y = float(controller.joyLeftY)/100.0;
    float x = float(controller.joyLeftX)/100.0;

    analogWrite(Lwb, 0);
    analogWrite(Rwb, 0);
    analogWrite(Lwf, 0);
    analogWrite(Rwf, 0);

    if (x > 0.4) {
      analogWrite(Lwb, pwr * abs(x));
      analogWrite(Rwf, pwr * abs(x));
    } else if (x < -0.4) {
      analogWrite(Lwf, pwr * abs(x));
      analogWrite(Rwb, pwr * abs(x));
      
    } else if (y > 0) {
      analogWrite(Lwf, pwr * abs(y));
      analogWrite(Rwf, pwr * abs(y));
    } else if (y < 0) {
      analogWrite(Lwb, pwr * abs(y));
      analogWrite(Rwb, pwr * abs(y));
    }
  }
};