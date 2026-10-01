#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"
#include "game_data.h"


#pragma intrinsic(memcpy, memset)


extern unsigned char g_slot_table[0x300 * 0x21c];


/* Initializes the object production (Hersteller) system.
 * Loads product definitions, recipes, and production chain
 * data from game files. */

// DATA: SERVER 0x1002dde0

// DATA: SERVER 0x100a8c34

// DATA: SERVER 0x1014d8c0
// DATA: SERVER 0x101de450
