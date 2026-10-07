// FUNCTION: GOLDTL 0x005e3e60

extern unsigned short g_7ea3c0[];

int __cdecl fcn_00475fd0(char*);
void __cdecl fcn_00476060(char*);

void __cdecl fcn_005e3e60(int x0, int y0, char* surf)
{
	int n;
	int x;
	int y;

	n = 0;
	if (fcn_00475fd0(surf) != 0) {
		for (y = 0; y < 120; y++) {
			for (x = 0; x < 160; x++) {
				(*(unsigned short**) (surf + 0x1c))[*(int*) (surf + 0x10) * (y + y0) + x + x0] =
				    g_7ea3c0[n];
				n++;
			}
		}
		fcn_00476060(surf);
	}
}
