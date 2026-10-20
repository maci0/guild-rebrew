#pragma optimize("s", on)

typedef struct Loc614a6c {
	int f0;
	char pad4[4];
	int f8;
	char padc[0xc];
	int f18;
	int f1c;
} Loc614a6c;

typedef struct Vtbl614a6c {
	char pad0[4];
	void (__stdcall* release)(void*);
	char pad8[0x30];
	void (__stdcall* getinfo)(void*, int, Loc614a6c*);
} Vtbl614a6c;

typedef struct Obj614a6c {
	char pad0[0xc];
	int f0c;
	int f10;
	char pad14[0x24];
	void* f38;
	int f3c;
	char pad40[8];
	int f48;
	char pad4c[0x414];
	int f460;
} Obj614a6c;

int __fastcall fcn_00614789(Obj614a6c*);

/* ADDRESS: GOLDTL 0x00614a6c */
int __stdcall fcn_00614a6c(Obj614a6c* a0, void* a1)
{
	Loc614a6c info;
	int r;

	if (a1 == 0) {
		return (int) 0x8876086c;
	}
	if (a0->f460 != 0) {
		return (int) 0x80004005;
	}
	(*(Vtbl614a6c**) a1)->getinfo(a1, 0, &info);
	if (info.f0 == a0->f10 && info.f18 == a0->f0c && info.f1c == a0->f0c) {
		a0->f48 = info.f8 & 1;
		r = fcn_00614789(a0);
		if (r < 0) {
			return r;
		}
		a0->f38 = a1;
		(*(Vtbl614a6c**) a1)->release(a1);
		a0->f3c = 0;
		a0->f460 = 2;
		return 0;
	}
	return (int) 0x8876086c;
}
