extern int g_10069a0;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_100f1dc;
extern int g_6a3760;
extern int g_774954;
extern char g_6a3440;
extern int g_774654;

int __cdecl fcn_004b3c50(int);
char* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(char*);
void __cdecl d2_SetForm(char*, int);
void __cdecl fcn_004b5630(int, int);
void __cdecl fcn_00519190(int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(char*);
void __cdecl fcn_004b5530(int, int);
void __cdecl fcn_004b5a80(int);
void __cdecl fcn_004b5b20(int);
void __cdecl fcn_004b60e0(int);

/* ADDRESS: GOLDTL 0x004b60e0 */
void __cdecl fcn_004b60e0(int flags)
{
	unsigned short* tab;
	char* obj;
	int tag;
	int v;
	int r;

	r = 0;
	tab = (unsigned short*) (0x7f4ca0 + (unsigned int) g_774970 * 0x21c);
	tag = fcn_004b3c50(g_10069a0);
	obj = fcn_00470820(0, 0, (char*) 0x681130);
	fcn_00471b60(obj);
	d2_SetForm(obj, 0);
	v = (flags & 0xfffffff6) | 0x100;
	fcn_004b5630(tag, v);
	d2_SetForm(obj, 1);
	fcn_00519190(0x1b95, *tab);
	g_100f1dc = -1;
	for (;;) {
		if (g_6a3760 == -1) {
			if (g_774954 != 0) {
				r = 3;
			} else {
				r = (g_6a3440 != 5) + 1;
			}
			g_774654 = 1;
		}
		if (!fcn_005373e0((int) fcn_004b60e0, v | 0x80)) {
			break;
		}
	}
	fcn_00471e30(obj);
	if (r == 1) {
		fcn_004b5530(g_10069a0, v);
		return;
	}
	if (r == 2) {
		fcn_004b5a80(v);
		return;
	}
	if (r == 3) {
		fcn_004b5b20(v);
		return;
	}
}
