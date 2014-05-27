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
#include "systicks.h"
#include "iohelp.h"
#include "utility.h"

// Forward declaration with 'noreturn' attribute
void main() __attribute__ ((noreturn));

//---------------------------------------------------------------------------
// Device state
//---------------------------------------------------------------------------

/** State information maintained by the device
 *
 * This includes the current color values for each of the LED's as well as
 * the current value of the fade out timer.
 */
typedef enum _STATE {
  STATE_RED = 0, //!< Index of red LED intensity
  STATE_GREEN,   //!< Index of green LED intensity
  STATE_BLUE,    //!< Index of blue LED intensity
  STATE_TIMER,   //!< Current count down timer

  STATE_MAX      //!< Maximum state index
  } STATE;

/** This array holds the current device state
 */
static uint8_t g_state[STATE_MAX];

//---------------------------------------------------------------------------
// LED control
//---------------------------------------------------------------------------

/** Update the current PWM values to bring them closer to the target
 */
static void ledUpdate() {
  // Update RED value
  uint8_t val = spwmValue(SPWM0);
  if(val<g_state[STATE_RED])
    val++;
  else if(val>g_state[STATE_RED])
    val--;
  spwmOut(SPWM0, val);
  // Update GREEN value
  val = spwmValue(SPWM1);
  if(val<g_state[STATE_GREEN])
    val++;
  else if(val>g_state[STATE_GREEN])
    val--;
  spwmOut(SPWM1, val);
  // Update BLUE value
  val = spwmValue(SPWM2);
  if(val<g_state[STATE_BLUE])
    val++;
  else if(val>g_state[STATE_BLUE])
    val--;
  spwmOut(SPWM2, val);
  }

//---------------------------------------------------------------------------
// Protocol implementation
//---------------------------------------------------------------------------

//! Maximum command size
#define MAX_COMMAND_SIZE 6

//! Input buffer
static uint8_t g_buffer[MAX_COMMAND_SIZE];

//! Input index
static uint8_t g_index = 0;

/** Check for a command and process it.
 */
static void cmdProcess() {
  while(uartAvail()) {
    g_buffer[g_index] = uartRecv();
    if(!((g_index==0)&&(g_buffer[0]!='!'))) {
      g_state[STATE_TIMER] = 0x0a;
      g_index++;
      if(g_buffer[g_index-1]=='\n') {
        g_state[STATE_GREEN] = 0xff;
        if(g_index==MAX_COMMAND_SIZE) {
          g_state[STATE_BLUE] = 0xff;

          // Copy in data
/*
          g_state[STATE_RED] = g_buffer[1];
          g_state[STATE_GREEN] = g_buffer[2];
          g_state[STATE_BLUE] = g_buffer[3];
          g_state[STATE_TIMER] = g_buffer[4];
*/
          }
        g_index = 0;
        }
      else if(g_index>=MAX_COMMAND_SIZE) {
        g_index = 0; // Too much data
        g_state[STATE_RED] = 0xff;
        }
      }
    }
  }

//---------------------------------------------------------------------------
// Main program
//---------------------------------------------------------------------------

/** Program entry point
 */
void main() {
  uartInit();
  spwmInit();
//  adcInit(ADC0);
  sei();
  // Initialise state
  uint16_t last;
  for(last=0; last<STATE_MAX; last++)
    g_state[last] = 255;
  g_state[STATE_TIMER] = 10;
  last = ticks();
  // Main loop
  while(true) {
    // Check for incoming commands
    cmdProcess();
    // Update the timer
    if(ticksElapsed(last)>=TICKS_PER_SECOND) {
      if(g_state[STATE_TIMER]!=0)
        g_state[STATE_TIMER]--;
      else {
        g_state[STATE_RED] = 0;
        g_state[STATE_GREEN] = 0;
        g_state[STATE_BLUE] = 0;
        }
      last = ticks();
      }
    // Update LED state
    ledUpdate();
    // Wait for a while
    wait(100);
    }
  }
