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

    paraEjectServo.write(90);
  } else {
    Serial.print("NO Eject!");

    paraEjectServo.write(0);
  }
  Serial.print("\n");
}

boolean checkParachuteEject() {
  int pulse = pulseIn(paraSensorPin, HIGH);
  
  return pulse <= 1700 && pulse != 0;
}

