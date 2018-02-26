#include <Servo.h>
#include <stdlib.h>

// Model B450

/** Pins for the auto hover mode. (GEAR Toggle) */
int autoHoverSensorPin = 10;

/** Pins for capsule ejection. (FLAPS Toggle) */
int capsuleSensorPin = 8;
int capsuleServoPin = 9;

/** Pins for enabling the parachute ejection (Throttle Cut Button) */
int parachuteSensorPin = 12;
int parachuteServoPin = 11;

/** Servos that either eject the capsule or the parachute. */
Servo paraEjectServo, capsuleEjectServo;

bool autoHover, parachuteEjected, capsuleDisconnected = false;

/** Store initial capsule pulse length. This is necessary to allow switching the toggle into any direction. */
int initialDisconnectCapsuleVal;

void setup() {
  // Initialize the PWN input sensors.
  pinMode(parachuteSensorPin, INPUT);
  pinMode(capsuleSensorPin, INPUT);
  pinMode(autoHoverSensorPin, INPUT);

  // Attach the servo to the parachute servo pin.
  paraEjectServo.attach(parachuteServoPin);
  capsuleEjectServo.attach(capsuleServoPin);

  // Enable logging at the specified serial port.
  Serial.begin(9600);

  initialDisconnectCapsuleVal = pulseIn(capsuleSensorPin, HIGH);  
}

void loop() {

  bool ejectParachute = checkParachuteEject();
  
  if (ejectParachute && !parachuteEjected) {
    parachuteEjected = true;
    Serial.print("Ejected Parachute!\n");
    paraEjectServo.write(90);
  } else if (!parachuteEjected) {
    paraEjectServo.write(0);
  }

  // Handle capsule disconnect (One Time Toggle)
  if (checkCapsuleDisconnect() && !capsuleDisconnected) {
    capsuleDisconnected = true;
    Serial.print("Disconnected Capsule!\n");
    capsuleEjectServo.write(90);
  } else if (!capsuleDisconnected) {
    capsuleEjectServo.write(0);
  }

  // Handle Auto Hover Toggle button.
  bool autoHoverToggle = checkAutoHoverToggle();

  if (autoHoverToggle && !autoHover) {
    autoHover = true;
    Serial.print("Auto Hover enabled\n");
  } else if (!autoHoverToggle && autoHover) {
    autoHover = false;
    Serial.print("Auto Hover disabled\n");
  }
}

/**
 * Pin check functions
 */

bool checkCapsuleDisconnect() {
  int pulseDiff = abs(pulseIn(capsuleSensorPin, HIGH) - initialDisconnectCapsuleVal);

  return pulseDiff > 150;
}

bool checkAutoHoverToggle() {
  return pulseIn(autoHoverSensorPin, HIGH) > 1700;
}

bool checkParachuteEject() {
  return pulseIn(parachuteSensorPin, HIGH) < 1000;
}
