

// SIZE 0x2
typedef struct {
	unsigned char kind : 5;
	unsigned char f5 : 1;
	unsigned char f6 : 1;
	unsigned char f7 : 1;
	unsigned char g0 : 1;
} Bits;

extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl SetEmitterFlags(char** a, int* s, unsigned char* k, unsigned char* b5, unsigned char* b6, unsigned char* b7, unsigned char* c0)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	*(float*) (e + 0xb4) = *s * 0.01f;
	((Bits*) (e + 0xd4))->kind = *k;
	((Bits*) (e + 0xd4))->f5 = *b5;
	((Bits*) (e + 0xd4))->f6 = *b6;
	((Bits*) (e + 0xd4))->f7 = *b7;
	((Bits*) (e + 0xd4))->g0 = *c0;
	return 0;
}
