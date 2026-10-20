extern float g_6628a8;
extern float flt_1;
extern float flt_6628cc;
extern float flt_6629d0;

char* __cdecl fcn_004ce610(void* obj);
char* __cdecl fcn_004ce680(void* obj);
float __cdecl fcn_004ce8b0(void* obj);
float __cdecl fcn_004ff040(void* obj);

/* ADDRESS: GOLDTL 0x004d3e90 */
float __cdecl fcn_004d3e90(void* a0, unsigned int a1)
{
	float r;
	int n;

	r = g_6628a8;
	switch (a1) {
	case 0:
		r = 1.0f;
		if (*(char*) ((char*) a0 + 0x1c4) != 0) {
			r = 0.5f;
		}
		n = *(int*) (fcn_004ce610(a0) + 0x58);
		if ((n == 1 || n == 2) && *(int*) (fcn_004ce680(a0) + 0x20) <= 0) {
			r = 0.2f;
		}
		return fcn_004ce8b0(a0) * r;
	case 1:
		if (*(char*) ((char*) a0 + 0x1c4) == 1) {
			r = 1.0f;
		} else if (*(char*) ((char*) a0 + 0x1c4) == 0) {
			r = 0.4f;
		} else {
			r = 0.5f;
		}
		n = *(int*) (fcn_004ce610(a0) + 0x58);
		if ((n == 1 || n == 2) && *(int*) (fcn_004ce680(a0) + 0x20) <= 0) {
			r = 1.0f;
		}
		return r / fcn_004ce8b0(a0);
	case 2:
		if (*(char*) ((char*) a0 + 0x1c4) != 2) {
			return flt_6628cc;
		}
		return flt_1;
	case 3:
		return flt_1;
	case 4:
	case 5:
		if (*(char*) ((char*) a0 + 0x1c4) != 2) {
			return flt_1 / fcn_004ff040(a0);
		}
		return flt_6629d0;
	}
	return r;
}
