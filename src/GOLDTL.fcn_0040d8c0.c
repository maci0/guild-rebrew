#include <string.h>

extern char* g_6b7e98;

void __cdecl fcn_00425bf0(char*, int, const char*);
void __cdecl fcn_004056a0(char*, int);

// FUNCTION: GOLDTL 0x40d8c0
// SIZE: 190

/* SetCharacterCamera(): puts the camera into one of the character views. */
int __cdecl fcn_0040d8c0(char** ch, char** view)
{
	if (*ch == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "SetCharacterCamera(): Invalid character");
		return 1;
	}
	if (strcmp("CLOSEUP", *view) == 0) {
		fcn_004056a0(*ch, 0);
	} else if (strcmp("LEFT_SHOULDER", *view) == 0) {
		fcn_004056a0(*ch, 1);
	} else if (strcmp("RIGHT_SHOULDER", *view) == 0) {
		fcn_004056a0(*ch, 2);
	} else if (strcmp("EGO", *view) == 0) {
		fcn_004056a0(*ch, 3);
	}
	return 0;
}
