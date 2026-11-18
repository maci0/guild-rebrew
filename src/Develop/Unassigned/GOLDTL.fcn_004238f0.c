extern int g_6b7d7c;
extern int g_6b7d7c;



void __cdecl fcn_0042aa20(int, int);

void __cdecl fcn_004238f0(int* p, int value)
{
	if (*(int*) ((char*)&g_6b7d7c) == 0) {
		return;
	}
	if (p == 0) {
		return;
	}
	*(int*) ((char*) p + 0xc) = value;
	fcn_0042aa20(*(int*) p, value);
}
