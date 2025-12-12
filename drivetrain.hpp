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


  void drive_with_controls() {
    float y = float(controller.joyLeftY)/100.0;
    float x = -(float(controller.joyLeftX)/100.0);
    float left = y + x;
    float right = y - x;
    Serial.println(String(x) + ", " + String(y));

    if (left > 0.0) {
      analogWrite(Lwf, left * pwr);
    } else if (left < 0.0) {
      analogWrite(Lwb, abs(left) * pwr);
    } else {     
      analogWrite(Lwf, 0);
      analogWrite(Lwb, 0);
    }

    if (right > 0.0) {
      analogWrite(Rwf, right * pwr);
    } else if (right < 0.0) {
      analogWrite(Rwb, abs(right) * pwr);
    } else {
      analogWrite(Rwf, 0);
      analogWrite(Rwb, 0);
    }
  }
};