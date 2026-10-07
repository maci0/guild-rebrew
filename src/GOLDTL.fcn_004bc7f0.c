// FUNCTION: GOLD 0x004bc2e0
// FUNCTION: GOLDTL 0x4bc7f0

extern char g_68149c[];

char* __cdecl fcn_00503fe0(int, ...);
char* __cdecl fcn_00503e80(void);
int __cdecl fcn_00505370(char*);
int __cdecl fcn_00505340(char*);
unsigned short __cdecl fcn_0042e410(unsigned short);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00455350(char*, char*, float*);

int __cdecl fcn_004bc7f0(float* out)
{
	char* list[0x100];
	unsigned short n;
	char* e;
	char* r;

	n = 0;
	for (e = fcn_00503fe0(1, 6); e != 0; e = fcn_00503e80()) {
		if (fcn_00505370(e) == 0 && fcn_00505340(e) == 0 && *(int*) (e + 0x61) != 0)
			list[n++] = e;
	}
	e = list[fcn_0042e410(n)];
	r = fcn_00445600(*(int*) (e + 0x61), 0x300, 0, g_68149c);
	if (r != 0) {
		fcn_00455350(r, r + 0x4c, out);
	} else {
		e = *(char**) (e + 0x61);
		fcn_00455350(e, e + 0x4c, out);
	}
	return 1;
}
