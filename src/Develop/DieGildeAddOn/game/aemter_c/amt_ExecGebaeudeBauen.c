#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include <stdio.h>
#include <string.h>
#include "client_data.h"
extern unsigned char* lpGebaeudePROT;
extern int g_6b7fdc;




int __cdecl vfs_ResolvePath(char* a, int b, int c, char* out);
int __cdecl fcn_0050d200(int a, int b);
char* __cdecl _strupr(char* s);
void __cdecl fcn_005986f0(char* a, int b);
void __cdecl d3_ComputeObjectYawToTarget(float* out, int obj);
void __cdecl fcn_004c5530(int a1);

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* gm_CityEntity;
extern char g_67f0ac[]; 
extern char g_68de2c[]; 

void __cdecl ReportClientMessage(const char*);
int __cdecl gm_RandomMod(int);
int __cdecl d3_SelectSceneContext(int, int);
int __cdecl d3_TransformPoint(char*, char*, int*);
void __cdecl fcn_004c5530(int a1);
int __cdecl amt_SendOfficeCommand(unsigned char, char*, char*, int, int);
void __cdecl amt_NotifyOfficeAppointed(void*, unsigned int);
void __cdecl amt_NotifyOfficeLost(void*, unsigned int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl fcn_00597ff0(int, char*);
int __cdecl d3_CollectUnusedSceneObjects(char*, int*);
void __cdecl d3_ComputeObjectYawToTarget(float* out, int obj);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strupr(char*);

/* ADDRESS: GOLDTL 0x004a4d90 */
int __cdecl amt_ExecGebaeudeBauen(int a0, char* a1, char* a2)
{
	char buildingName[260];
	char path[260];
	char resolvedPath[256];
	char event[0xf8];














	int v3;
	int v4;
	int v6;

	if (*a1 != 5) {
		return 0;
	}
	if (*a2 != 12) {
		return 0;
	}
	v3 = *(unsigned int*) (a2 + 4);
	*(int*) buildingName = g_6798d4;
	strcat(buildingName, (char*) ((char *)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(int*) (a1 + 4)] + 1));
	_strupr(buildingName + 2);
	v4 = 0;
	for (;;) {
		if (v4) {
			sprintf(path, (char*) 0x67f0c0, (char*) 0x7e1ae0, buildingName,
				(char) (v4 + '@'));
		}
		else {
			sprintf(path, (char*) 0x67f0ac, (char*) 0x7e1ae0, buildingName);
		}
		v6 = vfs_ResolvePath(path, g_6b7fdc, g_6b7fdc, resolvedPath);
		if (v6) {
			break;
		}
		if (v4) {
			sprintf(buildingName, (char*) 0x67f074,
				(char*) ((char *)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(int*) (a1 + 4)] + 1));
			return 0;
		}
		v4 = 1;
	}
	sprintf(event + 0x9c, (char*) 0x679060, path);
	*(pos14_7f4c00*) (event + 0x28) = gm_GameTime;
	v6 = *(unsigned int*) (a0 + 4);

	*(int*) (event + 0xc) = *(int*) (event + 8) = v6;
	*(int*) (event + 0x58) = v6;

	v4 = *(unsigned int*) (a1 + 4);
	event[4] = 13;

	event[0x36] = 2;
	*(int*) (event + 0x5c) = v4; *(int*) (event + 0x60) = fcn_0050d200(a0, v4);
	fcn_005986f0(event + 0x80, v3);
	d3_ComputeObjectYawToTarget((float*) (event + 0x90), v3);
	fcn_004c5530((int) event);
	return 1;
}
