#include <Servo.h>

#define AH_NEUTRAL 0
#define AH_ENABLED 1
#define AH_DISABLED 2

// Model B450

/** Pins for parachute ejection. */
int paraSensorPin = 10;
int paraServoPin = 11;

/** Pins for capsule ejection. */
int capsuleSensorPin = 8;
int capsuleServoPin = 9;

/** Pins for enabling the auto-hover */
int autoHoverSensorPin = 12;

/** Servos that either eject the capsule or the parachute. */
Servo paraEjectServo, capsuleEjectServo;

bool autoHover = false;

void setup() {
  // Initialize the PWN input sensors.
  pinMode(paraSensorPin, INPUT);
  pinMode(capsuleSensorPin, INPUT);
  pinMode(autoHoverSensorPin, INPUT);

  // Attach the servo to the parachute servo pin.
  paraEjectServo.attach(paraServoPin);
  capsuleEjectServo.attach(capsuleServoPin);

  // Enable logging at the specified serial port.
  Serial.begin(9600);
}

void loop() {
  
  if (checkParachuteEject()) {
    Serial.print("Eject Parachute\n");
    paraEjectServo.write(90);
  } else {
    paraEjectServo.write(0);
  }

  if (checkCapsuleDisconnect()) {
    Serial.print("Disconnect Capsule\n");
  }

  determineAutoHoverState();
}

/**
 * Logic & behavior
 */

void determineAutoHoverState() {
  int autoHoverState = getAutoHoverState();

  if (autoHoverState == AH_ENABLED  && !autoHover) {
    autoHover = true;
    Serial.print("Auto Hover enabled!\n");
  } else if (autoHoverState == AH_DISABLED && autoHover) {
    autoHover = false;
    Serial.print("Auto Hover disabled!\n");
  }
}

/**
 * Pin check functions
 */

bool checkCapsuleDisconnect() {
  return pulseIn(capsuleSensorPin, HIGH) > 1100;
}

bool checkParachuteEject() {
  return pulseIn(paraSensorPin, HIGH) > 1700;
}

int getAutoHoverState() {
  int pulse = pulseIn(autoHoverSensorPin, HIGH) - 1500;

  if (pulse > 50) {
    return AH_ENABLED;
  } else if (pulse < -50) {
    return AH_DISABLED;
  }

  return AH_NEUTRAL;
}

