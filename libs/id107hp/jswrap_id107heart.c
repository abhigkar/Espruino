#include <jswrap_id107touch.h>
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

#define HEARTRATE_ADDR 0x5A

JshI2CInfo i2cHeartRate; //Heart Rate

/*JSON{
  "type": "class",
  "class" : "Id107hp"
}
*/
////////////////////////////////////////////////////////////
//Section for Si114x
///////////////////////////////////////////////////////////

void jswrap_id107hp_heartWrParm(unsigned char reg, unsigned char data) {
  unsigned char buf[3];
  buf[0] = 0x17;
  buf[1] = data;
  buf[2] = (0xA0 | reg);
  jsi2cWrite(&i2cHeartRate, HEARTRATE_ADDR, 3, buf, true);
}

void jswrap_id107hp_heartWr(unsigned char reg, unsigned char data) {
  unsigned char buf[2];
  buf[0] = reg;
  buf[1] = data;
  jsi2cWrite(&i2cHeartRate, HEARTRATE_ADDR, 2, buf, true);
}

/*JSON{
	  "type" : "staticmethod",
	  "class" : "Id107hp",
	  "name" : "initHeartRate",
	  "generate" : "jswrap_id107hp_init_heart"
}
Init methof for Si114x Heart Rate sensor
*/
void jswrap_id107hp_init_heart() {
  
  jshI2CInitInfo(&i2cHeartRate);
  i2cHeartRate.bitrate = 0x7FFFFFFF; // make it as fast as we can go
  i2cHeartRate.pinSDA = HEARTRATE_PIN_SDA;
  i2cHeartRate.pinSCL = HEARTRATE_PIN_SCL;
  jshPinSetValue(i2cHeartRate.pinSCL, 1);
  jshPinSetState(i2cHeartRate.pinSCL, JSHPINSTATE_GPIO_OUT_OPENDRAIN_PULLUP);
  jshPinSetValue(i2cHeartRate.pinSDA, 1);
  jshPinSetState(i2cHeartRate.pinSDA, JSHPINSTATE_GPIO_OUT_OPENDRAIN_PULLUP);
  jshDelayMicroseconds(10000);

  jswrap_id107hp_heartWr(0x07, 0x17);

  
  jswrap_id107hp_heartWr(0x03, 0x03);       // turn on interrupts
  jswrap_id107hp_heartWr(0x04, 0x0F);    // turn on interrupt on PS12 JJ
  jswrap_id107hp_heartWr(0x05, 0x0F);     // interrupt on ps2 AND PS1 measurement
  jswrap_id107hp_heartWr(0x08, 0x84);     // see datasheet -- every 10ms
  jswrap_id107hp_heartWr(0x09, 0x08);      // see datasheet ---- one measurement
  jswrap_id107hp_heartWr(0x0A, 0x08);       // see datasheet --every time the device wakes up
  jswrap_id107hp_heartWr(0x10, 0x02);
  jswrap_id107hp_heartWr(0x0F, 0x00);      // this powers off the green leds of the ID107HR
  //Serial.println(pulse.getReg(PulsePlug::PS_LED21), BIN);
  //Serial.print("CHLIST = ");
  //Serial.println(pulse.readParam(0x01), BIN);
  jswrap_id107hp_heartWrParm(0x01, 0x77);         // all measurements on
  jswrap_id107hp_heartWrParm(0x0B, 0x00);
  jswrap_id107hp_heartWrParm(0x02, 0x21);  // 21 = LED 2 & LED 1 (red) resp.
  jswrap_id107hp_heartWrParm(0x07, 0x03);      // PS1 photodiode select
  jswrap_id107hp_heartWrParm(0x08, 0x03);      // PS2 photodiode select
  jswrap_id107hp_heartWrParm(0x09, 0x03);      // PS3 photodiode select
  jswrap_id107hp_heartWrParm(0x0A, 0b01110000);    // B01110000 is default
  jswrap_id107hp_heartWr(0x18,0b00001111);     // starts an autonomous read loop
}

/*JSON{
	  "type" : "staticmethod",
	  "class" : "Id107hp",
	  "name" : "pulseALSRead",
	  "generate" : "jswrap_id107hp_pulseALSRead"
}
read ALS data
*/
void jswrap_id107hp_pulseALSRead(){
  unsigned char buf[6];
  buf[0] = 0x22;
  jsi2cWrite(&i2cHeartRate, HEARTRATE_ADDR, 1, buf, true);
  jsi2cRead(&i2cHeartRate, HEARTRATE_ADDR, 4, buf, true);

  buf[4] = buf[0] +  (buf[1] << 8);
  buf[5] = buf[2] +  (buf[3] << 8);
  jsiConsolePrintf("test_vis_1 %d\n",buf[4]);
  jsiConsolePrintf("test_ir_1 %d\n",buf[5]);
}