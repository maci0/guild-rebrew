

typedef struct Inner0442910 {
	char pad0[0x1e4];
	unsigned int count;
} Inner0442910;

typedef struct Slot0442910 {
	Inner0442910* inner;
	int** tex;
	char pad8[0x4a4 - 8];
} Slot0442910;
// SIZE 0x4a4

typedef struct Ov0442910 {
	char pad0[0x40c];
	Slot0442910 slots[3];
	char pad11f8[0x163c - 0x11f8];
	unsigned char count;
} Ov0442910;

typedef struct Obj0442910 {
	char pad0[0x1ec];
	Ov0442910* ov;
} Obj0442910;

Obj0442910* __cdecl fcn_00439750(int kind, int id);
void __cdecl fcn_00439c00(Obj0442910* parent, Obj0442910* o);
int __cdecl fcn_00449b60(int id);
void __cdecl fcn_0044c200(int a, int b);
void __cdecl fcn_00449f90(Obj0442910* o, int z, int id);
void __cdecl fcn_0045ce90(int* t);
void __cdecl fcn_00438b40(Obj0442910* o, int a);
void __cdecl fcn_00438cb0(Obj0442910* o, int a);
void __cdecl fcn_00439aa0(Obj0442910* o);
void __cdecl d3_DisposeObject(Obj0442910* o);

Obj0442910* __cdecl fcn_00442910(Obj0442910* parent, int a, int b, int id)
{
	Obj0442910* o;
	Ov0442910* ov;
	int** t;
	unsigned int n;
	unsigned int i;

	o = fcn_00439750(4, id);
	if (o == 0) {
		return 0;
	}
	if (parent != 0) {
		fcn_00439c00(parent, o);
	}
	if (fcn_00449b60(id) == 0) {
		fcn_0044c200(id, id);
	}
	fcn_00449f90(o, 0, id);
	ov = o->ov;
	if (ov != 0 && ov->slots[0].inner != 0) {
		for (i = 0; i < ov->count; i++) {
			if (ov->slots[i].inner != 0) {
				n = ov->slots[i].inner->count;
				t = ov->slots[i].tex;
				for (; n > 0; n--) {
					if (*t != 0) {
						fcn_0045ce90(*t);
					}
					t++;
				}
			}
			ov = o->ov;
		}
		fcn_00438b40(o, a);
		fcn_00438cb0(o, b);
		if (parent == 0) {
			fcn_00439aa0(o);
		}
		return o;
	}
	d3_DisposeObject(o);
	return 0;
}
