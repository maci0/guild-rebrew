extern char* g_1015ea0;
extern int g_6a4768;
extern int g_77e8a0;
extern int g_772514;

int __cdecl fcn_005455b0(void);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00470820(int, int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_004727a0(int, int);

/* ADDRESS: GOLDTL 0x00545670 */
int __cdecl fcn_00545670(char* e, short a2, short a3, int a4, int a5)
{
	int a;
	int i;
	int v;

	if ((e[0x78] & 8) == 0) {
		*(int*) (e + 0x74) = 0;
		return 1;
	}
	for (i = 0, a = 0x77e8c4; a < 0x77e984; a += 0xc, i++) {
		if (*(int*) a == -1) {
			break;
		}
	}
	if (i >= 0x10) {
		i = fcn_005455b0();
	}
	if (i == -1) {
		*(int*) (e + 0x74) = 0;
		return 2;
	}
	if (i > g_6a4768) {
		g_6a4768 = i;
	}
	fcn_004727a0(g_77e8a0, 0);
	*(int*) (e + 0x74) = i * 0xc + 0x77e8c0;
	*(int*) ((char*) *(int*) (e + 0x74)) = (int) e;
	*(int*) ((char*) *(int*) (e + 0x74) + 4) = fcn_0046f740(i << 5, 0, a5, g_772514);
	v = *(int*) ((char*) *(int*) (e + 0x74) + 4);
	*(int*) (g_1015ea0 + v * 0x2f4 + 0x58) = 1;
	*(int*) ((char*) *(int*) (e + 0x74) + 8) = fcn_00470820(a2, a3, a4);
	fcn_00471d80(*(int*) ((char*) *(int*) (e + 0x74) + 8), 3);
	fcn_00471af0(*(int*) ((char*) *(int*) (e + 0x74) + 8), 0);
	if (*(int*) ((char*) *(int*) (e + 0x74) + 4) == -1) {
		__asm { int 3 }
	}
	if (*(int*) ((char*) *(int*) (e + 0x74) + 8) == -1) {
		__asm { int 3 }
	}
	return 0;
}
