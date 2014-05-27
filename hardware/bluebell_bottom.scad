/*--------------------------------------------------------------------------*
* 24-May-2014 ShaneG
*
* The bottom part of the case for the Bluebell ambient device.
*--------------------------------------------------------------------------*/
include <common.scad>;

difference() {
  // Build the main cube
  cube(size = [ CASE_WIDTH, CASE_HEIGHT, CASE_DEPTH ], center = false);
  // Make it hollow
  translate(v = [ SHELL_SIZE, SHELL_SIZE, SHELL_SIZE ]) {
    cube(size = [ PCB_WIDTH, PCB_HEIGHT, CASE_DEPTH ], center = false);
    }
  }

