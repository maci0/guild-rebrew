extern int g_6b8010;
extern char* g_90e094;

// FUNCTION: GOLDTL 0x51eb20
// SIZE: 147

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00446f70(int, int);

int __cdecl fcn_0051eb20(int a)
{
	int save;
	int i;
	char* e;

	save = g_6b8010;
	fcn_004432d0(0, 1);
	for (i = 0; i < 0x100; i++) {
		if (g_90e094[i * 0xa9] != 0 && *(char**) (g_90e094 + i * 0xa9 + 0x61) != 0) {
			*(int*) (*(char**) (g_90e094 + i * 0xa9 + 0x61) + 0x204) =
			    *(int*) (g_90e094 + i * 0xa9 + 1);
		}
	}
	fcn_00446f70(0, a);
	for (i = 0; i < 0x100; i++) {
		e = g_90e094 + i * 0xa9;
		if (*e != 0 && *(char**) (e + 0x61) != 0) {
			*(char**) (*(char**) (e + 0x61) + 0x204) = e;
		}
	}
	fcn_004432d0(save, 1);
	return 1;
}
