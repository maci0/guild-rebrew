


extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern char g_6ac9b4[];
extern char g_6ac9a4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005cdd90(int k)
{
	int h;

	h = fcn_00470820(0, 0, g_6ac9b4);
	fcn_00471b60(h);
	d2_SetForm(h, 2);
	io_AppendText(g_6ac9a4, k + 0x253);
	d2_SetForm(h, 1);
	io_AppendText((char*) (k * 2 + 0x134b));
	io_AppendText((char*) (k * 2 + 0x134c));
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005cdd90, 0x657c7) != 0);
	fcn_00471e30(h);
}
