#include <string.h>

extern char g_7f4ca0[];

unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
int __cdecl fcn_00495400(int who, int idx, int arg, int* out1, int* out2);
int __cdecl fcn_004aa7c0(char* e, int* a, int* b);
float __cdecl fcn_00507e70(char* a, char* b, int c);
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x0049c880 */
int __cdecl fcn_0049c880(int a0, unsigned short* a1, int a2, int* a3, int* a4)
{
	int v7[6];
	int v8[6];
	float v9;
	int v11;
	int v5;
	int id;
	char* p;

	(void) a0;
	if (a2 != 0) {
		return 0;
	}
	p = (char*) a1;
	if (*(int*) (p + 0x170) != 0) {
		if (p[2] == 3) {
			if ((p[0x1e8] & 4) == 0) {
				return 0;
			}
			goto retry;
		}
		if (fcn_00502cd0(*(int*) (*(char**) (p + 0x170) + 0x5d), 2, 6, 0, 0x15) != 0) {
			goto retry;
		}
		v7[0] = 2;
		v7[1] = 0x15;
		v7[2] = 1;
		v7[5] = 0x3ee147ae;
		v8[0] = 4;
		v8[1] = *(int*) (*(char**) (p + 0x170) + 1);
		v8[2] = 1;
	}
	else {
		if (p[2] == 3) {
			if ((p[0x1e8] & 4) == 0) {
				return 0;
			}
			goto retry;
		}
		v7[0] = 5;
		v7[1] = 4;
		v7[2] = 1;
		v8[0] = 0;
		v8[1] = 0;
		v8[2] = 0;
	}
	v11 = 1;
	id = *a1;
	goto attempt;
retry:
	memset(v7, 0, sizeof(v7));
	memset(v8, 0, sizeof(v8));
	if (fcn_004aa7c0(p, v7, v8) == 0) {
		return 0;
	}
	v9 = fcn_00507e70(p, g_7f4ca0 + v8[4] * 0x21c, 4);
	if (gm_RandomFloat01() + v9 >= 1.0f) {
		memcpy(a3, v7, sizeof(v7));
		memcpy(a4, v8, sizeof(v8));
		return 0x28;
	}
	v7[0] = 4;
	v7[1] = 3;
	v7[2] = 1;
	v8[0] = 0;
	v8[1] = 0;
	v8[2] = 0;
	v11 = 0;
	id = *a1;
attempt:
	v5 = fcn_00495400(0x28, id, v11, v7, v8);
	if (v5 == 0) {
		return 0;
	}
	memcpy(a3, v7, sizeof(v7));
	memcpy(a4, v8, sizeof(v8));
	return v5;
}
