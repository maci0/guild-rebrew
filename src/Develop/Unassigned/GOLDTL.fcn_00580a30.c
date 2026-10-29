


typedef char* (__cdecl* pagefn)(void);

extern int g_774a14;
extern int g_774a18;
extern char* g_774a10;
extern int g_6a81dc[5];
extern pagefn g_6a81f0[5];
extern int* g_665f08;
extern int g_6b7fac;

char* __cdecl fcn_00580d50(void);
char* __cdecl fcn_00584010(void);
void __cdecl fcn_00580c20(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471d80(int, int);

int __cdecl fcn_00580a30(void)
{
	char* p;
	int n;
	int i;

	if (g_774a14 != 0) {
		return -3;
	}
	n = 0;
	for (i = 0; i < 5; i++) {
		if (g_6a81dc[i] == 1) {
			n++;
		}
	}
	if (n == 0) {
		return -2;
	}
	g_774a10 = fcn_00580d50();
	if (g_774a10 == 0) {
		goto fail;
	}
	p = g_774a10;
	while (*(char**) (p + 0x70) != 0) {
		p = *(char**) (p + 0x70);
	}
	for (i = 0; i < 5; i++) {
		if (g_6a81dc[i] == 1) {
			*(char**) (p + 0x70) = g_6a81f0[i]();
			if (*(char**) (p + 0x70) == 0) {
				goto fail;
			}
			while (*(char**) (p + 0x70) != 0) {
				p = *(char**) (p + 0x70);
			}
		}
	}
	*(char**) (p + 0x70) = fcn_00584010();
	if (*(char**) (p + 0x70) == 0) {
fail:
		fcn_00580c20();
		return -1;
	}
	g_665f08[0] = 1;
	g_665f08[1] = 1;
	g_665f08[2] = (*(volatile int*)&g_6b7fac);
	g_665f08[3] = (*(volatile int*)&g_6b7fac);
	g_665f08[4] = 0;
	g_665f08[5] = 0;
	g_665f08[6] = (int) g_774a10;
	g_665f08[5] = 0;
	g_665f08[7] = 0;
	g_665f08[8] = -1;
	g_665f08[9] = fcn_00470820(0, 0, "tutorial\\inline_form");
	fcn_00471af0(g_665f08[9], 0);
	fcn_00471d80(g_665f08[9], 3);
	g_665f08[10] = 0;
	g_665f08[11] = 0;
	g_665f08[12] = 0;
	g_665f08[13] = fcn_00470820(0, 0, "tutorial\\aux_form");
	fcn_00471af0(g_665f08[13], 0);
	fcn_00471d80(g_665f08[13], 3);
	g_665f08[15] = 0;
	g_665f08[16] = 0;
	g_665f08[22] = 0;
	g_665f08[21] = 0;
	g_665f08[23] = 0;
	g_665f08[24] = -1;
	g_665f08[26] = -1;
	g_665f08[27] = -1;
	g_774a14 = 1;
	g_774a18 = 1;
	return 0;
}
