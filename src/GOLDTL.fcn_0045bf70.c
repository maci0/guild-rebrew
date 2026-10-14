

typedef int (__stdcall* fcn_0045bf70_f)(void*);

void __cdecl fcn_0045bf70(char* p)
{
	void* q;

	if (p[0] == 0x2a) {
		q = *(void**) (p + 0x50);
		if (q != 0) {
			*(int*) 0x14ce728 = ((fcn_0045bf70_f) ((int*) *(int*) q)[2])(q);
			*(int*) (p + 0x50) = 0;
		}
		return;
	}
	q = *(void**) (p + 0x50);
	if (q != 0) {
		*(int*) 0x14ce728 = ((fcn_0045bf70_f) ((int*) *(int*) q)[2])(q);
		*(int*) (p + 0x50) = 0;
	}
}
