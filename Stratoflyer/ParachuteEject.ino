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

void initializeParachuteEjectSwitch() {
  paraEjectServo1.write(105); // Left Servo
  paraEjectServo2.write(150); // Right Servo
}

void ejectParachutes() {
  parachuteEjected = true;
  paraEjectServo1.write(0);
  paraEjectServo2.write(0);
  Serial.println("Ejected Parachute!");
}

void handleParachuteEjectSwitch() { 
  bool ejectParachute = checkParachuteEject();

  if (ejectParachute && !parachuteEjected && capsuleDisconnected) {
    ejectParachutes();
  } else if (ejectParachute && !capsuleDisconnected) {
    turnOffAllLights();
    turnOnLights(true, false, false);
  }
}
