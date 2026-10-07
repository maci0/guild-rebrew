#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c06;

// FUNCTION: GOLDTL 0x5392a0

int sprintf(char*, const char*, ...);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00442e30(void);
void __cdecl fcn_00514120(char*);
void __cdecl fcn_0051e080(char*, char*, int);
void __cdecl gm_InitEntitySlots(void);
void __cdecl gm_ResetAllEntities(void);
void __cdecl fcn_005012f0(void);
void __cdecl fcn_00510930(void);
int __cdecl fcn_0051e070(void);
void __cdecl fcn_00448360(char*, int, int);

void __cdecl fcn_005392a0(char* name, int net)
{
	char path[0x104];

	fcn_004432d0(0, 0);
	fcn_00442e30();
	fcn_00514120(name);
	if (net != 0) {
		sprintf(path, "%s/%s.NET", "gamedata/cities", name);
	} else {
		sprintf(path, "%s/%s.CTY", "gamedata/cities", name);
	}
	(*(int*)&g_7f4c00) = 0;
	(*(short*)&g_7f4c04) = 6;
	g_7f4c06 = 0;
	fcn_0051e080(path, "city", 2);
	gm_InitEntitySlots();
	gm_ResetAllEntities();
	fcn_005012f0();
	fcn_00510930();
	fcn_004432d0(0, 0);
	fcn_00442e30();
	if (fcn_0051e070() == 0) {
		fcn_00448360("scenes/*ChooseCity.ed3", 0, 0);
	} else {
		fcn_00448360("scenes/*ChooseCity_Europa.ed3", 0, 0);
	}
}
