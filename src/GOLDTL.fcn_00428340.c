#pragma intrinsic(strcpy)

extern int* g_14cb8f0;
extern int g_6b7eb0;

int __cdecl fcn_00427f00(int a0);
int __cdecl fcn_004262b0(int a0, char* a1);
void __cdecl fcn_00425bf0(int a0, int a1, char* a2);
void __cdecl fcn_00428720(int a0);
void __cdecl fcn_00427c40(int a0, int a1);
int __cdecl sprintf(char* a0, const char* a1, ...);
char* __cdecl strcpy(char* a0, const char* a1);

/* ADDRESS: GOLDTL 0x00428340 */
int __cdecl fcn_00428340(char* a0, int a1, ...)
{
	int obj;
	int i;
	int kind;
	int* argp;

	if (a0 == 0) {
		return 0;
	}
	if (fcn_00427f00((int) a0) == 0) {
		return 0;
	}
	obj = fcn_004262b0((int) a0, (char*) 0x679608);
	if (obj == 0) {
		fcn_00425bf0((int) a0, 0, (char*) 0x6795d0);
		return 0;
	}
	if (a1 != *(char*) (obj + 0x24)) {
		fcn_00425bf0((int) a0, 0, (char*) 0x679610);
		fcn_00428720((int) a0);
		return 0;
	}
	argp = &a1;
	for (i = 0; i < *(char*) (obj + 0x24); i++) {
		kind = *(int*) (obj + 0x28 + i * 4);
		if (kind == 6) {
			strcpy((char*) (0x14cb540 + i * 0x60), (char*) *(argp + 1));
			argp++;
		} else if (kind == 1) {
			*(int*) ((char*) *(int*) 0x6b7ea0 + i * 4) = *(argp + 1);
			argp++;
		} else if (kind == 2) {
			*(int*) ((char*) *(int*) 0x6b7ea0 + i * 4) = *(char*) (argp + 1);
			argp++;
		}
	}
	fcn_00427c40((int) a0, obj);
	*(int*) (a0 + 0x124) = *(int*) (a0 + 0x124) | 1;
	*(int*) (a0 + 0xc28) = (int) a0 + 0x128;
	sprintf((char*) &g_14cb8f0[g_6b7eb0 * 0x21 + 1], (char*) 0x6795c0, a0);
	g_14cb8f0[g_6b7eb0 * 0x21] = 0;
	g_6b7eb0 = g_6b7eb0 + 1;
	if (g_6b7eb0 > 0x1e) {
		g_6b7eb0 = 0;
	}
	return 1;
}
