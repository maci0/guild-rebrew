extern int g_6b7d7c;



void __cdecl fcn_00423670(int*, int, int);
int __cdecl fcn_0042a850(int);

void __cdecl fcn_00423550(int* a1)
{
	if (g_6b7d7c != 0 && a1[0] != 0) {
		if (*(int*) (a1[1] + 0x38) == 0) {
			fcn_00423670(a1, 0, 0);
			return;
		}
		fcn_0042a850(a1[0]);
	}
}
