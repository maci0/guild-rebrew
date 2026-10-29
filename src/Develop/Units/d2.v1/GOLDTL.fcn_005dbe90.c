

extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern char g_6ac76c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
/* ADDRESS: GOLD 0x5cf970 */

void __cdecl fcn_005dbe90(char* text)
{
	int h;

	h = fcn_00470820(0, 0, g_6ac76c);
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	fcn_00519190("%s", text);
	fcn_00473a90(0, 0);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005dbe90, 0x677c7) != 0);
	fcn_00471e30(h);
}
