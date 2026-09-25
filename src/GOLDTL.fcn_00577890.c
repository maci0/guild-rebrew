// FUNCTION: GOLDTL 0x577890
// SIZE: 165

int __cdecl fcn_00577940(int);
float __cdecl fcn_00507f10(char*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004f4f60(int, int, int, int, int);

int __cdecl fcn_00577890(char* a, char* b, int c)
{
	int k;
	float fa;
	float fb;
	int id;

	k = fcn_00577940(c);
	if (k >= 0) {
		fa = fcn_00507f10(a, 4);
		fb = fcn_00507f10(b, 4);
		if (gm_RandomFloat01() + (fa - fb * 0.5f) >= 1.0f) {
			if (*(char**) (b + 0x170) != 0) {
				id = *(int*) (*(char**) (b + 0x170) + 1);
			} else if (*(char**) (b + 0x16c) != 0) {
				id = *(int*) (*(char**) (b + 0x16c) + 1);
			} else {
				id = -1;
			}
			fcn_004f4f60(k, 1, *(int*) (b + 4), *(int*) (a + 4), id);
			return 1;
		}
	}
	return 0;
}
