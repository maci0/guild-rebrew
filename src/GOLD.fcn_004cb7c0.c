// FUNCTION: GOLD 0x004cb7c0
// fcn_004cb7c0 — r=fcn_004f9020(a+0x10); if(b){ b[0]=1; b[1]=0; *(int*)(b+6)=0; } return 0.

int __cdecl fcn_004f9020(void*);

int __cdecl fcn_004cb7c0(char* a, char* b)
{
	int r;
	r = fcn_004f9020(a + 0x10);
	if (b != 0) {
		b[0] = 1;
		b[1] = 0;
		*(int*) (b + 6) = 0;
	}
	return 0;
}
