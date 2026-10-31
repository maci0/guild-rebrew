extern int g_14cbca0;
extern int g_699364;
extern int cm_LastEntityId;
extern char g_7f4ca0[];

int __cdecl fcn_0064d3f8(void);
void __cdecl fcn_0042e4c0(int a0);
int __cdecl fcn_004c4dc0(void* a0, int a1);
int __cdecl fcn_00503fe0(int a0, int a1, int a2);
int __cdecl fcn_0050a7e0(int a0, int a1, int a2, unsigned short a3,
                        int a4, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x004c7790 */
int __cdecl fcn_004c7790(void* a0, char* a1)
{
	int v;
	int r;
	int arg;

	if (g_14cbca0 != -1) {
		g_699364 = *(int*) ((char*) a0 + 0x10);
	} else {
		*(int*) ((char*) a0 + 0x26) = fcn_0064d3f8();
	}
	fcn_0042e4c0(*(int*) ((char*) a0 + 0x26));
	v = *(int*) ((char*) a0 + 0x1f);
	if (v == -1) {
		arg = 0;
	} else {
		v = fcn_004c4dc0(a0, v);
		*(int*) ((char*) a0 + 0x1f) = v;
		arg = fcn_00503fe0(1, 1, v);
		if (arg == 0)
			return 1;
	}
	r = (int) (unsigned short) fcn_0050a7e0(
		*(unsigned char*) ((char*) a0 + 0x14),
		*(int*) ((char*) a0 + 0x15),
		*(int*) ((char*) a0 + 0x19),
		*(unsigned short*) ((char*) a0 + 0x1d),
		arg,
		*(unsigned char*) ((char*) a0 + 0x23),
		*(unsigned char*) ((char*) a0 + 0x24),
		*(unsigned char*) ((char*) a0 + 0x25));
	if (r == 0xffff)
		return 1;
	r = r * 540;
	cm_LastEntityId = *(int*) (g_7f4ca0 + r + 4);
	if (a1 != 0) {
		a1[0] = 1;
		a1[1] = 1;
		*(char**) (a1 + 6) = g_7f4ca0 + r;
	}
	return 0;
}
