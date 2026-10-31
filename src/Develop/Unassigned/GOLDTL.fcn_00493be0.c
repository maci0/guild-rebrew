#include <math.h>

extern float flt_1;
extern float flt_6628cc;

int __cdecl gm_LookupEntityRecordById(int a0);
int __cdecl fcn_005c6270(int a0, int a1);

/* ADDRESS: GOLDTL 0x00493be0 */
int __cdecl fcn_00493be0(void* a0)
{
	char* p;
	float f;
	float frac;
	int n;
	int v;
	int k;

	p = (char*) a0;
	n = (int) (*(float*) (p + 4) - flt_1);
	f = *(float*) (p + 4);
	frac = f - ceil(f);
	v = gm_LookupEntityRecordById(*(int*) (p + 0x18));
	if (frac >= flt_6628cc) {
		n++;
	}
	n = (n < 0) ? 0 : n;
	switch (n) {
	case 0:
	case 1:
	case 2:
	case 3:
		return 0;
	case 4:
	case 5:
		k = 1;
		break;
	case 6:
	case 7:
		k = 2;
		break;
	case 8:
	case 9:
		k = 3;
		break;
	case 10:
	case 11:
		k = 4;
		break;
	case 12:
	case 13:
		k = 5;
		break;
	case 14:
	case 15:
	case 16:
		k = 6;
		break;
	default:
		k = 7;
		break;
	}
	if (fcn_005c6270(v, 0x22e) != 0) {
		k--;
	}
	return k;
}
