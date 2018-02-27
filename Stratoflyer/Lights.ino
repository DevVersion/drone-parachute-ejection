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

bool _blink = false;

void handleColoredLights() {

  if (armed && capsuleDisconnected && parachuteEjected) {
    _blink = !_blink;

    if (_blink) {
       turnOnLights(true, false, false);
    } else {
       turnOnLights(false, false, true);
    }

    // Since we just display a blinking LED, and the state of the flyer is kind of locked
    // right now, we can have a delay of around 150ms for a proper blinking.
    delay(150);

    return;
  }
  
  if (!armed) {
    turnOnLights(true, false, false);
  } else {
    turnOnLights(false, true, false);
  }

  if (armed && autoHover) {
    turnOnLights(false, false, true);
  }
}

void turnOffAllLights() {
  digitalWrite(redLightPin, LOW);
  digitalWrite(greenLightPin, LOW);
  digitalWrite(blueLightPin, LOW);
}

void turnOnLights(bool red, bool green, bool blue) {
  digitalWrite(redLightPin, red ? HIGH : LOW);
  digitalWrite(greenLightPin, green ? HIGH : LOW);
  digitalWrite(blueLightPin, blue ? HIGH : LOW);
}

