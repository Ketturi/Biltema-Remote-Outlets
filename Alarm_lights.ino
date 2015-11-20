/*Alarm clock light control
 * 
 */

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

const int alarmsig = 6;     // Pin goes high when alarm is sound/snooze is on
const int rcPin = 3;        // Pin where transmitter is connected
const int dip1Pin = 0;      // Selects if outlets are turned off when alarm is muted
const int dip2Pin = 1;      // Selects if delay is applied when turning of lights
const int32_t ondelay = 600000;  // 10 min (600000ms) delay before lights are turned off
int alarmState = 0;         // current state of the Alarm
int alarmLastState = 0;     // previous state of the Alarm

void setup() {
  pinMode(alarmsig, INPUT);
  pinMode(dip1Pin, INPUT_PULLUP);
  pinMode(dip2Pin, INPUT_PULLUP);

  mySwitch.enableTransmit(3);
  mySwitch.setRepeatTransmit(20);
}

void loop() {
  alarmState = digitalRead(alarmsig);
  if (alarmState != alarmLastState) {
    if (alarmState == HIGH) {
       switchOutlet(0,1);
       switchOutlet(1,1);
    }
    else if (digitalRead(dip1Pin) == HIGH) {
       if (digitalRead(dip2Pin) == HIGH){
          delay(ondelay);
       }
       switchOutlet(0,0);
       switchOutlet(1,0);

    }
    delay(50);    // Delay a little bit to avoid bouncing   
  }
  alarmLastState = alarmState;
}

void switchOutlet(int dev, int state) { //switchOutlet(device address [0-3],on/off)
  int32_t code[] = {83028, 86100, 70740, 21588}; // For BILTEMA remote outlets
  mySwitch.send(code[dev] + state,24);
}


