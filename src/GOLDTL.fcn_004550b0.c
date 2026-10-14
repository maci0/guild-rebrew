


extern int g_67a370;

void __cdecl fcn_004379a0(int, int, int, int, int);
char __cdecl fcn_00455000(char*, char*);

void __cdecl fcn_004550b0(int a1, int* a2)
{
	if (a2 == 0) {
		return;
	}
	if (a1 == 0) {
		return;
	}
	fcn_004379a0(g_67a370, a1, a2[0x44 / 4] | 0x280, (int) fcn_00455000, (int) a2);
}
