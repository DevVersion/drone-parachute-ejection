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

int _cdClosedVal = 5;
int _cdOpenedVal = 45;

void determineInitialCapsuleValue() {
  if (!initialDisconnectCapsulePulse) {
    initialDisconnectCapsulePulse = pulseIn(capsuleSensorPin, HIGH);

    if (initialDisconnectCapsulePulse > 0) {
      Serial.println("Success: Connecting established to RC controller");
    }
  }
}

void initializeCapsuleDisconnect() {
  // Initial capsule servo degree
  capsuleEjectServo.write(_cdClosedVal);

  determineInitialCapsuleValue();

  // Security check. Just checking the disconnect capsule switch.
  if (!initialDisconnectCapsulePulse) {
    Serial.println("Warning: Looks like the RC controller is not turned on!");
  }
}


void handleCapsuleDisconnectSwitch() {
  // Handle the capsule disconnect. There are different behaviors for this switch:
  //   (1) If armed, and got toggled --> Disconnect
  //   (2) If not armed, and got toggled --> Open Servo --> Needs to be toggled back to become armed.
  
  bool switchToggled = isCapsuleSwitchToggled();

  // If armed, and the switch as been turned on, and the capsule hasn't been connected yet.
  // This is being called if the switch has been toggled --> capsule will be disconnected.
  if (armed && switchToggled && !capsuleDisconnected) {
    capsuleDisconnected = true;
    capsuleEjectServo.write(_cdOpenedVal);
    Serial.print("Disconnected Capsule!\n");
  }

  // If not armed, and the switch is turned on, and test mode was previously disabled.
  // This allows the engineers to properly connect the ballon.
  if (!armed && switchToggled && !capsuleServoTestMode) {
    capsuleServoTestMode = true;
    capsuleEjectServo.write(_cdOpenedVal);
  }

  // If not armed, and the switch is turned back from the test mode.
  if (!armed && !switchToggled && capsuleServoTestMode) {
    capsuleServoTestMode = false;
    capsuleEjectServo.write(_cdClosedVal);
  }
}
