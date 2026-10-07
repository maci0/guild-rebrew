#include <string.h>

extern char g_6812d0[][32];

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_004bca30(char*);
void __cdecl fcn_00455350(char*, char*, float*);
char* __cdecl fcn_00403b90(char*, float*);
char* __cdecl fcn_0040c120(char*, int, int);

// FUNCTION: GOLD 0x004bbf00
// FUNCTION: GOLDTL 0x4bc410

void __cdecl fcn_004bc410(char** a1, int kind)
{
	float pos[4];
	char buf[0x80];
	char* ent;
	char* obj;

	fcn_0064d41a(buf, "dummy_%s", g_6812d0[kind]);
	ent = fcn_004bca30(buf);
	if (ent == 0)
		return;
	fcn_00455350(ent, ent + 0x4c, pos);
	if (kind == 3)
		strcpy(buf, "kuh_KUH");
	else if (kind == 7)
		strcpy(buf, "pferd_PFERD");
	else if (kind == 6)
		strcpy(buf, "schwein_SCHWEIN");
	obj = fcn_00403b90(buf, pos);
	a1[0] = obj;
	if (obj != 0) {
		*(float*) (obj + 0x1a0) = 1.0f;
		*(float*) (a1 + 4) = pos[0];
		*(float*) (a1 + 5) = pos[1];
		*(float*) (a1 + 6) = pos[2];
		*(int*) (a1 + 1) = kind;
		*(int*) (a1[0] + 4) = 2;
		*(int*) (*(char**) (a1[0] + 0x34) + 0x224) = 0;
		fcn_0040c120(a1[0], 0x38, 1);
	}
}
