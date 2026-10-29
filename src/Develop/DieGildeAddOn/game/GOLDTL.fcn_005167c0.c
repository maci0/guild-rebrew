#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char* g_entity_type_table;
extern char* g_7f3b24;
extern char g_7f3b40[];
extern signed char g_7f3b00[];
extern char* g_7f3ee0;
extern char g_7f4ca0[];
extern char s_6a1fdc[];
extern void* g_14d0020[];
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern char g_776664;
extern char g_773dd4;
extern char g_6b8061;
extern int g_6b8010;
extern int g_67530c;
extern int g_6791c8;
extern int g_6b86d8;
extern int g_67a370;
extern float g_67a964;

int __cdecl fcn_00500e20(char*);
int __cdecl gm_GetBuildingTypeCategory(int);
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
void __cdecl fcn_00516b70(void);
void __cdecl fcn_00516be0(void);
char* __cdecl fcn_00445600(char*, int, char*, char*);
char __cdecl fcn_00442d50(int, unsigned char);
int __cdecl gm_CheckEntityType(char*);
void __cdecl fcn_00437ac0(int, int, int, void (__cdecl*)(void));
void __cdecl fcn_004bd150(int);
void __cdecl fcn_00530a00(char*);
void __cdecl fcn_00505c80(char*);
int __cdecl fcn_00413190(int);
void __cdecl ch_SetVisible(char*, int);
int __cdecl fcn_004053a0(char*, int);
void __cdecl fcn_004fdcf0(char*);
void __cdecl fcn_004fdfe0(char*);
void* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl ch_UpdateAttachedModelPosition(char*, int);
void __cdecl fcn_00516550(void);
void __cdecl fcn_005165b0(void);
void __cdecl fcn_005156a0(void);
void __cdecl fcn_00515ef0(void);

/* ADDRESS: GOLDTL 0x005167c0 */
void __cdecl fcn_005167c0(unsigned char* a0, int a1)
{
	int mode;
	int type;
	int count;
	int i;
	unsigned char* rec;
	unsigned char* entity;
	unsigned char* obj;
	unsigned char** p;

	mode = fcn_00500e20(&(*(char*) &g_7f4c00));
	gm_GetBuildingTypeCategory(*a0);
	rec = (unsigned char*) (g_entity_type_table + *a0 * 0x24d);
	entity = (unsigned char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, a1);
	if (entity != 0 && *(unsigned short*) entity != 0xfd) {
		type = ((signed char*) g_7f3b40)[*(unsigned short*) entity];
		g_7f3b24 = (char*) entity;
		fcn_00516b70();
	} else {
		g_7f3b24 = 0;
		type = ((signed char*) g_7f3b00)[*rec];
		fcn_00516be0();
	}
	if (g_6b8010 != type
	    || (g_7746c4 != 0 && (unsigned char*) g_7746c4 != a0)
	    || (g_7746c8 != 0 && (unsigned char*) g_7746c8 != a0)) {
		return;
	}
	obj = (unsigned char*) fcn_00445600(0, 0x180, 0, s_6a1fdc);
	if (obj != 0) {
		fcn_00442d50((int) obj, g_776664 ? 1 : 0);
	}
	g_67530c = *(int*) (a0 + 1);
	if (g_7746cc != 0) {
		g_6791c8 = *(int*) (g_7746cc + 2);
	} else {
		g_6791c8 = *(int*) (a0 + 1);
	}
	if (mode == 1) {
		g_773dd4 = 1;
	} else if (mode == 0) {
		g_773dd4 = 0;
	} else if (mode == 2) {
		g_773dd4 = 2;
	} else if (mode == 3) {
		g_773dd4 = 3;
	}
	g_6b8061 = 0;
	g_67a964 = 1.0f;
	g_6b86d8 = 0x800;
	if (gm_CheckEntityType((char*) a0)) {
		fcn_00437ac0(g_67a370, 0, 0xc0, fcn_00516550);
		fcn_00437ac0(g_67a370, 0, 0xc0, fcn_005165b0);
	}
	if (*a0 == 0x1e && a1 == 0xfd) {
		fcn_004bd150(*(int*) (a0 + 0x71));
	}
	g_7f3ee0 = (char*) a0;
	fcn_00530a00((char*) a0);
	fcn_00437ac0(g_67a370, 0, 0x1e0, fcn_005156a0);
	fcn_00437ac0(g_67a370, 0, 0x20, fcn_00515ef0);
	fcn_00505c80((char*) a0);
	if (*rec == 0x16) {
		count = 8;
	} else {
		count = (*rec != 1) ? 8 : 4;
	}
	i = 0;
	p = (unsigned char**) g_14d0020;
	do {
		obj = *p;
		if (obj != 0 && (unsigned char*) fcn_00413190(*(int*) (obj + 0x88)) == entity) {
			if (*(int*) (obj + 0x2c) == *(int*) (a0 + 1)
			    || *(int*) (obj + 0x30) == *(int*) (entity + 2)) {
				ch_SetVisible((char*) obj, 1);
				fcn_004053a0((char*) obj, 0);
			} else {
				ch_SetVisible((char*) obj, 0);
			}
		}
		p++;
	} while ((int) p < 0x14d0c20);
	p = (unsigned char**) (g_7f4ca0 + 0x184);
	do {
		obj = *p;
		if (obj != 0 && (unsigned char*) fcn_00413190(*(int*) (obj + 0x88)) == entity) {
			if ((*(int*) (obj + 0x2c) != *(int*) (a0 + 1)
			     && *(int*) (obj + 0x30) != *(int*) (entity + 2))
			    || i >= count) {
				ch_SetVisible((char*) obj, 0);
			} else {
				ch_SetVisible((char*) obj, 1);
				fcn_004053a0((char*) obj, 0);
				fcn_004fdcf0((char*) p - 0x184);
				fcn_004fdfe0((char*) p - 0x184);
				i++;
			}
		}
		p = (unsigned char**) ((char*) p + 0x21c);
	} while ((int) p < 0x85a224);
	p = (unsigned char**) fcn_00502cd0(0, 2, 7, 4, 0x1d);
	while (p != 0) {
		obj = (unsigned char*) *(void**) ((char*) p + 0x3b);
		if (*(int*) (obj + 0x88) == g_67a370) {
			if (*(int*) (obj + 0x2c) == *(int*) (a0 + 1)) {
				ch_SetVisible((char*) obj, 1);
				fcn_004053a0((char*) obj, 0);
				ch_UpdateAttachedModelPosition((char*) obj, 1);
			} else if (*(int*) (obj + 0x88) == g_67a370) {
				ch_SetVisible((char*) obj, 0);
			}
		}
		p = (unsigned char**) gm_NextEntityQueryMatch();
	}
}
