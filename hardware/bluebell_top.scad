/*--------------------------------------------------------------------------*
* 24-May-2014 ShaneG
*
* The top part of the case for the Bluebell ambient device. This is best
* printed in white.
*--------------------------------------------------------------------------*/
include <common.scad>;

difference() {
  // Main section for the top
  difference() {
    // Build the main cube
    cube(size = [ CASE_TOP_WIDTH, CASE_TOP_HEIGHT, CASE_TOP_DEPTH ], center = false);
    // Make it hollow
    translate(v = [ SHELL_SIZE * 2, SHELL_SIZE * 2, SHELL_SIZE ]) {
      cube(size = [ PCB_WIDTH - (SHELL_SIZE * 2), PCB_HEIGHT - (SHELL_SIZE * 2), CASE_TOP_DEPTH ], center = false);
      }
    }
  // Cutaway for the overlap
  translate(v = [ -OVERLAP_ADJUST, -OVERLAP_ADJUST, CASE_TOP_DEPTH - CASE_OVERLAP_DEPTH ]) {
    difference() {
      // Build the main cube
      cube(size = [ CASE_TOP_WIDTH + (2 * OVERLAP_ADJUST), CASE_TOP_HEIGHT + (2 * OVERLAP_ADJUST), 1.5 * CASE_OVERLAP_DEPTH ], center = false);
      // Make it hollow
      translate(v = [ SHELL_SIZE + CASE_OVERLAP_WIDTH, SHELL_SIZE + CASE_OVERLAP_HEIGHT, -CASE_OVERLAP_DEPTH ]) {
        cube(size = [ CASE_TOP_WIDTH - ((SHELL_SIZE + CASE_OVERLAP_WIDTH) * 2), CASE_TOP_HEIGHT - ((SHELL_SIZE + CASE_OVERLAP_HEIGHT) * 2), 3 * CASE_OVERLAP_DEPTH ], center = false);
        }
      }
    }
  }
