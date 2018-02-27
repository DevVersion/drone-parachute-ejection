
/* Copyright 2018 Stratoflyer Industries.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <Servo.h>

// Model B450. Arduino Mega

/** Pins for the auto hover mode. (GEAR Toggle) */
int autoHoverSensorPin = 10;

/** Pins for the LEDs */
int blueLightPin = 44;
int greenLightPin = 46;
int redLightPin = 48;

/** Pins for capsule ejection. (FLAPS Toggle) */
int capsuleSensorPin = 8;
int capsuleServoPin = 9;

/** Pins for enabling the parachute ejection (Throttle Cut Button) */
int parachuteSensorPin = 12;
int parachuteServo2Pin = 5;
int parachuteServo1Pin = 6;

/** Pins for the arming sensor pin. */
int armingSensorPin = 13;

/** Valve Pin */
int valvePin = 7;

/** Servos that either eject the capsule or the parachute. */
Servo paraEjectServo1, paraEjectServo2, capsuleEjectServo;

bool autoHover = false;
bool parachuteEjected = false;
bool capsuleDisconnected = false;
bool capsuleServoTestMode = false;
bool armed = false;

/** Store initial capsule pulse length. This is necessary to allow switching the toggle into any direction. */
int initialDisconnectCapsulePulse;

void setup() {
  // Initialize the PWN input sensors.
  pinMode(parachuteSensorPin, INPUT);
  pinMode(capsuleSensorPin, INPUT);
  pinMode(autoHoverSensorPin, INPUT);
  pinMode(armingSensorPin, INPUT);

  // Init Valve pin.
  pinMode(valvePin, OUTPUT);

  // Setup RGB LED light pins.
  pinMode(blueLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
  pinMode(redLightPin, OUTPUT);

  // Attach the servo to the parachute servo pin.
  paraEjectServo1.attach(parachuteServo1Pin);
  paraEjectServo2.attach(parachuteServo2Pin);
  
  capsuleEjectServo.attach(capsuleServoPin);

  // Enable logging at the specified serial port.
  Serial.begin(9600);

  // Logging.
  Serial.println("Initialized Stratoflyer v0.1");

  initializeCapsuleDisconnect();
  initializeParachuteEjectSwitch();
}

void loop() {
  // Determine initial capsule value if RC controller is enabled afterwards.
  determineInitialCapsuleValue();
  
  // Handle RC buttons.
  handleRemoteController();

  // Handle colored lights.
  handleColoredLights();
}

