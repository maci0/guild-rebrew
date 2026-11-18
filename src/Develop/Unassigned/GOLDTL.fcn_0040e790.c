


#include <stdio.h>

extern char* evt_CurrentScript;
int __cdecl fcn_00445600(int a, int b, int c, char* name);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040e790(int* a, char** name)
{
	char buf[0x200];
	int r;

	r = fcn_00445600(*a, 0x140, 0, *name);
	if (r == 0) {
		sprintf(buf, "unknown object %s", *name);
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), buf);
	}
	return r;
}
