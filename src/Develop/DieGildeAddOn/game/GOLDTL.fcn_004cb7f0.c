#include <stdio.h>
#include <string.h>

extern int g_14cbca0;
extern int gm_NextEntityId;
extern char* lpGebaeudePROT;
extern char g_7f4ca9[];
extern int g_6798d4;
extern int g_6b7fdc;
extern int d3_CurrentContextIndex;
extern int d3_ActiveCamera;
extern int g_773dd8;
extern unsigned char g_773dd4;
extern unsigned char g_773d75;
extern unsigned int g_67a370;
extern int g_774728;
extern float g_6a2bec;
extern float g_662d40[3];
extern char g_67f0ac[];
extern char g_7e1ae0[];
typedef struct {
 unsigned char kind; char name; char unknown002[0x245];
 unsigned char level, max_level; char unknown249[4];
} BuildingProto4cb7f0;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl ReportClientMessage(const char*);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char*);
void __cdecl fcn_00504250(unsigned char*);
void __cdecl gv_UpgradeField(unsigned char*);
int __cdecl vfs_ResolvePath(char*, int, int, char*);
void __cdecl d3_SelectSceneContext(int, int);
int __cdecl d3_TransformPoint(char*, char*, int*);
int __cdecl fcn_004488e0(char*, int, int);
void __cdecl fcn_00455140(char*, float*, float*);
float __cdecl fcn_00451380(float*, float*);
void __cdecl fcn_00438b40(char*, int*);
void __cdecl d3_SetObjectRotation(char*, int*);
void __cdecl fcn_00598860(int, void*);
void __cdecl fcn_004550b0(int, int);
void __cdecl d3_DestroyObject(int);
char __cdecl d3_ComputeObjectBoundingSphere(char*, char*, float*, float*);
char* __cdecl evt_LoadGfxScript(int);
void __cdecl fcn_00428340(char*, int, ...);
void __cdecl fcn_00510820(int, void*, int);
void __cdecl fcn_0052d9d0(void*);
int __cdecl fcn_00500e20(char*);
void __cdecl fcn_005165b0(int);
char __cdecl d3_TraverseSceneObjects(char*, char*, unsigned int, void (__cdecl*)(char*));
void __cdecl d3_VisitSceneObjects(int, int, int, int, void*);
void* __cdecl evt_FindScriptById(int);
int __cdecl evt_RequestScriptExit(int);
void __cdecl fcn_0052db70(char*);
void __cdecl fcn_00501d20(int);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x004cb7f0 */
int __cdecl fcn_004cb7f0(char* upgradeCmd, char* replyData)
{
	unsigned char* upgradeBuilding;
	BuildingProto4cb7f0* rec;
	char name[0x80];
	char path[0x104];
	char tmp[256];
	float vec[4];
	float direction[3];
	float angles[3];
	float radius;
	int saved;
	int h;
	int obj;
	int i;
	int res;

	if (g_14cbca0 != -1) {
		gm_NextEntityId = *(int*) (upgradeCmd + 0x14);
	}
	upgradeBuilding = gm_StartFilteredEntitySearch(1, 1, *(int*) (upgradeCmd + 0x10));
	if (upgradeBuilding == 0) {
		return 1;
	}
	rec = &((BuildingProto4cb7f0*)lpGebaeudePROT)[upgradeBuilding[0]];
	if (rec->level >= rec->max_level) {
		ReportClientMessage("cm_ExSetGebUpgrade(): already highest level");
		return 1;
	}
	upgradeBuilding[0] = (unsigned char) (upgradeBuilding[0] + 1);
	upgradeBuilding[0x5c] = (unsigned char) ((100 - (int) (signed char) upgradeBuilding[0x5c]) / 2 + (signed char) upgradeBuilding[0x5c]);
	gm_SetBuildingWorkerLimits(upgradeBuilding);
	fcn_00504250(upgradeBuilding);
	if (rec->kind == 0x1d) {
		gv_UpgradeField(upgradeBuilding);
	}
	*(int*)name = g_6798d4;
	strcat(name, &((BuildingProto4cb7f0*)lpGebaeudePROT)[upgradeBuilding[0]].name);
	_strupr(name + 2);
	i = 0;
	for (;;) {
		if (rec->kind == 0x21) {
			if (*(char*) (g_7f4ca9 + (*(unsigned short*) (upgradeBuilding + 0x27)) * 0x21c) == 1) {
				fcn_0064d41a(path, "%sgebaeude/*%s_A.ogr", g_7e1ae0, name);
			} else {
				fcn_0064d41a(path, "%sgebaeude/*%s_B.ogr", g_7e1ae0, name);
			}
		} else if (i != 0) {
			fcn_0064d41a(path, (char*)0x67f0c0, g_7e1ae0, name, (int)(char)(i + '@'));
		} else {
			fcn_0064d41a(path, g_67f0ac, g_7e1ae0, name);
		}
		if (vfs_ResolvePath(path, g_6b7fdc, g_6b7fdc, tmp) != 0) {
			break;
		}
		i++;
		if (i >= 4) {
			goto done;
		}
	}
	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	h = *(int*) (upgradeBuilding + 0x61);
	d3_TransformPoint((char*) h, (char*) (h + 0x4c), (int*) vec);
	obj = fcn_004488e0(path, 0, 0);
	if (obj == 0) {
		sprintf(name, "cm_ExGebUpgrade(): Could not load 3D-Object-Group '%s'...", path);
		ReportClientMessage(name);
		goto restore;
	} else {
		fcn_00455140((char*) *(int*)(upgradeBuilding + 0x61), g_662d40, direction);
		angles[0] = 0;
		angles[1] = 0;
		angles[2] = 0;
		angles[1] = fcn_00451380(g_662d40, direction);
		fcn_00438b40((char*) obj, (int*) vec);
		d3_SetObjectRotation((char*) obj, (int*) angles);
		fcn_00598860(obj, vec);
		if (g_773dd8 != 0) {
			fcn_004550b0(*(int*)(upgradeBuilding + 0x61), g_773dd8);
		}
		d3_DestroyObject(*(int*)(upgradeBuilding + 0x61));
		if (*(int*) (obj + 0x1ec) != 0 && d3_ComputeObjectBoundingSphere((char*) obj, (char*) d3_ActiveCamera, vec, &radius)) {
			res = (int)(radius * 1.8);
			h = (int) evt_LoadGfxScript(0x68b228);
			if (h != 0) {
				fcn_00428340((char*) h, 6, (int)vec[0], (int)vec[1], (int)vec[2],
				             (int)radius, res, obj);
				*(int*) (h + 0x104) = 0;
			}
		}
		fcn_00510820(obj, upgradeBuilding, 2);
	}
	fcn_0052d9d0(upgradeBuilding);
	h = *(int*) (upgradeBuilding + 0x61);
	if (h != 0) {
		float f;
		res = fcn_00500e20((char*) 0x7f4c00);
		if (res == 1) g_773dd4 = (unsigned char)res;
		else if (res == 0) g_773dd4 = (unsigned char)res;
		else if (res == 2) g_773dd4 = (unsigned char)res;
		else if (res == 3) g_773dd4 = (unsigned char)res;
		fcn_005165b0(*(int*)(upgradeBuilding + 0x61));
		d3_TraverseSceneObjects((char*) g_67a370, (char*) *(int*)(upgradeBuilding + 0x61), 0x2c0, (void (__cdecl*) (char*)) 0x514d80);
		f = (float) g_774728 + g_6a2bec;
		d3_VisitSceneObjects(g_67a370, *(int*)(upgradeBuilding + 0x61), 0x21e, 0x445d20, &f);
		if (*(int*) (upgradeBuilding + 0x95) != -1) {
			obj = (int) evt_FindScriptById(*(int*) (upgradeBuilding + 0x95));
			if (obj != 0) {
				evt_RequestScriptExit(obj);
			}
			*(int*) (upgradeBuilding + 0x95) = -1;
			fcn_0052db70((char*) upgradeBuilding);
		}
	}
restore:
	d3_SelectSceneContext(saved, 1);
done:
	fcn_00501d20(g_773d75);
	if (replyData != 0) {
		replyData[0] = 2;
		replyData[1] = 0;
		*(int*) (replyData + 6) = 0;
	}
	return 0;
}
