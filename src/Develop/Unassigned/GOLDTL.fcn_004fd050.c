


extern int g_773d48;

void __cdecl fcn_004fcda0(int, int, int*);
void __cdecl fcn_00535960(void);

void __cdecl fcn_004fd050(void)
{
	int buf[4];
	int i;

	g_773d48 = 0;
	for (i = 0; i < 0x300; i++) {
		fcn_004fcda0(i, 1, buf);
		if (g_773d48 > 0x40) {
			fcn_00535960();
			g_773d48 = 0;
		}
	}
	g_773d48 = 0;
}
