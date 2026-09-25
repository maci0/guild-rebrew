extern char g_773d75;
// FUNCTION: GOLDTL 0x0050f910
// SIZE: 54

char* __cdecl fcn_0050e4a0(int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl fcn_004c51a0(int, int, char, int);

void __cdecl fcn_0050f910(int a)
{
	char* e;
	char* r;

	e = fcn_0050e4a0(1);
	r = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x115);
	fcn_004c51a0(-1, *(int*) (r + 2), g_773d75, a);
}
