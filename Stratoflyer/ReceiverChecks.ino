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

bool isCapsuleSwitchToggled() {
  int pulse = pulseIn(capsuleSensorPin, HIGH);

  if (!initialDisconnectCapsulePulse || !pulse) {
    return false;
  }
  
  int pulseDiff = pulse - initialDisconnectCapsulePulse;

  return pulseDiff > 150 || pulseDiff < -150;
}

bool checkAutoHoverToggle() {
  return pulseIn(autoHoverSensorPin, HIGH) > 1700;
}

bool checkParachuteEject() {
  return pulseIn(parachuteSensorPin, HIGH) < 1000;
}

bool isArmingSwitchToggled() {
  return pulseIn(armingSensorPin, HIGH) > 1500;
}

