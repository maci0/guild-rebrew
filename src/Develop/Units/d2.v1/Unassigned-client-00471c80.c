extern char g_1015eac[];
extern char g_67d368[];
extern int g_1040494;
extern char g_1040490[];
void __cdecl d2_PositionControl(int, int, int);
#include "Develop/client_types.h"
typedef D2_FORM_RECORD Obj;

extern D2_FORM_RECORD d2_Forms[];

void __cdecl d2_CenterWindow(int win, unsigned char flags);
#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_772534;
extern Win_1015f40 d2_Windows[0x60];
typedef struct Slot {
	int id;
	int used;
	int value;
	char* data;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x38 - 0x24];
	int text;
	char pad3c[0x48 - 0x3c];
	int hidden;
	char pad4c[0x58 - 0x4c];
	int dirty;
	char pad5c[0x88 - 0x5c];
	int result;
	char* buf;
	char pad90[0x2f4 - 0x90];
} Slot;

int __cdecl d2_GetControlValue(int id);

/* ADDRESS: GOLDTL 0x00471c80 */
/* ADDRESS: GOLDDE 0x00465180 */
void __cdecl d2_CenterWindow(int idx, unsigned char flags)
{
	int* p;
	float value;
	float bound;
	int t;

	p = (int*) ((int) &d2_Windows + idx * 0x3cc);
	if (flags & 1) {
		t = p[3] / 2;
		value = (float) (p[1] + t)
			- (float) *(int*) &g_1015eac / *(float*) &g_67d368
			+ (float) *(int*) &g_1015eac - (float) t;
	} else {
		value = (float) p[1];
	}
	if (flags & 2) {
		bound = (float) (p[2] + p[4] / 2) * *(float*) &g_67d368 - (float) (p[4] / 2);
	} else {
		bound = (float) p[2];
	}
	t = *(int*) &g_1040494 - p[3];
	if ((float) t < value) {
		value = (float) t;
	}
	t = *(int*) &g_1040490 - p[4];
	if ((float) t < bound) {
		bound = (float) t;
	}
	d2_PositionControl((int) value, (int) bound, *(int*) ((char*) p + 0x27c));
}

/* ADDRESS: GOLDTL 0x00471d80 */
/* ADDRESS: GOLDDE 0x00465280 */
void __cdecl d2_CenterForm(int k, int flags)
{
	d2_CenterWindow(d2_Forms[k].wins[0], flags);
}

/* ADDRESS: GOLDTL 0x00471ee0 */
void __cdecl d2_SetControlValue(int i, int v)
{
	*(int*) (&((D2_CONTROL_TL*)d2_Controls)[(*(int*) (((char*)d2_Forms) + g_772534 * 0x2bc + 0x194) + i)].value_038) = v;
}

/* ADDRESS: GOLDTL 0x00471f20 */
char* __cdecl d2_GetFormControl(int j, int k)
{
	char* m;

	m = ((char*)d2_Windows) + ((int*) (((char*)d2_Forms) + g_772534 * 0x2bc + 4))[k] * 0x3cc;
	if (j > *(int*) (m + 0x2c)) {
		return 0;
	}
	return (char*)&((D2_CONTROL_TL*)d2_Controls)[(*(int**) (m + 0x28))[j]];
}

/* ADDRESS: GOLDTL 0x00471ff0 */
int __cdecl d2_GetFormControlValue(int j, int k)
{
	char* m;

	m = ((char*)d2_Windows) + ((int*) (((char*)d2_Forms) + g_772534 * 0x2bc + 4))[k] * 0x3cc;
	if (j > *(int*) (m + 0x2c)) {
		return 0;
	}
	return d2_GetControlValue((*(int**) (m + 0x28))[j]);
}
