// FUNCTION: GOLD 0x005783a0
// FUNCTION: GOLDTL 0x580960

extern int* g_665f08;
extern int g_67d370;
extern int g_774a14;
extern int g_100f1dc;

int __cdecl fcn_00580960(void)
{
	int r;

	if (*(int*) ((char*)&g_774a14) == 0) {
		return -4;
	}
	if (*(int*) ((char*)&g_100f1dc) != -1 && g_67d370 == g_665f08[19]) {
		r = 1;
	} else {
		r = 0;
	}
	return r;
}
