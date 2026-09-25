extern unsigned char* g_7e4260[32];

char* __cdecl fcn_004ce610(char*);
int __cdecl fcn_004ce270(char*, unsigned char*);
float __cdecl fcn_004cefb0(char*, int);
float __cdecl fcn_004ff040(unsigned char*);

// FUNCTION: GOLD 0x004d1f10
// SIZE: 241
// FUNCTION: GOLDTL 0x4d2f70
// SIZE: 241

unsigned char* __cdecl fcn_004d2f70(char* a1)
{
	float best;
	float d;
	unsigned char* e;
	unsigned char* result;
	int i;

	best = 1000000.0f;
	result = 0;
	if (*(int*) (fcn_004ce610(a1) + 0x58) != 2) {
		for (i = 0; i < 32; i++) {
			e = g_7e4260[i];
			if (e != 0 && fcn_004ce270(a1, e) != 0 && e[8] != 0) {
				d = fcn_004cefb0(a1, *(int*) (*(char**) (e + 0x184) + 0x34));
				if (d * fcn_004ff040(e) < best) {
					best = d;
					result = g_7e4260[i];
				}
			}
		}
	} else {
		for (i = 0; i < 32; i++) {
			e = g_7e4260[i];
			if (e != 0 && fcn_004ce270(a1, e) != 0 && e[8] != 0) {
				d = fcn_004cefb0(a1, *(int*) (*(char**) (e + 0x184) + 0x34));
				if (d * fcn_004ff040(e) < best) {
					best = d;
					result = g_7e4260[i];
				}
			}
		}
	}
	return result;
}
