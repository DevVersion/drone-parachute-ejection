#include <Servo.h> 

int paraSensorPin = 12;
int paraServoPin = 11;

// Reference to the Servo that ejects the parachute.
Servo paraEjectServo;

void setup() {
  // Initialize the PWN input parachute sensor.
  pinMode(paraSensorPin, INPUT);

  // Attach the servo to the parachute servo pin.
  paraEjectServo.attach(paraServoPin);

  // Enable logging at the specified serial port.
  Serial.begin(9600);    
}

void loop() {
  if (checkParachuteEject()) {
    Serial.print("Eject!");

    // For testing, set the servo to 180deg.
    paraEjectServo.write(180);
  } else {
    Serial.print("NO Eject!");

    // Default to 90deg.
    paraEjectServo.write(90);
  }
  Serial.print("\n");
}

boolean checkParachuteEject() {
  return pulseIn(paraSensorPin, HIGH) <= 1700;
}

