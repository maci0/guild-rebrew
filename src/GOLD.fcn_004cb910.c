
// fcn_004cb910 — r=fcn_004f27d0(a+0x10); if(b){ b[1]=0; b[0]=(r==0)+1; b[6]=0; } return 0.

int __cdecl fcn_004f27d0(void*);

int __cdecl fcn_004cb910(char* a, char* b)
{
	int r;
	r = fcn_004f27d0(a + 0x10);
	if (b != 0) {
		b[1] = 0;
		b[0] = (char) ((r == 0) + 1);
		*(int*) (b + 6) = 0;
	}
	return 0;
}
