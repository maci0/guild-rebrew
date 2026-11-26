

void __cdecl gm_AddTime(int, int, int, int);

void __cdecl gm_AdvanceGameTime(int a1, int a2, int a3, int a4, int a5)
{
	gm_AddTime(a1, a3, a4, a5);
}
