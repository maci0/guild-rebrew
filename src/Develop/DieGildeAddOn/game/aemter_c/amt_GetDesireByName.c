#include <stdio.h>
#include <string.h>

extern int g_6798d4;
extern unsigned char* lpGebaeudePROT;
extern int vfs_RootDir;
extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern int d2_CurrentWindowId;

int __cdecl vfs_ResolvePath(char* a, int b, int c, char* out);
int __cdecl gm_CalcBuildingCost(int a, int b);
char* __cdecl _strupr(char* s);
void __cdecl d3_GetObjectWorldPosition(char* a, int b);
void __cdecl d3_ComputeObjectYawToTarget(float* out, int obj);
void __cdecl cm_SendCopyEntityData(int a1);

extern int d3_CurrentContextIndex;
extern char* gm_CityEntity;
extern int g_6798d4;    
extern char g_7e1ae0[]; 
extern char g_67f0ac[]; 
extern char g_68de2c[]; 

void __cdecl ReportClientMessage(const char*);
int __cdecl gm_RandomMod(int);
int __cdecl d3_SelectSceneContext(int, int);
int __cdecl d3_TransformPoint(char*, char*, int*);
void __cdecl cm_SendCopyEntityData(int a1);
int __cdecl amt_SendOfficeCommand(unsigned char, char*, char*, int, int);
void __cdecl amt_NotifyOfficeAppointed(void*, unsigned int);
void __cdecl amt_NotifyOfficeLost(void*, unsigned int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_CalcPersonWealth(unsigned short);
void __cdecl lc_GetBauplatzPrefix(int, char*);
int __cdecl d3_CollectUnusedSceneObjects(char*, int*);
void __cdecl d3_ComputeObjectYawToTarget(float* out, int obj);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strupr(char*);

/* ADDRESS: GOLD 0x004a47c0 */
/* ADDRESS: GOLDTL 0x004a4200 */
int __cdecl amt_GetDesireByName(char* name)
{
	char buf[0x80];

	if (_strcmpi(name, "APS") == 0) {
		return 0;
	}
	if (_strcmpi(name, "UNVERSEHRTHEIT") == 0) {
		return 1;
	}
	if (_strcmpi(name, "WOHNUNG") == 0) {
		return 2;
	}
	if (_strcmpi(name, "GELD") == 0) {
		return 3;
	}
	if (_strcmpi(name, "BERUF") == 0) {
		return 4;
	}
	if (_strcmpi(name, "VERGNUEGEN") == 0) {
		return 5;
	}
	if (_strcmpi(name, "ANSEHEN") == 0) {
		return 6;
	}
	if (_strcmpi(name, "AMT") == 0) {
		return 7;
	}
	if (_strcmpi(name, "BILDUNG") == 0) {
		return 8;
	}
	if (_strcmpi(name, "RECHTSCHAFFENHEIT") == 0) {
		return 9;
	}
	if (_strcmpi(name, "GEMEINHEIT") == 0) {
		return 10;
	}
	if (_strcmpi(name, "SICHERHEIT") == 0) {
		return 11;
	}
	if (_strcmpi(name, "FORTPFLANZUNG") == 0) {
		return 12;
	}
	if (_strcmpi(name, "TRAEGHEIT") == 0) {
		return 13;
	}
	sprintf(buf, "amt_GetDesireByName(): Unbekanntes Bed\xfcrfnis: %s", name);
	return -1;
}
