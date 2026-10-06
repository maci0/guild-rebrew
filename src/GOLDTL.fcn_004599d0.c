// FUNCTION: GOLDTL 0x4599d0

void __cdecl fcn_0045bfb0(int);
int __cdecl fcn_0045c5b0(int, int, int, int);
void __cdecl fcn_0045ce90(int);

void __cdecl fcn_004599d0(void* a1, int a2)
{
	int v;

	fcn_0045bfb0(*(int*) ((char*) a1 + 0x1c));
	v = fcn_0045c5b0(a2, *(int*) ((char*) a1 + 0x24), 0, 0);
	*(int*) ((char*) a1 + 0x1c) = v;
	if (v != 0) {
		fcn_0045ce90(v);
	}
}
