

typedef int (__stdcall* WND_IS_VISIBLE_FN)(int);
typedef void (__stdcall* WND_ENABLE_FN)(int, int);

int __stdcall main_ToggleSiblingWindowCallback(int a1, int a2)
{
	if (a1 != *(int*) 0x774940) {
		if ((*(WND_IS_VISIBLE_FN*) 0x662284)(a1) != 0) {
			(*(WND_ENABLE_FN*) 0x6622f0)(a1, a2);
		}
	}
	return 1;
}
