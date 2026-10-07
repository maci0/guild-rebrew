#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memcpy, memset)

int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);

// FUNCTION: GOLDTL 0x40f3d0

int __cdecl fcn_0064d470(int, int);
int __cdecl fcn_00413120(int);

char __cdecl fcn_0040f3d0(int a, int b)
{
	if (fcn_0064d470(a, b) != 0) {
		fcn_00413120(a);
	}
	return 1;
}
