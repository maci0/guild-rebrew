// FUNCTION: GOLDTL 0x00426340
// SIZE: 112

extern char* g_6b7e98;

int __cdecl fcn_00426340(void)
{
	while (*(char**) (g_6b7e98 + 0x118) < (char*) (*(int*) (g_6b7e98 + 0x120) + *(int*) (g_6b7e98 + 0x11c))) {
		if (**(char**) (g_6b7e98 + 0x118) == ';') {
			(*(char**) (g_6b7e98 + 0x118))++;
			return 1;
		}
		(*(char**) (g_6b7e98 + 0x118))++;
	}
	return 0;
}
