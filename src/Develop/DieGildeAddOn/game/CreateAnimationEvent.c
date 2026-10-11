
#include "../command/command_internal.h"

/* Name inferred from the task allocation and animation callback. */

void* __cdecl fcn_0040c0a0(char*);
void __cdecl fcn_00406410(char*);

char* __cdecl CreateAnimationEvent(char* owner, char* name)
{
	unsigned char* obj;
	char* d;
	char* s;

	obj = (unsigned char*) fcn_0040c0a0(owner);
	if (obj == 0) {
		return 0;
	}
	{
		s = name;
		*(char**) (obj + 0x14) = owner;
		d = (char*) obj + 0xf0;
		*(int*) (obj + 0xc) = 0;
		*(void (__cdecl**)(char*)) obj = fcn_00406410;
		obj[9] = 0x2f;
		*(int*) (obj + 0x28) = 0;
		obj[0x10] = 0;
		while ((*d++ = *s++) != 0) {
		}
	}
	return (char*) obj;
}
