//---------------------------------------------------------------------------
// Common definitions for the Night Light case
//---------------------------------------------------------------------------
// 27-Mar-2014 ShaneG
//
// This file contains the common definitions (dimensions and utility modules)
// used to generate the two halves of the Night Light case.
//---------------------------------------------------------------------------

// Printer resolution (used for spheres and circles)
RESOLUTION = 0.1;

// Shell information
SHELL_SIZE   = 2;

// Size for the board + battery pack
PCB_WIDTH  = 58;
PCB_HEIGHT = 26;
PCB_DEPTH  = 92;

// Case dimensions (bottom)
CASE_WIDTH   = PCB_WIDTH + (2 * SHELL_SIZE);
CASE_HEIGHT  = PCB_HEIGHT + (2 * SHELL_SIZE);
CASE_DEPTH   = PCB_DEPTH + (2 * SHELL_SIZE);

// Overlap sizes
OVERLAP_ADJUST      = 0.25;

CASE_OVERLAP_DEPTH  = SHELL_SIZE * 2;
CASE_OVERLAP_WIDTH  = 2 * OVERLAP_ADJUST;
CASE_OVERLAP_HEIGHT = 2 * OVERLAP_ADJUST;

// Case dimensions (top)
CASE_TOP_WIDTH  = PCB_WIDTH + (2 * SHELL_SIZE);
CASE_TOP_HEIGHT = PCB_HEIGHT + (2 * SHELL_SIZE);
CASE_TOP_DEPTH  = SHELL_SIZE + CASE_OVERLAP_DEPTH;

