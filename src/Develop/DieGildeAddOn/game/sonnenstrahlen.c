#include "sonnenstrahlen.h"

#ifdef REBREW_GOLD
#define fcn_00445600 fcn_00449690
#define fcn_00442910 fcn_00446e10
#define fcn_00418860 fcn_004172e0
#endif

extern int g_6b7fac;
extern int SonnenstrahlenAktiv;
extern int SonnenstrahlenStartZeit;
extern int SonnenstrahlenPhase;
char* __cdecl fcn_00445600(char*, int, char*, char*);
char* __cdecl fcn_00442910(char*, float*, float*, char*);
void __cdecl StartSonnenstrahlen(char* unused)
{
	int value;
	value = g_6b7fac;
	SonnenstrahlenAktiv = 1;
	SonnenstrahlenStartZeit = value;
	SonnenstrahlenPhase = 0;
}
void __cdecl fcn_00418860(char*);

extern char* g_6b8014;
extern char* g_6b5cf8;

char* __cdecl CreateSonnenstrahlen(void)
{
	float rotation[3];
	float position[4];
	char* licht;
	float value;

	licht = fcn_00445600(0, 8, 0, "pLicht");
	rotation[0] = 0.0f;
	value = *(float*) (licht + 0x88);
	rotation[2] = 0.0f;
	rotation[1] = value;
	value = *(float*) (g_6b8014 + 0x4c);
	position[0] = value;
	value = *(float*) (g_6b8014 + 0x50);
	position[1] = value;
	value = *(float*) (g_6b8014 + 0x54);
	position[2] = value;
	g_6b5cf8 = fcn_00442910(0, position, rotation, "sonnenstrahlen");
#ifdef REBREW_GOLD
	g_6b5cf8[0x212] |= 0x0c;
	g_6b5cf8[0x211] &= ~2;
#else
	g_6b5cf8[0x216] |= 3;
	g_6b5cf8[0x214] &= 0x7f;
#endif
	*(int*) (g_6b5cf8 + 0x220) = 5;
	*(int*) (g_6b5cf8 + 0x224) = 1;
#ifdef REBREW_GOLD
	g_6b5cf8[0x213] &= ~4;
#else
	g_6b5cf8[0x217] &= ~1;
#endif
	StartSonnenstrahlen(g_6b5cf8);
	fcn_00418860(g_6b5cf8);
	return g_6b5cf8;
}

void __cdecl StopSonnenstrahlen(char* objekt, int phase)
{
    int zeit;

    zeit = g_6b7fac;
    SonnenstrahlenAktiv = -1;
    SonnenstrahlenStartZeit = zeit;
    SonnenstrahlenPhase = phase;
}
