#include <stdio.h>
#include <string.h>

extern int g_14cbca0;
extern int g_699364;
extern char* g_868050;
extern char g_7f4ca9[];
extern int g_6798d4;
extern int g_6b7fdc;
extern int g_6b8010;
extern int g_6b8014;
extern int g_773dd8;
extern unsigned char g_773dd4;
extern unsigned char g_773d75;
extern unsigned int g_67a370;
extern int g_774728;
extern float g_6a2bec;
extern float g_664ec0;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_0041d9e0(const char*);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char*);
void __cdecl fcn_00504250(unsigned char*);
void __cdecl gv_UpgradeField(unsigned char*);
int __cdecl fcn_0042f690(char*, int, int, char*);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00455350(char*, char*, int*);
int __cdecl fcn_004488e0(char*, int, int);
void __cdecl fcn_00455140(char*, float*, float*);
float __cdecl fcn_00451380(float*, float*);
void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_00438cb0(char*, int*);
void __cdecl fcn_00598860(int, void*);
void __cdecl fcn_004550b0(int, int);
void __cdecl d3_DestroyObject(int);
char __cdecl fcn_00413680(char*, char*, float*, float*);
char* __cdecl fcn_00426fd0(int);
void __cdecl fcn_00428340(char*, int, ...);
void __cdecl fcn_00510820(int, void*, int);
void __cdecl fcn_0052d9d0(void*);
int __cdecl fcn_00500e20(char*);
void __cdecl fcn_005165b0(int);
char __cdecl fcn_00437ac0(char*, char*, unsigned int, void (__cdecl*)(char*));
void __cdecl fcn_004379a0(int, int, int, int, void*);
void* __cdecl fcn_00426cc0(int);
int __cdecl fcn_00428720(int);
void __cdecl fcn_0052db70(char*);
void __cdecl fcn_00501d20(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_0066080a(char*);
long __cdecl _ftol(float);

/* ADDRESS: GOLDTL 0x004cb7f0 */
int __cdecl fcn_004cb7f0(char* a0, char* a1)
{
	unsigned char* v4;
	char* rec;
	char name[0x80];
	char path[0x104];
	char tmp[0xfc];
	char vec[0x10];
	float center[4];
	float radius;
	float f;
	int saved;
	int h;
	int obj;
	int i;
	int res;

	if (g_14cbca0 != -1) {
		g_699364 = *(int*) (a0 + 0x14);
	}
	v4 = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0x10));
	if (v4 == 0) {
		return 1;
	}
	rec = g_868050 + v4[0] + v4[0] * 0x24c;
	if ((unsigned char) rec[0x247] >= (unsigned char) rec[0x248]) {
		fcn_0041d9e0("cm_ExSetGebUpgrade(): already highest level");
		return 1;
	}
	v4[0] = (unsigned char) (v4[0] + 1);
	v4[0x5c] = (unsigned char) ((100 - (int) (signed char) v4[0x5c]) / 2 + (signed char) v4[0x5c]);
	gm_SetBuildingWorkerLimits(v4);
	fcn_00504250(v4);
	if (*rec == 0x1d) {
		gv_UpgradeField(v4);
	}
	saved = g_6798d4;
	strcpy(name, g_868050 + v4[0] + v4[0] * 0x24c + 1);
	fcn_0066080a(name + 2);
	i = 0;
	for (;;) {
		if (*rec != 0x21) {
			if (i == 0) {
				fcn_0064d41a(path, (char*) 0x67f0ac, (char*) 0x7e1ae0, name);
			} else {
				fcn_0064d41a(path, (char*) 0x67f0c0, (char*) 0x7e1ae0, name, i + '@');
			}
		} else if (*(char*) (g_7f4ca9 + (*(unsigned short*) (v4 + 0x27)) * 0x21c) == 1) {
			fcn_0064d41a(path, "%sgebaeude/*%s_A.ogr", (char*) 0x7e1ae0, name);
		} else {
			fcn_0064d41a(path, "%sgebaeude/*%s_B.ogr", (char*) 0x7e1ae0, name);
		}
		if (fcn_0042f690(path, g_6b7fdc, g_6b7fdc, tmp) != 0) {
			break;
		}
		i++;
		if (i >= 4) {
			goto done;
		}
	}
	h = *(int*) (v4 + 0x61);
	fcn_004432d0(0, 1);
	fcn_00455350((char*) h, (char*) (h + 0x4c), (int*) vec);
	obj = fcn_004488e0(path, 0, 0);
	if (obj == 0) {
		sprintf(name, "cm_ExGebUpgrade(): Could not load 3D-Object-Group '%s'...", path);
		fcn_0041d9e0(name);
	} else {
		center[0] = 0.0f;
		fcn_00455140((char*) h, (float*) 0x662d40, center);
		radius = fcn_00451380((float*) 0x662d40, center);
		fcn_00438b40((char*) obj, (int*) vec);
		fcn_00438cb0((char*) obj, (int*) center);
		fcn_00598860(obj, vec);
		if (g_773dd8 != 0) {
			fcn_004550b0(h, g_773dd8);
		}
		d3_DestroyObject(h);
		if (*(int*) (obj + 0x1ec) != 0 && fcn_00413680((char*) obj, (char*) g_6b8014, center, &radius)) {
			res = (int) _ftol(radius * g_664ec0);
			h = (int) fcn_00426fd0(0x68b228);
			if (h != 0) {
				f = center[0];
				fcn_00428340((char*) h, 6, (int) _ftol(f), (int) _ftol(f), (int) _ftol(f),
				             (int) _ftol(f), res, obj);
				*(int*) (h + 0x104) = 0;
			}
		}
		fcn_00510820(obj, v4, 2);
	}
	fcn_0052d9d0(v4);
	h = *(int*) (v4 + 0x61);
	if (h != 0) {
		switch (fcn_00500e20((char*) 0x7f4c00)) {
		case 0:
			g_773dd4 = 0;
			break;
		case 1:
			g_773dd4 = 1;
			break;
		case 2:
			g_773dd4 = 2;
			break;
		case 3:
			g_773dd4 = 3;
			break;
		}
		fcn_005165b0(h);
		fcn_00437ac0((char*) g_67a370, (char*) h, 0x2c0, (void (__cdecl*) (char*)) 0x514d80);
		f = (float) g_774728 + g_6a2bec;
		fcn_004379a0(g_67a370, h, 0x21e, 0x445d20, &f);
		if (*(int*) (v4 + 0x95) != -1) {
			obj = (int) fcn_00426cc0(*(int*) (v4 + 0x95));
			if (obj != 0) {
				fcn_00428720(obj);
			}
			*(int*) (v4 + 0x95) = -1;
			fcn_0052db70((char*) v4);
		}
	}
	fcn_004432d0(saved, 1);
done:
	fcn_00501d20(g_773d75);
	if (a1 != 0) {
		a1[0] = 2;
		a1[1] = 0;
		*(int*) (a1 + 6) = 0;
	}
	return 0;
}
