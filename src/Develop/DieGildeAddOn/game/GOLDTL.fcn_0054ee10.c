#pragma pack(push, 1)
typedef struct
{
	int a;
	int b;
	int c;
	short d;
} fcn_0054ee10_Stamp;
// SIZE 0xe
#pragma pack(pop)

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_6a5af4[];
extern char g_6a5ae0[];

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_00500bb0(fcn_0054ee10_Stamp* s, int a2, int a3, int a4);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_004f4f60(int a, int b, int c, int d, int e);
void __cdecl fcn_004c54c0(int a1, int a2, int a3, int a4);
int __cdecl fcn_004f6470(int id, int* out, unsigned short k);
void __cdecl fcn_00508cf0(int n, int* out);
void __cdecl fcn_004c58f0(int a1, int a2, int a3);
int __cdecl fcn_004b4650(char* a1, int kind);
void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5);
void __cdecl fcn_004c6ae0(int a1, int a2);
int __cdecl fcn_004c5620(int a1, char* e);

/* ADDRESS: GOLDTL 0x0054ee10 */
void __cdecl fcn_0054ee10(char* t)
{
	int impactValue;
	int pick[16];
	int ids[32];
	char buf[0x100];
	char* firstEntity;
	char* secondEntity;
	int id;
	int n;
	int i;

	*(fcn_0054ee10_Stamp*) (t + 0x52) = (*(fcn_0054ee10_Stamp*)&gm_GameTime);
	*(int*) (t + 0x70) = 2;
	if ((t[0x78] & 2) == 0)
		return;
	firstEntity = gm_LookupEntityRecordById(*(int*) (t + 0xac));
	secondEntity = gm_LookupEntityRecordById(*(int*) (t + 0xb0));
	if (firstEntity == 0 || (*(int*) (firstEntity + 0x1c8) & 0x100) || secondEntity == 0 || (*(int*) (secondEntity + 0x1c8) & 0x200)) {
		*(fcn_0054ee10_Stamp*) (t + 0x52) = (*(fcn_0054ee10_Stamp*)&gm_GameTime);
		fcn_00500bb0((fcn_0054ee10_Stamp*) (t + 0x52), 0, 2, 0);
		*(int*) (t + 0x84) = fcn_004c5620(-1, t);
		return;
	}
	if (*(int*) (t + 0xb4) != 0) {
		fcn_00500bb0((fcn_0054ee10_Stamp*) (t + 0x52), 0x18, 0, 0);
		*(int*) (t + 0x58) = 0;
		if (secondEntity[2] == 6 || secondEntity[2] == 7) {
			io_FormatTextBuffer(buf, 0x1e18, *(unsigned short*) firstEntity);
			fcn_00545d40(*(int*) (secondEntity + 4), -1, buf, 0, 0x5fb, g_6a5af4);
		}
		impactValue = -4;
	} else {
		fcn_00500bb0((fcn_0054ee10_Stamp*) (t + 0x52), 0x60, 0, 0);
		*(int*) (t + 0x58) = 0;
		impactValue = -2;
		if (secondEntity[2] == 6 || secondEntity[2] == 7) {
			io_FormatTextBuffer(buf, 0x1d5b, *(unsigned short*) firstEntity, *(unsigned short*) firstEntity);
			fcn_00545d40(*(int*) (secondEntity + 4), -1, buf, 0, 0x5fb, g_6a5ae0);
		}
		id = -1;
		if (*(char**) (firstEntity + 0x170) != 0)
			id = *(int*) (*(char**) (firstEntity + 0x170) + 1);
		else if (*(char**) (secondEntity + 0x170) != 0)
			id = *(int*) (*(char**) (secondEntity + 0x170) + 1);
		fcn_004f4f60(0x16, 1, *(int*) (firstEntity + 4), *(int*) (secondEntity + 4), id);
		fcn_004c54c0(*(int*) (firstEntity + 4), *(int*) (secondEntity + 4), 0x34, 1);
		n = fcn_004f6470(*(int*) (secondEntity + 4), ids, *(unsigned short*) firstEntity);
		fcn_00508cf0(n < 0x10 ? n : 0x10, pick);
		for (i = 0; i < 3; i++, n--) {
			if (n == 0)
				break;
			fcn_004c58f0(ids[pick[i]], *(int*) (firstEntity + 4), 0);
		}
		if (firstEntity[2] == 6)
			fcn_004b4650(firstEntity, 0xb);
	}
	fcn_004c5420(*(int*) (firstEntity + 4), 0x1c8, 4, 0x100, 0);
	fcn_004c5420(*(int*) (secondEntity + 4), 0x1c8, 4, 0x200, 0);
	fcn_004c6ae0(*(int*) (firstEntity + 4), impactValue);
}
