#include <math.h>

extern int g_1043370;
extern int g_6b8010;
extern int g_6b7fac;
extern float g_662920;
extern float g_665ea0;
extern double g_665ea8;
extern float g_6628bc;
extern float g_6628cc;
extern float g_662a3c;

int __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00455350(char*, char*, float*);
int __cdecl gm_ResolveEntityById(char**, int, int, int);
char __cdecl fcn_0045b990(int, float*, int*, int*, float*);
void __cdecl fcn_004518a0(float*);
void __cdecl fcn_00438b40(char*, float*);
int __cdecl fcn_004c48f0(void);

/* ADDRESS: GOLDTL 0x00558680 */
int __cdecl fcn_00558680(char* a0)
{
	float pos1[4];
	float pos2[4];
	float dir[4];
	char flag[4];
	int keys[4];
	float len;
	float scale;
	int saved;
	int level;
	int handle;
	int rec;
	int block;
	int ret;

	saved = g_6b8010;
	fcn_004432d0(0, 1);
	block = *(int*) (a0 + 0xc8);
	if (block != 0) {
		rec = *(int*) (block + 0x1cc);
		if (rec != 0 && *(int*) (rec + 0x318) != 0) {
			gm_ResolveEntityById(&handle, 0, 0, *(int*) (a0 + 0xb4));
			if (handle != 0) {
				rec = *(int*) (handle + 0x61);
				if (rec != 0) {
					level = *(int*) (rec + 0x1cc);
					if (level != 0 && *(int*) (level + 0x318) != 0) {
						if (*(int*) (*(int*) (a0 + 0xc8) + 0x1d0) != 0) {
							*(int*) (a0 + 0xec) = g_6b7fac;
							fcn_004432d0(saved, 1);
							return 1;
						}
						fcn_00455350((char*) rec, (char*) rec + 0x4c, pos1);
						block = *(int*) (a0 + 0xc8);
						fcn_00455350((char*) block, (char*) block + 0x4c, pos2);
						dir[0] = pos1[0] - pos2[0];
						dir[1] = 0.0f;
						dir[2] = pos1[2] - pos2[2];
						len = (float) sqrt((double) (dir[0] * dir[0] + dir[2] * dir[2]));
						fcn_0045b990(g_1043370, pos1, keys, (int*) flag, &scale);
						pos1[1] = scale + 80.0f;
						dir[0] = pos1[0] - pos2[0];
						dir[1] = pos1[1] - pos2[1];
						dir[2] = pos1[2] - pos2[2];
						if (len < 45.0f) {
							ret = 2;
							*(int*) (a0 + 0xc4) = 0;
							goto done;
						}
						keys[0] = *(int*) (a0 + 0xec);
						keys[1] = 0;
						scale = (float) (unsigned int) g_6b7fac - (float) keys[0];
						level = g_1043370;
						ret = 1;
						keys[2] = fcn_004c48f0();
						*(int*) (a0 + 0xec) = g_6b7fac;
						scale = ((float) (unsigned int) keys[2] * 0.25f + 0.5f) * scale;
						fcn_004518a0(dir);
						dir[0] = scale * dir[0];
						dir[1] = scale * dir[1];
						dir[2] = scale * dir[2];
						pos1[0] = dir[0] + pos2[0];
						pos1[1] = dir[1] + pos2[1];
						pos1[2] = dir[2] + pos2[2];
						fcn_0045b990(level, pos1, (int*) flag, keys, &len);
						if (pos1[1] < len + 80.0f) {
							pos1[1] = scale * 0.978 + pos1[1];
							pos1[0] = scale * dir[0] * 0.1f + pos2[0];
							pos1[2] = scale * dir[2] * 0.1f + pos2[2];
						}
						rec = *(int*) (a0 + 0xc8);
						*(int*) (a0 + 0xe0) = *(int*) (rec + 0x84);
						*(int*) (a0 + 0xe4) = *(int*) (rec + 0x88);
						*(int*) (a0 + 0xe8) = *(int*) (rec + 0x8c);
						*(float*) (a0 + 0xd0) = pos1[0];
						*(float*) (a0 + 0xd4) = pos1[1];
						*(float*) (a0 + 0xd8) = pos1[2];
						fcn_00438b40((char*) rec, pos1);
done:
						fcn_004432d0(saved, 1);
						return ret;
					}
				}
			}
		}
	}
	fcn_004432d0(saved, 1);
	return 0;
}
