extern int g_633444;
extern char* g_889f74;

// FUNCTION: GOLD 0x00519b80
/* Twin of GOLDTL 0x51eb20; the back-pointer field sits at 0x200 in GOLD, 0x204 in GOLDTL. */

void __cdecl fcn_004478e0(int, int);
void __cdecl fcn_0044aa10(int, int);

int __cdecl fcn_00519b80(int a)
{
	int save;
	int i;
	char* e;

	save = g_633444;
	fcn_004478e0(0, 1);
	for (i = 0; i < 0x100; i++) {
		if (g_889f74[i * 0xa9] != 0 && *(char**) (g_889f74 + i * 0xa9 + 0x61) != 0) {
			*(int*) (*(char**) (g_889f74 + i * 0xa9 + 0x61) + 0x200) =
			    *(int*) (g_889f74 + i * 0xa9 + 1);
		}
	}
	fcn_0044aa10(0, a);
	for (i = 0; i < 0x100; i++) {
		e = g_889f74 + i * 0xa9;
		if (*e != 0 && *(char**) (e + 0x61) != 0) {
			*(char**) (*(char**) (e + 0x61) + 0x200) = e;
		}
	}
	fcn_004478e0(save, 1);
	return 1;
}
