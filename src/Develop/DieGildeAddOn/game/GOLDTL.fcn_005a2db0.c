#pragma pack(push, 2)
typedef struct Pos5a2db0 {
	int a;
	int b;
	int c;
	short d;
} Pos5a2db0;

typedef struct Msg5a2db0 {
	int pad0;
	unsigned char type;
	char pad5[3];
	int seed;
	int id;
	char pad10[0x28 - 0x10];
	Pos5a2db0 pos;
	unsigned char flag;
	char pad37[0x58 - 0x37];
	unsigned char mode;
	char pad59[3];
	int target;
	int from;
	char pad64[0xf8 - 0x64];
} Msg5a2db0;
#pragma pack(pop)

#include <string.h>
#include "client_types.h"

extern char* g_14ab4ec;
extern char* g_14ab54c;
extern char* g_14ab5cc;
extern char* g_7746a0;
extern int g_774808;
extern char g_14cf950;
extern unsigned short g_774970;
extern char g_7f4ca4[];
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl fcn_005338d0(char* name, char* path, int arg);
void __cdecl fcn_00597ec0(char* e);
void __cdecl fcn_005a1430(char* e);
void __cdecl fcn_005a2500(char* a, char* b);
void __cdecl fcn_005a2d60(char* a, char* b);
void __cdecl fcn_004c5530(Msg5a2db0* m);

#pragma optimize("y", off)


/* Runs one contact/office tick per pumped message, resolving the three
 * office markers and dispatching on the active contact. */
/* ADDRESS: GOLDTL 0x005a2db0 */
void __cdecl fcn_005a2db0(char* a0, char* a1)
{
	Msg5a2db0 m;
	char* p1;
	char* p2;
	char* p3;

	fcn_005338a0();
	while (fcn_005373e0(fcn_005a2db0, 0x67fff)) {
		fcn_00597ec0(a0);
		p1 = fcn_005338d0("contact_WUERFELSPIEL", g_14ab4ec, 0x16);
		p2 = fcn_005338d0("contact_STAMMTISCH", g_14ab54c, 0x16);
		p3 = fcn_005338d0("ob_DUNKLE_ECKE", g_14ab5cc, 0x16);
		if (g_7746a0) {
			if (g_7746a0 == p1) {
				fcn_005a1430(a0);
			} else if (g_7746a0 == p2) {
				fcn_005a2500(a0, a1);
			} else if (g_7746a0 == p3) {
				fcn_005a2d60(a0, a1);
			}
		}
		if (g_774808) {
			if (g_14cf950 == 0x12) {
				memset(&m, 0, sizeof(m));
				m.type = 0x74;
				m.seed = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
				m.id = -1;
				m.pos = *(Pos5a2db0*) &g_7f4c00;
				m.flag = 2;
				m.target = *(int*) (a0 + 1);
				m.from = *(int*) (a1 + 2);
				fcn_004c5530(&m);
			} else if (g_14cf950 == 0x17) {
				fcn_005a2d60(a0, a1);
			}
		}
	}
}
