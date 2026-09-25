extern int g_6b7fac;

void __cdecl fcn_00438ac0(char* p, int a);

// FUNCTION: GOLDTL 0x43ac80
// SIZE: 90
char __cdecl fcn_0043ac80(char* a, char on)
{
	if (on) {
		if (*(int*) (a + 0x218) == 5 && *a == 'r') {
			*(int*) (a + 0x218) = 6;
			*(int*) (a + 0x40) = g_6b7fac;
			fcn_00438ac0(a, 0);
			return 1;
		}
	} else if (*(int*) (a + 0x218) == 6) {
		*(int*) (a + 0x218) = 5;
		fcn_00438ac0(a, 0);
	}
	return 1;
}
