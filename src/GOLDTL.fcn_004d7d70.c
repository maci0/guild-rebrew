// FUNCTION: GOLD 0x4d6970
// SIZE: 224
// FUNCTION: GOLDTL 0x4d7d70
// SIZE: 224

typedef struct {
	int id;
	int f4;
	int f8;
	char fc;
	char padd[3];
	char name[0x10];
	int f20;
	int f24;
	int f28;
} ent2c;
// SIZE 0x2c

extern int g_772f34;
extern int g_772f30;
extern int g_68bfbc;
extern int g_68b7a4;
extern int g_772f38;
extern int g_772ea4;
extern int g_100f1dc;
extern int g_67d370;
extern int g_68b7a8;
extern char* g_772f24;
extern int g_774654;

void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_0052ae80(void);
void __cdecl fcn_004d0a20(void);
void __cdecl fcn_004d06d0(void);
void __cdecl fcn_004d0f00(void);
void __cdecl fcn_004d1790(char*);
void __cdecl fcn_004d0070(void);
void __cdecl fcn_004cfc00(char*);
void __cdecl fcn_004cf180(void);
void __cdecl fcn_004cf6b0(void);
ent2c* __cdecl fcn_004ceac0(char*, char*);
int __cdecl fcn_004c67c0(int, ent2c*);

void __cdecl fcn_004d7d70(char* rec)
{
	ent2c l;

	fcn_00472380(g_68b7a4, 0, g_68bfbc, g_772f34 - g_772f30 + 1);
	fcn_0052ae80();
	fcn_004d0a20();
	fcn_004d06d0();
	fcn_004d0f00();
	fcn_004d1790(rec);
	fcn_004d0070();
	fcn_004cfc00(rec);
	fcn_004cf180();
	fcn_004cf6b0();
	if (g_772f38 != 0 || g_772ea4 != 0) {
		g_774654 = 1;
		return;
	}
	if (g_100f1dc == -1 || g_67d370 != g_68b7a8)
		return;
	l = *fcn_004ceac0(rec, g_772f24);
	l.id = *(int*) (g_772f24 + 4);
	l.f4 = 5;
	fcn_004c67c0(*(int*) (rec + 0x10), &l);
}
