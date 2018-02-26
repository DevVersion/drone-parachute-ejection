#include <Servo.h> 

// Model B450

/** Pins for parachute ejection. */
int paraSensorPin = 12;
int paraServoPin = 11;

/** Pins for capsule ejection. */
int capsuleSensorPin = 8;
int capsuleServoPin = 9;

/** Servos that either eject the capsule or the parachute. */
Servo paraEjectServo, capsuleEjectServo;

void setup() {
  // Initialize the PWN input sensors.
  pinMode(paraSensorPin, INPUT);
  pinMode(capsuleSensorPin, INPUT);

  // Attach the servo to the parachute servo pin.
  paraEjectServo.attach(paraServoPin);
  capsuleEjectServo.attach(capsuleServoPin);

  // Enable logging at the specified serial port.
  Serial.begin(9600);    
}

void loop() {
  
  if (checkParachuteEject()) {
    Serial.print("Eject Parachute!\n");
    paraEjectServo.write(90);
  } else {
    paraEjectServo.write(0);
  }

  if (checkCapsuleEject()) {
    Serial.print("Eject Capsule\n");

    // Eject Capsule Servo
  } else {
    
  }
}

boolean checkCapsuleEject() {
  return pulseIn(capsuleSensorPin, HIGH) > 1100;
}

boolean checkParachuteEject() {  
  return pulseIn(paraSensorPin, HIGH) > 1700;
}

