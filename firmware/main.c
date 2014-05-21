/*--------------------------------------------------------------------------*
* Main program
*---------------------------------------------------------------------------*
* 14-Apr-2014 ShaneG
*
* Template program for ATtiny85 C/asm projects.
*--------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "softuart.h"
#include "iohelp.h"
#include "utility.h"

// Forward declaration with 'noreturn' attribute
void main() __attribute__ ((noreturn));

//---------------------------------------------------------------------------
// LED control
//---------------------------------------------------------------------------

static uint8_t g_red = 0;
static uint8_t g_grn = 0;
static uint8_t g_blu = 0;

/** Set the target values for the LED's
 *
 * @param red target for red LED
 * @param grn target for green LED
 * @param blu target for blue LED
 */
static void ledSet(uint8_t red, uint8_t grn, uint8_t blu) {
  g_red = red;
  g_grn = grn;
  g_blu = blu;
  }

/** Update the current PWM values to bring them closer to the target
 */
static void ledUpdate() {
  // Update RED value
  uint8_t val = spwmValue(SPWM0);
  if(val<g_red)
    val++;
  else if(val>g_red)
    val--;
  spwmOut(SPWM0, val);
  // Update GREEN value
  val = spwmValue(SPWM1);
  if(val<g_grn)
    val++;
  else if(val>g_grn)
    val--;
  spwmOut(SPWM1, val);
  // Update BLUE value
  val = spwmValue(SPWM2);
  if(val<g_blu)
    val++;
  else if(val>g_blu)
    val--;
  spwmOut(SPWM2, val);
  }

static bool ledMatch() {
  return ((spwmValue(SPWM0)==g_red)&&(spwmValue(SPWM1)==g_grn)&&(spwmValue(SPWM2)==g_blu));
  }

//---------------------------------------------------------------------------
// Main program
//---------------------------------------------------------------------------

/** Program entry point
 */
void main() {
  spwmInit();
  sei();
  // Set up output values
  uint32_t output = 0x00FF0000L;
  ledSet((output>>16)&0xFF, (output>>8)&0xFF, output&0xFF);
  while(true) {
    if(ledMatch()) {
      output = output >> 8;
      if(output==0)
        output = 0x00FF0000L;
      ledSet((output>>16)&0xFF, (output>>8)&0xFF, output&0xFF);
      }
    ledUpdate();
    wait(10);
    }
  }
