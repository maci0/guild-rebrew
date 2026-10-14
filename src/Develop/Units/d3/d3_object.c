#include "d3_object.h"

#ifdef REBREW_GOLD
int __cdecl fcn_0043d0e0(int);
int __cdecl fcn_0043c7a0(int);
#else
void __cdecl fcn_0043a0a0(char*);
void __cdecl fcn_004398d0(char*);
#endif

char __cdecl d3_DestroyObject(D3_OBJECT* object)
{
	if (object != 0) {
#ifdef REBREW_GOLD
		fcn_0043d0e0((int) object);
		fcn_0043c7a0((int) object);
#else
		fcn_0043a0a0((char*) object);
		fcn_004398d0((char*) object);
#endif
		return 1;
	}
	return 0;
}
