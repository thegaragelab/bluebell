#!/usr/bin/env python
#----------------------------------------------------------------------------
# 29-May-2014 ShaneG
#
# Simple wrapper to control the Bluebell device over Bluetooth.
#----------------------------------------------------------------------------
try:
  from serial import Serial
except:
  print "This module requires the PySerial model."
  exit(1)

#----------------------------------------------------------------------------
# Helper functions
#----------------------------------------------------------------------------

def trimValue(val):
  """ Make sure a value is an integer in the range 0 to 255
  """
  try:
    val = int(val)
  except:
    val = 0
  # Trim to range
  if val < 0:
    val = 0
  if val > 255:
    val = 255
  return val

#----------------------------------------------------------------------------
# Classes
#----------------------------------------------------------------------------

class Bluebell:
  """ This class wraps the Bluetooth serial connection to a Bluebell device.
  """

  def __init__(self, port):
    """ Initialise the device with the port to connect on.
    """
    self._port = port

  def update(self, red, green, blue, time = 10):
    """ Change the device to the requested color for the period specified.

      @param red the red component of the color (0 to 255)
      @param green the green component of the color (0 to 255)
      @param blue the blue component of the color (0 to 255)
      @param time the time (in seconds) to hold the color.

      @return true if the command was sucessfuly sent to the device.
    """
    # Set up the serial port
    port = None
#    try:
    port = Serial(self._port, baudrate = 57600, timeout = 0.2)
#    except:
#      return False
    # Write the data
    data = (
      ord('!'),
      trimValue(red),
      trimValue(green),
      trimValue(blue),
      trimValue(time),
      ord('\n')
      )
    print data
    port.write(data)
    print port.read()
    # All done
    port.close()
    return True

