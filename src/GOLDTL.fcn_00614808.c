/* Reconstruction of GOLDTL 0x00614808.
 * Native ABI is thiscall: self in ecx, one stack argument, ret 4. MSVC 6 C
 * rejects __thiscall, so __fastcall plus a dead second parameter keeps self
 * in ecx and the callee-pops ret 4. Dispatch tables hold __stdcall methods. */

typedef struct Buf614808 {
	int x0;
	int x4;
	int flag;
	int xc;
	int x10;
	int x14;
	int x18;
	int x1c;
} Buf614808;

typedef struct Obj8 {
	void* vt;
} Obj8;

typedef struct VT8 {
	void* pad00[2];
	int (__stdcall* m08)(void*);
	void* pad0c[17];
	int (__stdcall* m50)(void*, int, int, int, int, int, void*, void*);
	void* pad54[4];
	int (__stdcall* m64)(void*, int, int, int, int, void*, void*);
	int (__stdcall* m68)(void*, int, int, int, void*, void*);
	void* pad6c[4];
	int (__stdcall* m7c)(void*, void*, void*);
	void* pad80[2];
	int (__stdcall* m88)(void*);
	void* pad8c[5];
	int (__stdcall* ma0)(void*, void*);
} VT8;

typedef struct Obj30 {
	void* vt;
} Obj30;

typedef struct VT30 {
	void* pad00[14];
	int (__stdcall* m38)(void*, void*, void*);
	int (__stdcall* m3c)(void*, void*, void*);
} VT30;

typedef struct Obj34 {
	void* vt;
} Obj34;

typedef struct VT34 {
	void* pad00[14];
	int (__stdcall* m38)(void*, void*, void*);
	int (__stdcall* m3c)(void*, int, void*, void*);
} VT34;

typedef struct Obj614808 {
	void* vt;
	void* f04;
	Obj8* f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	int f1c;
	Obj8* f20;
	Obj8* f24;
	int f28;
	int f2c;
	Obj30* f30;
	Obj34* f34;
	char pad38[0x460 - 0x38];
	int f460;
	int f464;
	int f468;
	int f46c;
	int f470;
	int f474;
} Obj614808;

/* The native body keeps an EBP frame under the locked profile. */
#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00614808 */
int __fastcall fcn_00614808(Obj614808* self, int unused, int a1)
{
	Buf614808 buf;
	Obj8* p;
	int r;

	(void) unused;
	p = 0;
	if (self->f460 == 1) {
		((VT34*) self->f34->vt)->m38(self->f34, 0, &buf);
	} else {
		if (self->f30 == 0) {
			r = ((VT8*) self->f08->vt)->m50(self->f08, self->f0c, self->f0c, self->f1c, 1, self->f10, 0, &self->f30);
			if (r < 0) {
				r = ((VT8*) self->f08->vt)->m50(self->f08, self->f0c, self->f0c, self->f1c, 0, self->f10, 0, &self->f30);
				if (r < 0)
					return r;
			}
		}
		((VT30*) self->f30->vt)->m38(self->f30, 0, &buf);
	}
	self->f46c = buf.flag & 1;
	if (self->f46c == 0) {
		if (self->f20 == 0) {
			r = ((VT8*) self->f08->vt)->m64(self->f08, self->f0c, self->f0c, self->f10, 0, 1, &self->f20);
			if (r < 0)
				return r;
		}
		p = self->f20;
	} else {
		if (self->f460 == 1)
			((VT34*) self->f34->vt)->m3c(self->f34, a1, 0, &p);
		else
			((VT30*) self->f30->vt)->m3c(self->f30, 0, &p);
	}
	if (self->f24 == 0 && self->f14 != 0) {
		r = ((VT8*) self->f08->vt)->m68(self->f08, self->f0c, self->f0c, self->f18, 0, &self->f24);
		if (r < 0)
			return r;
	}
	((VT8*) self->f08->vt)->m7c(self->f08, p, self->f24);
	((VT8*) self->f08->vt)->ma0(self->f08, &self->f474);
	if (self->f46c != 0)
		((VT8*) p->vt)->m08(p);
	r = ((VT8*) self->f08->vt)->m88(self->f08);
	if (r < 0)
		return r;
	self->f464 = a1;
	self->f468 = 1;
	return 0;
}
