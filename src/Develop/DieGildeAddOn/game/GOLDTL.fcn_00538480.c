extern int g_100f1dc;
extern int g_774654;
extern int g_774960;



int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_005356b0(void*);
void __cdecl fcn_005438c0(void);

void __cdecl fcn_00538480(void)
{
	int h;
	int q;

	h = fcn_00470820(0, 0, "Runde beenden");
	q = 0;
	fcn_00471b60(h);
	do {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				q = 1;
			}
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_00538480, 0x67fff) != 0);
	fcn_00471e30(h);
	if (q != 0) {
		g_774960 = 1;
		fcn_005356b0((void*) fcn_005438c0);
	}
}
