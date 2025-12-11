#include <SoftwareSerial.h>

SoftwareSerial BTserial(11, 10);

static constexpr size_t kMessageSize_B = 7;
uint8_t rxBuffer[kMessageSize_B] = {};
size_t numRxBytes = 0;

boolean btnMidLeft;
boolean btnMidRight;
boolean joyLeftBtn;

boolean btnRightUp;
boolean btnRightRight;
boolean btnRightDown;
boolean btnRightLeft;


int8_t joyLeftX;
int8_t joyLeftY;

static constexpr uint8_t kJoystickMinimum = 0;
static constexpr uint8_t kJoystickMiddle = 127;
static constexpr uint8_t kJoystickMaximum = 254;

  // Increase this slightly if the robot is driving (or its motors are whining) without moving the
  // joystick
  static constexpr uint8_t kJoystickDeadzone = 22;


void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);  
}


int8_t parseJoystickValue(const uint8_t aAxis) {
    if (aAxis <= kJoystickMiddle - kJoystickDeadzone) {
      return map(aAxis, kJoystickMinimum, kJoystickMiddle + kJoystickDeadzone, -100, 0);
    } else if (aAxis >= kJoystickMiddle + kJoystickDeadzone) {
      return map(aAxis, kJoystickMiddle + kJoystickDeadzone, kJoystickMaximum, 0, 100);
    } else {
      return 0;
    }
  }

void loop() {
  if (numRxBytes != kMessageSize_B) {
      while (BTserial.available() > 0) {
        uint8_t rxByte = BTserial.read();

        if (numRxBytes == 0 && rxByte != 0xFF) {
          // Ignore input until we see the start of a message
        } else if (numRxBytes < kMessageSize_B) {
          // Append the byte to the message buffer
          rxBuffer[numRxBytes++] = rxByte;
        } else {
          // We've somehow received too many bytes between start bytes.
          // Clear the buffer and try again.
          memset(rxBuffer, 0, sizeof(rxBuffer));
          numRxBytes = 0;
        }
      }
      delay(8);
    } else {
      // Print received message to the console
      char s[48] = {0};
      snprintf(s, 47, "RX: [0x%02x][0x%02x][0x%02x][0x%02x][0x%02x][0x%02x][0x%02x]\n", rxBuffer[0],
               rxBuffer[1], rxBuffer[2], rxBuffer[3], rxBuffer[4], rxBuffer[5], rxBuffer[6]);
      // Serial.println(s);


      btnMidLeft = (rxBuffer[1] & 0x17);
      btnMidRight = (rxBuffer[1] & 0x10);
      joyLeftBtn = (rxBuffer[1] & 0x20);

      btnRightUp = (rxBuffer[2] & 0x10);
      btnRightRight = (rxBuffer[2] & 0x20);
      btnRightDown = (rxBuffer[2] & 0x40);
      btnRightLeft = (rxBuffer[2] & 0x80);

      joyLeftX = parseJoystickValue(rxBuffer[3]);
      joyLeftY = parseJoystickValue(rxBuffer[4]);

      Serial.println(String(-joyLeftX) + ", " + String(joyLeftY));
    

      // Clear the message buffer to make room for the next message
      memset(rxBuffer, 0, sizeof(rxBuffer));
      numRxBytes = 0;
    }
}
