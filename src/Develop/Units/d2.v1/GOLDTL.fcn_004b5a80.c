

extern char g_681130[];
extern char g_68112c[];
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_004b5a80(int flags)
{
	int h;

	h = fcn_00470820(0, 0, g_681130);
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	io_AppendText(0x1b99);
	io_AppendText((int) g_68112c);
	d2_SetForm(h, 2);
	io_AppendText(0x7d);
	flags |= 0x80;
	while (fcn_005373e0(fcn_004b5a80, flags) != 0) {
		if (g_14ce8e0 != 0)
			g_774654 = 1;
		else if (g_100f1dc == 2)
			g_774654 = 1;
	}
	fcn_00471e30(h);
}
