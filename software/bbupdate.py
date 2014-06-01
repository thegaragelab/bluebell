#!/usr/bin/env python
#----------------------------------------------------------------------------
# 29-May-2014 ShaneG
#
# Send an update to the Bluebell device.
#----------------------------------------------------------------------------
import sys
from os.path import basename
from bluebell import Bluebell

#--- Banner and usage information
BANNER = """
bluebell.py - Bluebell Ambient Device Control Utility
Copyright (c) 2014, The Garage Lab. All Rights Reserved.
"""

USAGE = """
Usage:

  %s port red green blue [time]

Parameters:
  port    Specify the name of the serial port to use for communication.
  red     The red component of the color - 0 to 255
  green   The green component of the color - 0 to 255
  blue    The blue component of the color - 0 to 255
  time    The amount of time (in seconds) to hold the color. If not specified
          the default is 0 (hold forever or until the next change).
"""

#----------------------------------------------------------------------------
# Helper functions
#----------------------------------------------------------------------------

def showUsage():
  print USAGE.strip() % basename(sys.argv[0])
  exit(1)

#----------------------------------------------------------------------------
# Main program
#----------------------------------------------------------------------------

if __name__ == "__main__":
  print BANNER.strip() + "\n"
  if not len(sys.argv) in (5, 6):
    showUsage()
  # Collect our data
  device = Bluebell(sys.argv[1])
  if len(sys.argv) == 6:
    device.update(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
  else:
    device.update(sys.argv[2], sys.argv[3], sys.argv[4])

