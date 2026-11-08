extern int g_7e46ac;
extern int g_1040490;
extern int g_1040494;
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern char g_67d67c[];

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00533cf0(int);
void __cdecl fcn_0046b4f0(void);
void __cdecl fcn_00469e30(int);
void __cdecl fcn_00473150(unsigned char*);
void __cdecl fcn_005270c0(int);
#include <string.h>

typedef struct {
	int type;
	char name[0x78];
} SaveReq;

extern unsigned char g_7747b0;
extern char* g_14ac604;
extern int g_14ac608;
extern char g_773de8;
extern char g_6b5c60[];

void __cdecl fcn_00533a40(char*);
int __cdecl fcn_005e4060(void);
int __cdecl fcn_004c5790(int, void*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005e3d20(void);
void __cdecl fcn_0051e080(char*, char*, int);

/* ADDRESS: GOLDTL 0x005e3b70 */
void __cdecl fcn_005e3b70(void)
{
	int flags;
	unsigned char* p;

	flags = (g_7e46ac & ~0x2000) | 0x100000;
	p = fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x1e, 1);
	while (!(*p & 4)) {
		fcn_005373e0(0, flags);
	}
	g_1040488 = 0;
	g_1040480 = g_1040494;
	g_1040484 = 0;
	g_104048c = g_1040490;
	g_7e46ac = 0x24087;
	fcn_00533cf0(1);
	fcn_0046b4f0();
	fcn_00469e30(0x794);
	fcn_00473150(p);
	fcn_005270c0(0);
	fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x32, 0xa);
}

/* ADDRESS: GOLD 0x005d7580 */
/* ADDRESS: GOLDTL 0x005e40b0 */
void __cdecl fcn_005e40b0(void)
{
	SaveReq s;
	int r;

	if (g_7747b0 & 4) {
		if (!(g_7747b0 & 0x10)) {
			fcn_00533a40((char*) g_14ac608);
			return;
		}
		if (fcn_005e4060() == 0) {
			fcn_00533a40((char*) (*(int*)&g_14ac604));
			return;
		}
		memset(&s, 0, sizeof(s));
		s.type = 1;
		strcpy(s.name, "QUICKSAVE");
		r = fcn_004c5790(0xf, &s);
		while (fcn_004c4450(r) == 0) {
			fcn_00535960();
		}
	} else if (!(g_7747b0 & 0x80)) {
		fcn_00533a40("Quicksave");
		fcn_005373e0(0, 0x657c7);
		fcn_005e3d20();
		g_773de8 = 1;
		fcn_0051e080("Gamedata\\Saves\\Quicksave.SAV", "Quicksave", 1);
		fcn_00533a40(g_6b5c60);
	}
}
