typedef struct Loc6149fc {
	int f0;
	char pad4[0x14];
	int f18;
	int f1c;
} Loc6149fc;

typedef struct Vtbl6149fc {
	char pad0[4];
	void (__stdcall* release)(void*);
	char pad8[0x30];
	void (__stdcall* getinfo)(void*, int, Loc6149fc*);
} Vtbl6149fc;

typedef struct Obj6149fc {
	char pad0[0xc];
	int f0c;
	int f10;
	char pad14[0x20];
	void* f34;
	char pad38[0x428];
	int f460;
} Obj6149fc;

int __fastcall fcn_00614789(Obj6149fc*);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x006149fc */

int __stdcall fcn_006149fc(Obj6149fc* a0, void** a1)
{
	Loc6149fc info;
	int r;

	if (a1 == 0) {
		return (int) 0x8876086c;
	}
	if (a0->f460 != 0) {
		return (int) 0x8876086c;
	}
	(*(Vtbl6149fc**) a1)->getinfo(a1, 0, &info);
	if (info.f0 != a0->f10) {
		return (int) 0x8876086c;
	}
	if (info.f18 != a0->f0c || info.f1c != a0->f0c) {
		return (int) 0x8876086c;
	}
	r = fcn_00614789(a0);
	if (r < 0) {
		return r;
	}
	a0->f34 = a1;
	(*(Vtbl6149fc**) a1)->release(a1);
	a0->f460 = 1;
	return 0;
}
