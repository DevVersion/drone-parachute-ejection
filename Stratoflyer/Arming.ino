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

unsigned long _startArmingMs = 0;

void handleArmingSwitch() {
  bool canArm = isArmingSwitchToggled();

  if (armed || !canArm) {
    _startArmingMs = 0;
    return;
  }
  
  unsigned long curMillis = millis();

  if (!_startArmingMs) {
    _startArmingMs = curMillis;
  } else if (curMillis > _startArmingMs + 2000) {
    if (capsuleServoTestMode) {
      Serial.println("Arming failed. Capsule disconnection switch is enabled");

      // Small blink to indicate that something didn't work.
      turnOffAllLights();
      turnOnLights(true, false, true);
      delay(150);
      
    } else {
      armed = true;
      Serial.println("Successfully armed now!");
    }

    _startArmingMs = 0;
  }
}

