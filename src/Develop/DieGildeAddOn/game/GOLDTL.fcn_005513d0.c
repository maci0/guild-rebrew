#include <string.h>

extern char g_7f4ca0[];
extern int g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

char* __cdecl fcn_00508e40(int);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004c5980(void*);
int __cdecl fcn_004c4fc0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x005513d0 */
void __cdecl fcn_005513d0(char* a0)
{
	char msg[0x114];
	char* entry;
	char* rec;
	int* ids;
	int v20;
	int count;
	int i;
	int state;
	float f;
	float r;
	float t;

	v20 = -1;
	entry = g_7f4ca0 + *(unsigned short*) (a0 + 8) * 0x21c;
	rec = fcn_00508e40(*(int*) (entry + 0x5c));
	if (rec == 0 || rec[8] == 0 || entry[8] == 0)
		goto tail;
	state = *(int*) (a0 + 0x70);
	if (state != 0) {
		if (state != 1)
			return;
		if (*(float*) (a0 + 0xac) < 3.0) {
			*(int*) (a0 + 0x52) += 1;
			*(float*) (a0 + 0xac) = *(float*) (a0 + 0xac) + 1.0;
			return;
		}
		if (entry[2] == 6) {
			memset(msg, 0, sizeof(msg));
			*(int*) (msg + 0xc) = *(int*) (entry + 4);
			*(unsigned short*) (msg + 0x1c) = g_7f4c04;
			*(int*) (msg + 0x18) = g_7f4c00;
			*(int*) (msg + 0x20) = g_7f4c08;
			*(short*) (msg + 0x24) = g_7f4c0c;
			msg[8] = 7;
			*(int*) (msg + 0x14) = -1;
			*(int*) (msg + 0x34) = *(int*) (entry + 4);
			*(int*) (msg + 0x38) = *(int*) (rec + 4);
			msg[0x26] = 0x20;
			*(int*) (msg + 0x30) = 2;
			fcn_00500bb0(msg + 0x18, 0, 0x1e, 0);
			fcn_004c5980(msg);
		}
		*(float*) (a0 + 0xac) = 0;
		if (*(int*) (entry + 0x170) != 0)
			v20 = *(int*) (*(int*) (entry + 0x170) + 1);
		if (entry[9] != 0) {
			fcn_004c4fc0(8, *(int*) (rec + 4), *(int*) (entry + 4), 0, v20, 0, 0, 2);
		} else {
			fcn_004c4fc0(8, *(int*) (entry + 4), *(int*) (rec + 4), 0, v20, 0, 0, 2);
		}
		*(int*) (a0 + 0x70) = 0;
		*(int*) (a0 + 0x52) += (gm_RandomMod(8) & 0xffff) + 1;
		return;
	}
	count = 0;
	ids = (int*) (entry + 0x68);
	for (i = 0; i < 5; i++) {
		if (ids[i] != -1 && fcn_00508e40(ids[i]) != 0)
			count++;
	}
	if (count != 5) {
		f = (5.0f - (float) count) * 0.2f;
		f = f * f;
		r = gm_RandomFloat01();
		t = (1.0f - f) + r;
		if (t <= f * *(float*) (a0 + 0xac)) {
			*(int*) (a0 + 0x70) = 1;
			*(int*) (a0 + 0x52) += 1;
			*(float*) (a0 + 0xac) = 0;
			return;
		}
		*(float*) (a0 + 0xac) = f * 0.1f + *(float*) (a0 + 0xac);
		return;
	}
tail:
	fcn_00546190(a0);
}
