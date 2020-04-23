#include <jswrap_template.h>
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
  "type" : "variable",
  "name" : "BTNA",
  "generate_full" : "19",
  "return" : ["pin",""]
}
The pin connected to the 'A' button. Reads as `1` when pressed, `0` when not
*/

/*JSON{
  "type" : "event",
  "class" : "Id107hp",
  "name" : "accel",
  "params" : [["xyz","JsVar",""]]
}
Accelerometer data available with `{x,y,z,diff}` object as a parameter.

* `x` is X axis (left-right) in `g`
* `y` is Y axis (up-down) in `g`
* `z` is Z axis (in-out) in `g`
* `diff` is difference between this and the last reading in `g`

You can also retrieve the most recent reading with `Id107hp.getAccel()`.
 */


/*JSON{
    "type" : "staticmethod",
    "class" : "Id107hp",
    "name" : "setPollInterval",
    "generate" : "jswrap_id107hp_setPollInterval",
    "params" : [
      ["interval","float","Polling interval in milliseconds"]
    ]
}
Set how often the watch should poll for new acceleration/gyro data
*/



/*JSON{
  "type" : "init",
  "generate" : "jswrap_badge_init"
}*/
void jswrap_badge_init() {


}

/*JSON{
  "type" : "kill",
  "generate" : "jswrap_badge_kill"
}*/
void jswrap_badge_kill() {

}

/*JSON{
  "type" : "idle",
  "generate" : "jswrap_badge_idle"
}*/
bool jswrap_badge_idle() {
  return false;
}