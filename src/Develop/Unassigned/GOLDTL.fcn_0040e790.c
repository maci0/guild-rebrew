


#include <stdio.h>

extern char* evt_CurrentScript;
int __cdecl fcn_00445600(int a, int b, int c, char* name);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl ecmd_GetSubObjectHandle(int* parent, char** name)
{
	char buf[0x200];
	int handle;

	handle = fcn_00445600(*parent, 0x140, 0, *name);
	if (handle == 0) {
		sprintf(buf, "unknown object %s", *name);
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), buf);
	}
	return handle;
}
