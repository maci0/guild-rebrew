// FUNCTION: GOLDTL 0x005b54b0

#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
typedef struct {
	unsigned short id;
	char pad2[2];
	int handle;
	char pad8[0x164];
	char* owner;
	char pad170[0xac];
} House5b54;

#define HOUSES 768

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char* g_773da8;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl fcn_00503e80(void);
char* __cdecl gm_ResolveParentEntity(char*);
void __cdecl fcn_004d1d40(char*, char);
void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004c5980(void* data);

void __cdecl fcn_005b54b0(char* p)
{
	char msg[0x114];
	char* e;
	char* par;
	int i;
	int n;

	e = gm_StartFilteredEntitySearch(1, 5, 0x10);
	if (e == 0) {
		return;
	}
	do {
		if (*(short*) (e + 0x27) != *(short*) g_773da8) {
			break;
		}
		fcn_00503e80();
	} while (1);
	par = gm_ResolveParentEntity(p);
	memset(msg, 0, sizeof(msg));
	msg[8] = 3;
	msg[0x26] = (char) 0xa2;
	*(int*) (msg + 0x14) = -1;
	msg[0x30] = 2;
	*(int*) (msg + 0xc) = ((House5b54*)g_7f4ca0)[g_774970].handle;
	*(int*) (msg + 0x34) = ((House5b54*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].handle;
	*(int*) (msg + 0x38) = *(int*) (par + 4);
	msg[0x7c] = 9;
	for (i = 0; i < 16; i++) {
		((int*) (msg + 0xc0))[i] = -1;
		((int*) (msg + 0x80))[i] = -1;
	}
	for (i = 0; i < 3; i++) {
		if (p != 0 && i == 0) {
			((int*) (msg + 0x100))[i] = *(int*) (p + 2);
		}
		else {
			((int*) (msg + 0x100))[i] = -1;
		}
	}
	if (p[0x28] == 2) {
		fcn_004d1d40(msg, 2);
		fcn_004d1d40(msg, 1);
	}
	else {
		fcn_004d1d40(msg, p[0x28]);
	}
	*(int*) (msg + 0x10c) = *(int*) (e + 1);
	n = 0;
	for (i = 0; i < HOUSES; i++) {
		if (n >= 4) {
			break;
		}
		if (((House5b54*)g_7f4ca0)[i].id != 0xffff && ((House5b54*)g_7f4ca0)[i].owner == e) {
			((int*) (msg + 0xc0))[n] = ((House5b54*)g_7f4ca0)[i].handle;
			n++;
		}
	}
	*(int*) (msg + 0x18) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x1c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x20) = g_7f4c08;
	*(short*) (msg + 0x24) = g_7f4c0c;
	fcn_00500bb0(msg + 0x18, 0, 0xf, 0);
	fcn_004c5980(msg);
}
