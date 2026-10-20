typedef struct Vtbl607eb8 {
	char pad0[0x30];
	void (__stdcall* m30)(void*);
} Vtbl607eb8;

typedef struct Obj607eb8 {
	char pad0[4];
	void* f4;
	int f8;
	unsigned char f0c;
	char pad0d[0x2f];
	void* f3c;
	void* f40;
} Obj607eb8;

int __fastcall fcn_005f0ed9(Obj607eb8*, int, void*, int);
int __fastcall fcn_0060743b(Obj607eb8*, int, int, int, int, int, int, int, void*);

/* ADDRESS: GOLDTL 0x00607eb8 */

int __stdcall fcn_00607eb8(Obj607eb8* a0, int a1, int a2, int a3, int a4, int a5)
{
	int hr;

	hr = (int) 0x8876086c;
	if ((a1 & 0xe0ffefff) == 0) {
		if ((a0->f8 & 0x400) == 0 && (a0->f8 & 0x40) == 0) {
			hr = fcn_005f0ed9(a0, 0, &a0->f40, 0);
			if (hr >= 0) {
				if ((a0->f0c & 0x20) != 0) {
					a1 |= 0x10000000;
				}
				hr = fcn_0060743b(a0, 0, a1, a2, a3, a4, a5, 0, a0->f4);
			}
		}
	}
	if (a0->f40 != 0) {
		(*(Vtbl607eb8**) a0->f3c)->m30(a0->f3c);
		a0->f40 = 0;
	}
	return hr;
}
