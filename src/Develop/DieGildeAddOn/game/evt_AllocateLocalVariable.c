extern char g_67921c[];
extern char g_67920c[];
#include <string.h>

void __cdecl evt_LogScriptError(char* obj, int level, char* msg);
char* __cdecl evt_RequestScriptExit(char* obj);

/* ADDRESS: GOLDTL 0x00425ec0 */
/* ADDRESS: GOLDDE 0x00420990 */
char* __cdecl evt_AllocateLocalVariable(char* obj, int mode, int size, char* name)
{
	int* slot;
	char* rec;
	int i;
	int sz;
	int hdr;

	i = 0;
	sz = 0;
	rec = 0;
	slot = (int*) (*(char**) (obj + 0xc28) + 0x10);
	do {
		if (*slot == 0)
			goto found;
		i++; slot++;
	} while (i < 8);
	evt_LogScriptError(obj, *(int*) (obj + 0x118) - 1, (char*) &g_67921c);
	goto done;
found:
	if (mode == 1) {
		sz = 4;
	}
	else if (mode == 2) {
		sz = 1;
	}
	else if (mode == 7) {
		sz = 4;
	}
	else if (mode == 6) {
		sz = 0x60;
	}
	else {
		__asm { int 3 }
	}
	rec = *(char**) (obj + 0xc38);
	*(int*) (rec + 0x24) = size;
	hdr = *(int*) rec;
	*(int*) (rec + 0x28) = 1;
	*(int*) rec = (hdr ^ mode) & 0xf ^ hdr;
	*(char**) (rec + 0x2c) = rec + 0x30;
	strcpy(rec + 4, name);
	sz = sz * size + 0x30;
	*(int*) (obj + 0xc38) += sz;
	if (*(unsigned int*) (obj + 0xc38) > *(unsigned int*) (obj + 0xc34) + 0x400) {
		evt_LogScriptError(obj, *(int*) (obj + 0x118), (char*) &g_67920c);
		evt_RequestScriptExit(obj);
	}
	*(char**) (*(char**) (obj + 0xc28) + 0x10 + i * 4) = rec;
done:
	return rec;
}
