extern char g_6811b0[];
extern char g_6811b0[];



extern int* g_665f08;

void __cdecl d2_SetForm(int, int);
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
	d2_SetForm(*(int*) (p + 8), 1);
	fcn_00519190((void*) g_6811b0);
	d2_SetForm(*(int*) (*(int*) (*(int*) ((int) g_665f08 + 0x1c) + 0x74) + 8), 2);
	fcn_00519190((void*) g_6811b0);
	return 0;
}
