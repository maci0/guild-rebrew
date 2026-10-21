/* Teardown-shaped routine: releases three device-child interfaces through
   vtable slot 0xe0, then releases and clears six plain interfaces through
   slot 8, then walks the two internal interface arrays. Native ABI is
   stdcall with one stack argument (ret 4). */

typedef struct Vt614c9a {
	char pad0[8];
	void (__stdcall* release8)(void*);
	char padc[0xd4];
	void (__stdcall* releasee0)(void*, void*);
} Vt614c9a;

typedef struct Obj614c9a {
	char pad0[8];
	void* device;
	char padc[0x14];
	void* f20;
	void* f24;
	void* f28;
	void* f2c;
	void* f30;
	void* f34;
	void* f38;
	void* f3c;
	void* f40;
	void* f44;
	char pad48[8];
	void* f50;
	void* f54;
	char pad58[0x418];
	void* f470;
	char pad474[0x18];
	void* f48c;
	void* f490;
} Obj614c9a;

/* ADDRESS: GOLDTL 0x00614c9a */
void __stdcall fcn_00614c9a(Obj614c9a* o)
{
	Vt614c9a* vt;
	void* dev;
	void* p;
	void** q;
	int i;
	int j;

	dev = o->device;
	if (dev != 0) {
		if (o->f470 != 0) {
			vt = (Vt614c9a*) *(int*) dev;
			vt->releasee0(dev, o->f470);
			o->f470 = 0;
		}
		if (o->f48c != 0) {
			vt = (Vt614c9a*) *(int*) dev;
			vt->releasee0(dev, o->f48c);
			o->f48c = 0;
		}
		if (o->f490 != 0) {
			vt = (Vt614c9a*) *(int*) dev;
			vt->releasee0(dev, o->f490);
			o->f490 = 0;
		}
	}
	if (o->f20 != 0) {
		p = o->f20;
		((Vt614c9a*) *(int*) p)->release8(p);
		o->f20 = 0;
	}
	if (o->f24 != 0) {
		p = o->f24;
		((Vt614c9a*) *(int*) p)->release8(p);
		o->f24 = 0;
	}
	if (o->f28 != 0) {
		p = o->f28;
		((Vt614c9a*) *(int*) p)->release8(p);
		o->f28 = 0;
	}
	if (o->f2c != 0) {
		p = o->f2c;
		((Vt614c9a*) *(int*) p)->release8(p);
		o->f2c = 0;
	}
	if (o->f34 != 0) {
		p = o->f34;
		((Vt614c9a*) *(int*) p)->release8(p);
		o->f34 = 0;
	}
	if (o->f30 != 0) {
		p = o->f30;
		((Vt614c9a*) *(int*) p)->release8(p);
		o->f30 = 0;
	}
	q = &o->f40;
	for (i = 2; i != 0; i--) {
		p = q[-2];
		if (p != 0) {
			((Vt614c9a*) *(int*) p)->release8(p);
			q[-2] = 0;
		}
		p = q[0];
		if (p != 0) {
			((Vt614c9a*) *(int*) p)->release8(p);
			q[0] = 0;
		}
		q++;
	}
	q = &o->f54;
	for (j = 5; j != 0; j--) {
		for (i = 2; i != 0; i--) {
			p = q[-1];
			if (p != 0) {
				((Vt614c9a*) *(int*) p)->release8(p);
				q[-1] = 0;
			}
			p = q[0];
			if (p != 0) {
				((Vt614c9a*) *(int*) p)->release8(p);
				q[0] = 0;
			}
			q += 0x1a;
		}
	}
}
