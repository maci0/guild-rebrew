// GLOBAL: GOLDTL 0x6811b0
extern char g_6811b0[];
// GLOBAL: GOLD 0x602548
extern char g_6811b0[];
// FUNCTION: GOLD 0x00577b10
// FUNCTION: GOLDTL 0x5800e0

extern int* g_665f08;

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(void*);

int __cdecl fcn_005800e0(void)
{
	char* p;

	p = *(char**) ((int) g_665f08 + 0x1c);
	if (p == 0) {
		return -4;
	}
	p = *(char**) (p + 0x74);
	if (p == 0) {
		return -4;
	}
	fcn_004727a0(*(int*) (p + 8), 1);
	fcn_00519190((void*) g_6811b0);
	fcn_004727a0(*(int*) (*(int*) (*(int*) ((int) g_665f08 + 0x1c) + 0x74) + 8), 2);
	fcn_00519190((void*) g_6811b0);
	return 0;
}
