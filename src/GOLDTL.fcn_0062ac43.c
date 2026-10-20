/* Destructor-shaped body: releases two COM-style members through vtable slot
   0xe0, then releases eight interface-pointer pairs, two two-argument frees,
   two one-argument frees, and finally unlinks the object from the global list
   at 0x775f60 (next link at +0xac). Native ABI is fastcall with the object in
   ECX and no stack cleanup. */
typedef struct Vtbl62ac43 {
	char pad0[8];
	void (__stdcall* release)(void*);
	char padc[0xd4];
	void (__stdcall* iface)(void*, void*);
} Vtbl62ac43;

typedef struct Obj62ac43 {
	char pad0[4];
	void* field04;
	char pad8[4];
	void* field0c;
	char pad10[0x54];
	int field64;
	int field68;
	int field6c;
	char pad70[0x28];
	int field98;
	int field9c;
	char pada0[8];
	int fielda8;
	int next_ac;
} Obj62ac43;

/* ADDRESS: GOLDTL 0x0062ac43 */
void __fastcall fcn_0062ac43(Obj62ac43* self)
{
	void* o;
	int* p;
	int i;

	if (self->field64) {
		o = self->field04;
		((Vtbl62ac43*)*(int*)o)->iface(o, (void*)self->field64);
	}
	if (self->field68) {
		o = self->field04;
		((Vtbl62ac43*)*(int*)o)->iface(o, (void*)self->field68);
	}
	p = (int*)((char*)self + 0x10);
	for (i = 8; i != 0; i--) {
		o = (void*)p[8];
		if (o) {
			((Vtbl62ac43*)*(int*)o)->release(o);
			p[8] = 0;
		}
		o = (void*)*p;
		if (o) {
			((Vtbl62ac43*)*(int*)o)->release(o);
			*p = 0;
		}
		p++;
	}
	if (self->field0c) {
		o = self->field0c;
		((Vtbl62ac43*)*(int*)o)->release(o);
		self->field0c = 0;
	}
	if (self->field04) {
		o = self->field04;
		((Vtbl62ac43*)*(int*)o)->release(o);
		self->field04 = 0;
	}
	if (self->field6c && self->fielda8)
		(*(void (__stdcall**)(void*, void*))0x66204c)((void*)self->field6c, (void*)self->fielda8);
	if (self->field6c && self->field9c)
		(*(void (__stdcall**)(void*, void*))0x66204c)((void*)self->field6c, (void*)self->field9c);
	if (self->field98)
		(*(void (__stdcall**)(void*))0x662040)((void*)self->field98);
	if (self->field6c)
		(*(void (__stdcall**)(void*))0x662054)((void*)self->field6c);
	if (*(int*)0x775f60 != 0) {
		p = (int*)0x775f60;
		while (*p != (int)self) {
			if (*(int*)(*p + 0xac) == 0)
				break;
			p = (int*)(*p + 0xac);
		}
		if (*p)
			*p = *(int*)(*p + 0xac);
	}
}
