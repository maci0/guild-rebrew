// FUNCTION: GOLDTL 0x580960
// SIZE: 49

extern int* g_665f08;
extern int g_67d370;

int __cdecl fcn_00580960(void)
{
	int r;

	if (*(int*) 0x774a14 == 0) {
		return -4;
	}
	if (*(int*) 0x100f1dc != -1 && g_67d370 == g_665f08[19]) {
		r = 1;
	} else {
		r = 0;
	}
	return r;
}
