


extern char g_69059c[];
extern char g_690584[];
extern char g_690568[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl fcn_00471b60(int h);
void __cdecl d2_SetForm(int h, int b);
void __cdecl fcn_00519190(char* x);
int __cdecl fcn_005373e0(void* fn, int y);
void __cdecl fcn_00471e30(int h);

void __cdecl fcn_004fa5f0(char* x, int mode, int y)
{
	int h;

	if (mode == 0) {
		h = fcn_00470820(0, 0, g_69059c);
	} else if (mode == 1) {
		h = fcn_00470820(0, 0, g_690584);
	} else {
		h = fcn_00470820(0, 0, g_690568);
	}
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	fcn_00519190(x);
	g_100f1dc = -1;
	while (fcn_005373e0((void*) fcn_004fa5f0, y)) {
		if (g_14ce8e0) {
			g_774654 = 1;
		}
	}
	fcn_00471e30(h);
}
