

extern int g_772f10;
extern char* g_9b46c0[];
extern char g_68bda0[];

int __cdecl fcn_0064f170(char*, char*, int);

char __cdecl fcn_004d35b0(char* a1, char* a2)
{
	unsigned short* w;

	w = *(unsigned short**) (a2 + 0x16c);
	if (fcn_0064f170(a1, g_68bda0, 5) == 0 && *(int*) (*(char**) (a1 + 0x204) + 0xa) != *w) {
		g_9b46c0[g_772f10] = a1;
		g_772f10++;
	}
	return 1;
}
