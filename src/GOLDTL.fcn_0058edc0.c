// FUNCTION: GOLDTL 0x0058edc0
// SIZE: 171

extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_0058dfb0(int, char*, int);

int __cdecl fcn_0058edc0(int a1, char* s, int a3)
{
	int r;
	int i;

	r = 0;
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			for (i = 0; i < 8; i++) {
				if (g_67d370 == *(int*) (s + 0x28 + i * 0xc)) {
					*(int*) (s + 0x88) = i;
					fcn_00471af0(*(int*) s, 0);
					r = fcn_0058dfb0(a1, s, a3);
					fcn_00471af0(*(int*) s, 1);
					break;
				}
			}
			if (r != 0) {
				r = 1;
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_0058edc0, 0x677c7) != 0);
	return r;
}
