


extern char g_68b2d8[];

unsigned short* __cdecl fcn_00508e40(int);
void __cdecl fcn_0041d9e0(char*);
void __cdecl fcn_00529160(int, int, int, int);

int __cdecl fcn_004cc4c0(char* x, char* out)
{
	unsigned short* e;

	e = fcn_00508e40(*(int*) (x + 0x10));
	if (e == 0)
		fcn_0041d9e0(g_68b2d8);
	if (*e != 0xffff)
		fcn_00529160(*(int*) ((char*) e + 0x16c), *(int*) (x + 0x14), *e, 0);
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
