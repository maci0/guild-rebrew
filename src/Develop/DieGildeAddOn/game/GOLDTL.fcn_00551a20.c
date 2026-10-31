
#pragma pack(push, 1)
typedef struct
{
	int a;
	int b;
	int c;
	short d;
} fcn_00551a20_Stamp;
// SIZE 0xe
#pragma pack(pop)

// SIZE 0x21c
typedef struct
{
	unsigned short id;
	char pad2[0x21c - 2];
} fcn_00551a20_Ent;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

int __cdecl fcn_004c4450(int id);
void __cdecl fcn_00546190(char* t);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_004c5620(int a1, char* e);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl he_RegisterApEvent(int, char*, int, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_005dcf40(fcn_00551a20_Ent* e, int v);

void __cdecl fcn_00551a20(char* t)
{
	char buf[0x100];
	fcn_00551a20_Ent* e;
	char* p;
	char* q;

	if (*(int*) (t + 0x70) == -2 || *(int*) (t + 0x70) == -1) {
		fcn_00546190(t);
		return;
	}
	if (t[0x78] & 4)
		return;
	if (*(int*) (t + 0x84) != -1 && fcn_004c4450(*(int*) (t + 0x84)) == 0)
		return;
	*(int*) (t + 0x84) = -1;
	switch (*(int*) (t + 0x70)) {
	case 1:
		e = &((fcn_00551a20_Ent*) g_7f4ca0)[*(unsigned short*) (t + 8)];
		p = gm_LookupEntityRecordById(*(int*) (t + 0xac));
		if (p == 0) {
			*(fcn_00551a20_Stamp*) (t + 0x52) = (*(fcn_00551a20_Stamp*) &g_7f4c00);
			fcn_004c5620(-1, t);
			return;
		}
		io_FormatTextBuffer(buf, 0x1a9f, e->id);
		fcn_00545d40(*(int*) (p + 4), *(int*) (p + 4), buf, 0, 0x5f4, 0);
		q = (char*) gm_GetEntityTableEntry((char*) (p));
		if (q != 0) {
			(*(int*) (q + 0x64))++;
		}
		*(fcn_00551a20_Stamp*) (t + 0x52) = (*(fcn_00551a20_Stamp*) &g_7f4c00);
		fcn_004c5620(-1, t);
		return;
	case 0:
		e = &((fcn_00551a20_Ent*) g_7f4ca0)[*(unsigned short*) (t + 8)];
		p = gm_LookupEntityRecordById(*(int*) (t + 0xac));
		if (p == 0) {
			*(fcn_00551a20_Stamp*) (t + 0x52) = (*(fcn_00551a20_Stamp*) &g_7f4c00);
			fcn_004c5620(-1, t);
			return;
		}
		fcn_005dcf40(e, *(unsigned char*) (t + 0xb8));
		fcn_005dcf40(e, *(unsigned char*) (t + 0xb9));
		io_FormatTextBuffer(buf, 0x1a9e, e->id);
		t[0xba]++;
		*(short*) (t + 0x56) += 0x18;
		*(int*) (t + 0x70) = (unsigned char) t[0xba] >= 5;
		he_RegisterApEvent(*(unsigned short*) p, buf, 0, -*(int*) (t + 0xb4));
		return;
	}
}
