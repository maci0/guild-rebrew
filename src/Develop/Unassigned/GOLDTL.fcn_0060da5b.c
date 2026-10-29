/* Native ABI is __thiscall with eight stack arguments (ret 0x20); the object is
   in ECX. C89 cannot declare __thiscall, so the object arrives as the first
   __fastcall register argument and the unused second register argument keeps
   the eight stack arguments in their native slots. Emits the two three-dword
   records selected by the query result, then recurses for the child index when
   the third argument is zero. */
typedef struct L60da5b {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	char flag;
	char pad19[3];
} L60da5b;

typedef struct S60da5b {
	char pad0[0x48];
	int f48;
	char pad4c[0x3c];
	int* f88;
	char pad8c[0x30];
	int* fbc;
	char padc0[0x38];
	int f98;
} S60da5b;

int __fastcall fcn_005f2483(L60da5b*, int, int, int, int, int);
int __fastcall fcn_005f934b(L60da5b*);
void __fastcall fcn_005fad9e(S60da5b*, int, int, int, int);
void __fastcall fcn_0060db4e(void*, int, int);
void __fastcall fcn_0060da5b(S60da5b*, int, int, int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0060da5b */
void __fastcall fcn_0060da5b(S60da5b* self, int unused, int a1, int a2, int a3,
	int a4, int a5, int a6, int a7, int a8)
{
	L60da5b loc;
	int ebx;
	int edx;

	fcn_005f2483(&loc, 0, a1, a2, (int)self + 0x48, 0);
	if (loc.f8 == -1)
		return;
	do {
		ebx = fcn_005f934b(&loc);
		if (loc.flag) {
			edx = loc.fc;
		}
		else {
			edx = (loc.fc + 1) % 3;
		}
		a2 = edx;
		fcn_005fad9e(self, 0, ebx, a2, a8);
		fcn_0060db4e((void*)self->f98, 0, self->fbc[a2 + ebx * 3]);
		edx = (edx + 2) % 3;
		a2 = edx;
		fcn_005fad9e(self, 0, ebx, a2, a8);
		fcn_0060db4e((void*)self->f98, 0, self->fbc[ebx * 3 + a2]);
		if (a3 == 0) {
			fcn_0060da5b(self, 0, ebx, self->f88[ebx * 3 + a2], 1, 0, 0, 0, 0, a8);
		}
	} while (loc.f8 != -1);
}
