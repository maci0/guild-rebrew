// FUNCTION: GOLD 0x005075c0
// FUNCTION: GOLDTL 0x0050a710

typedef struct
{
	unsigned short id;
	unsigned char x2;
	char pad3;
	int x4;
	char pad8[0x54];
	int x5c;
	int x60;
	int x64;
	int x68[5];
	char pad7c[0x1a0];
} Ent21c;
// SIZE 0x21c

extern char g_7f4ca0[];
extern int g_773d70;

#pragma pack(push, 1)
typedef struct
{
	int id;
	char p4[0xe];
	int x12;
	char p16[0xf];
	unsigned int x25;
	char p29[4];
} Rec2d;
// SIZE 0x2d
#pragma pack(pop)

#include "client_types.h"
extern Rec2d_9a3800 g_9a3800[512];

int __cdecl fcn_0050a710(unsigned char* p)
{
	int id;
	int i;
	int j;
	int found;
	int cnt;

	if (p[2] == 6 || p[2] == 7) {
		return 0;
	}
	id = *(int*) (p + 4);
	for (i = 0; i < 768; i++) {
		found = 0;
		cnt = 0;
		if (((Ent21c*)g_7f4ca0)[i].x4 != id && (((Ent21c*)g_7f4ca0)[i].x2 == 6 || ((Ent21c*)g_7f4ca0)[i].x2 == 7)) {
			if (((Ent21c*)g_7f4ca0)[i].x5c == id || ((Ent21c*)g_7f4ca0)[i].x60 == id || ((Ent21c*)g_7f4ca0)[i].x64 == id) {
				return 0;
			}
			for (j = 0; j < 5; j++) {
				if (((Ent21c*)g_7f4ca0)[i].x68[j] == id) {
					found |= 1;
					cnt++;
				} else if (((Ent21c*)g_7f4ca0)[i].x68[j] != -1) {
					cnt++;
				}
			}
			if (found && cnt < 5) {
				return 0;
			}
		}
	}
	if (0x300 - g_773d70 < 0x20) {
		return 1;
	}
	for (i = 0; i < 512; i++) {
		if (((Rec2d*)g_9a3800)[i].x12 == id && ((Rec2d*)g_9a3800)[i].x25 != 0) {
			return 0;
		}
	}
	return 1;
}
