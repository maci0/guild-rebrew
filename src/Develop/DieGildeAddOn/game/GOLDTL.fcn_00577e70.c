#include <math.h>

extern char g_7f4ca0[];

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_004c5c80(int a1);
int __cdecl fcn_004c5da0(int who, int key, int target, char* name, int mode, char* text);
float __cdecl gm_GetEntitySkill(char* entity, int idx);
int __cdecl fcn_004c5620(char a1, unsigned char* e);
void __cdecl io_FormatTextBuffer(char* buf, char* fmt, ...);
void __cdecl fcn_00545d40();

/* ADDRESS: GOLDTL 0x00577e70 */
unsigned int __cdecl fcn_00577e70(char* a0, char* a1, char* a2)
{
	char v9[1024];
	char* v3;
	char* ent;
	unsigned char* v1;
	unsigned char* v8;
	unsigned short slot;
	float dx;
	float dy;
	float dz;
	float t0;
	float t1;

	if (a2 != 0 && *a2 == 0x18) {
		if (*(unsigned int*) (a1 + 0xc4) < 0x14) {
			*(unsigned int*) (a1 + 0xc4) = *(unsigned int*) (a1 + 0xc4) + 1;
			ent = gm_LookupEntityRecordById(*(unsigned int*) (a2 + 0xd8));
			if (ent != 0 && *(int*) (ent + 0x184) != 0) {
				v3 = (char*) *(int*) (*(int*) (a0 + 0x184) + 0x34);
				ent = (char*) *(int*) (*(int*) (ent + 0x184) + 0x34);
				dx = *(float*) (v3 + 0x4c) - *(float*) (ent + 0x4c);
				dy = *(float*) (v3 + 0x50) - *(float*) (ent + 0x50);
				dz = *(float*) (v3 + 0x54) - *(float*) (ent + 0x54);
				if (1850.0f <= (float) sqrt(dx * dx + dy * dy + dz * dz)) {
					if (*(int*) (a2 + 0xb4) != *(int*) (a1 + 0xac)) {
						*(int*) (a1 + 0xac) = *(int*) (a2 + 0xb4);
						fcn_004c5c80(*(unsigned int*) (a0 + 4));
						fcn_004c5da0(*(unsigned int*) (a0 + 4), *(unsigned int*) (a2 + 0xb4), -1, 0, 1, (char*) 0x6a7e3c);
					}
					return 0;
				}
				slot = *(unsigned short*) (a2 + 8);
				v1 = (unsigned char*) (slot * 0x21c + 0x7f4ca0);
				v8 = (unsigned char*) gm_LookupEntityRecordById(*(unsigned int*) (a2 + 0xc4));
				t0 = (float) (*(int*) (a2 + 0xe8) + 1) * 0.5f;
				t1 = (float) (*(int*) (a1 + 0xc0) + 1) * 0.5f;
				if (gm_GetEntitySkill((char*) v1, 2) + t0 < gm_GetEntitySkill((char*) v8, 2) + t1) {
					*(unsigned int*) (a2 + 0x84) = fcn_004c5620(-1, (unsigned char*) a2);
					io_FormatTextBuffer(v9, (char*) 0x4028, *v8);
					fcn_00545d40(*(unsigned int*) (slot * 0x21c + 0x7f4ca4), -1, v9, 1, 0x5fb, (char*) 0x6a7ea8);
					io_FormatTextBuffer(v9, (char*) 0x4029, *v1);
					fcn_00545d40(*(unsigned int*) (v8 + 4), -1, v9, 1, 0x5fb, (char*) 0x6a7ea8);
					return 1;
				}
			}
		}
	}
	return 0xffffffff;
}
