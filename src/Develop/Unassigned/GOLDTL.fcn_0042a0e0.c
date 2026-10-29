typedef void (__stdcall* g_6623b0_f)(int, int);
extern g_6623b0_f g_6623b0;
extern g_6623b0_f g_6623b0;



int __cdecl fcn_0042b120(int);

int __cdecl fcn_0042a0e0(int* a1, int a2)
{
	int r = 0;

	if (fcn_0042b120((int) a1) >= 0 && a2 >= 0 && a2 <= 0x7f) {
		g_6623b0(*a1, a2);
	} else {
		r = -1;
	}
	return r;
}
