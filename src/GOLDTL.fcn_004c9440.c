// FUNCTION: GOLDTL 0x4c9440
// SIZE: 230

#include <string.h>

#pragma pack(2)
typedef struct {
	int t;
	unsigned short type;
	int f6;
	int f10;
} stamp14;
// SIZE 0xe
#pragma pack()

extern stamp14 g_7f4c00;
extern int g_6a3438;
extern int g_6a3434;
extern int g_6a3430;
extern int g_772620;
extern char g_100dc20[];
extern char g_7f4ca0[];

int __cdecl fcn_00500cb0(stamp14*, stamp14*);
void __cdecl fcn_00546d10(void);
void __cdecl fcn_004fc180(void);
void __cdecl fcn_00500a40(void);
void __cdecl fcn_0047cf30(void);
void __cdecl fcn_0047de50(char*);
void __cdecl fcn_0047da10(void);
void __cdecl fcn_005c6310(void);
void __cdecl fcn_00531b80(void);

int __cdecl fcn_004c9440(char* x, char* out)
{
	int i;

	if (fcn_00500cb0(&g_7f4c00, (stamp14*) (x + 0x10)) < 0) {
		g_7f4c00 = *(stamp14*) (x + 0x10);
		if (g_6a3438 != 0)
			fcn_00546d10();
		if (g_6a3434 != 0) {
			fcn_004fc180();
			if (g_7f4c00.f6 % 6 == 0)
				fcn_00500a40();
		}
		if (g_6a3430 != 0)
			fcn_0047cf30();
		memset(g_100dc20, 0, 0xb00);
		if (g_6a3430 != 0) {
			g_772620 = 0;
			for (i = 0; i < 0x300; i++) {
				if (*(unsigned short*) (g_7f4ca0 + i * 0x21c) != 0xffff)
					fcn_0047de50(g_7f4ca0 + i * 0x21c);
			}
			fcn_0047da10();
		}
		fcn_005c6310();
		fcn_00531b80();
	}
	if (out != 0)
		*out = 1;
	return 0;
}
