#pragma optimize("s", on)

typedef struct Loc614bc5 {
	int f0;
	char pad4[4];
	int f8;
	char padc[0xc];
	int f18;
	int f1c;
} Loc614bc5;

typedef struct Vtbl614bc5 {
	char pad0[4];
	void (__stdcall* release)(void*);
	char pad8[0x30];
	void (__stdcall* getinfo)(void*, int, Loc614bc5*);
} Vtbl614bc5;

typedef struct Obj614bc5 {
	char pad0[0xc];
	int f0c;
	int f10;
	char pad14[0x1c];
	void* f30;
	void* f34;
	void* f38;
	void* f3c;
	char pad40[8];
	int f48;
	int f4c;
	char pad50[0x410];
	int f460;
} Obj614bc5;

int __fastcall fcn_00614789(Obj614bc5*);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00614bc5 */
int __stdcall fcn_00614bc5(Obj614bc5* a0, void* a1, void* a2)
{
	Loc614bc5 info;
	int r;

	if (a1 == 0 && a2 == 0) {
		return (int) 0x8876086c;
	}
	if (a0->f460 != 0) {
		return (int) 0x80004005;
	}
	if (a1 != 0) {
		(*(Vtbl614bc5**) a1)->getinfo(a1, 0, &info);
		if (info.f0 != a0->f10 || info.f18 != a0->f0c || info.f1c != a0->f0c) {
			return (int) 0x8876086c;
		}
		a0->f48 = info.f8 & 1;
	}
	if (a2 != 0) {
		(*(Vtbl614bc5**) a2)->getinfo(a2, 0, &info);
		if (info.f0 != a0->f10 || info.f18 != a0->f0c || info.f1c != a0->f0c) {
			return (int) 0x8876086c;
		}
		a0->f4c = info.f8 & 1;
	}
	r = fcn_00614789(a0);
	if (r < 0) {
		return r;
	}
	a0->f38 = a1;
	a0->f3c = a2;
	if (a1 != 0) {
		(*(Vtbl614bc5**) a1)->release(a1);
	}
	if (a0->f3c != 0) {
		(*(Vtbl614bc5**) a0->f3c)->release(a0->f3c);
	}
	a0->f460 = 4;
	return 0;
}
