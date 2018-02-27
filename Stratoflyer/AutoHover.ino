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

void handleAutoHoverSwitch() {
  // Ignore auto hover switch, if the capsule is disconnected.
  if (capsuleDisconnected) {
    return;
  }
  
  // Handle Auto Hover Toggle button.
  bool autoHoverToggle = checkAutoHoverToggle();

  if (autoHoverToggle && !autoHover) {
    autoHover = true;
    updateValveState();
    Serial.print("Auto Hover enabled\n");
  } else if (!autoHoverToggle && autoHover) {
    autoHover = false;
    updateValveState();
    Serial.print("Auto Hover disabled\n");
  }
}

void updateValveState() {
  if (autoHover) {
    digitalWrite(valvePin, HIGH);
  } else {
    digitalWrite(valvePin, LOW);
  }

  Serial.println(autoHover);
}

