// FUNCTION: GOLDTL 0x42a4a0
// SIZE: 45

extern int g_6b7f94;
int __cdecl fcn_0042b2c0(void);

int __cdecl fcn_0042a4a0(int* a1)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b2c0() != 0 || g_6b7f94 != 0) {
			*a1 = g_6b7f94;
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
