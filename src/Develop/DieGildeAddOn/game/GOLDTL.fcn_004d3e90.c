extern float g_6628a8;

char* __cdecl fcn_004ce610(void* obj);
char* __cdecl fcn_004ce680(void* obj);
float __cdecl fcn_004ce8b0(void* obj);
float __cdecl fcn_004ff040(void* obj);

/* ADDRESS: GOLDTL 0x004d3e90 */
float __cdecl fcn_004d3e90(void* obj, unsigned int mode)
{
	float r;
	int n;

	r = g_6628a8;
	switch (mode) {
	case 0:
		{
			float f;
			f = 1.0f;
			if (*(char*) ((char*) obj + 0x1c4) != 0) {
				f = 0.5f;
			}
			n = *(int*) (fcn_004ce610(obj) + 0x58);
			if ((n == 1 || n == 2) && *(int*) (fcn_004ce680(obj) + 0x20) <= 0) {
				f = 0.2f;
			}
			return fcn_004ce8b0(obj) * f;
		}
	case 1:
		{
			float f;
			if (*(char*) ((char*) obj + 0x1c4) == 1) {
				f = 1.0f;
			} else if (*(char*) ((char*) obj + 0x1c4) == 0) {
				f = 0.4f;
			} else {
				f = 0.5f;
			}
			n = *(int*) (fcn_004ce610(obj) + 0x58);
			if ((n == 1 || n == 2) && *(int*) (fcn_004ce680(obj) + 0x20) <= 0) {
				f = 1.0f;
			}
			return f / fcn_004ce8b0(obj);
		}
	case 2:
		if (*(char*) ((char*) obj + 0x1c4) != 2) {
			return 0.5f;
		}
		r = 1.0f; break;
	case 4:
	case 5:
		if (*(char*) ((char*) obj + 0x1c4) == 2) {
			return 0.2f;
		}
		return 1.0f / fcn_004ff040(obj);
	case 3:
		r = 1.0f; break;
	}
	return r;
}
