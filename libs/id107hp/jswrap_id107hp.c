
#include <jswrap_id107hp.h>
#include "jsinteractive.h"
#include "jsdevices.h"
#include "jsnative.h"
#include "jshardware.h"
#include "jsdevices.h"
#include "jspin.h"
#include "jstimer.h"
#include "jswrap_promise.h"
#include "jswrap_date.h"
#include "jswrap_math.h"
#include "jswrap_array.h"
#include "jswrap_arraybuffer.h"
#ifndef EMSCRIPTEN
#include "jswrap_bluetooth.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_soc.h"
#include "nrf_saadc.h"
#include "nrf5x_utils.h"
#include "jsi2c.h" // accelerometer/etc
#endif


/*JSON{
  "type": "class",
  "class" : "Id107hp"
}
*/

/*JSON{
  "type" : "init",
  "generate" : "jswrap_id107hp_init"
}*/
void jswrap_id107hp_init() {
  /// set poll handler
  // This timer kicks the watchdog, and does some other stuff as well
  
}

/*JSON{
  "type" : "kill",
  "generate" : "jswrap_id107hp_kill"
}*/
void jswrap_id107hp_kill() {
  
}


/*JSON{
  "type" : "idle",
  "generate" : "jswrap_id107hp_idle"
}*/

bool jswrap_id107hp_idle() {
 NRF_WDT->RR[0] = 0x6E524635;
 //jshKickWatchDog();
 
 return false;
}

/*JSON{
    "type" : "staticmethod",
    "class" : "Id107hp",
    "name" : "off",
    "generate" : "jswrap_id107hp_off"
}
Turn Id107hp.js off. It can only be woken by pressing BTN1.
*/
void jswrap_id107hp_off() {
  
}
 