


#include <string.h>

// SIZE 0x7c
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
