#include "Develop/DieGildeAddOn/game/ch_script.h"



#include <string.h>

// SIZE 0x4
typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Bytes4;

extern char* evt_CurrentScript;
void __cdecl d3_ChangeObjectTransparency(int a, int b, Bytes4 c);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl SetCharacterTransperancy(char** a, unsigned char* v)
{
	Bytes4 col;
	int o;

	if (*a == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	o = *(int*) (*a + 0x34);
	memset(&col, 0, sizeof(col));
	col.c &= 0xfe;
	col.a = *v;
	d3_ChangeObjectTransparency(o, *(int*) (o + 0x1cc), col);
	if (*(int*) (*a + 0x124) != 0) {
		o = **(int**) (*a + 0x124);
		d3_ChangeObjectTransparency(o, *(int*) (o + 0x1cc), col);
	}
	return 0;
}
