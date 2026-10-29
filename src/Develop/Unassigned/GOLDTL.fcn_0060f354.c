#pragma optimize("y", off)

/* Resolve-shaped method: maps the six node-field identifiers of the entity at
   arg1 through the +0x88 word table, stores the mapped values at +0x38..+0x3e
   and forwards the first resolved connection to 0x60f49e. Native ABI is
   thiscall (object in ECX) with two stack arguments and callee cleanup. */

typedef struct Ent60f354 {
	unsigned short f00, f02, f04, f06;
	unsigned short f08, f0a, f0c, f0e;
	unsigned short f10, f12, f14, f16;
	unsigned short f18, f1a, f1c, f1e;
	char pad20[0x18];
	unsigned short f38, f3a, f3c, f3e;
} Ent60f354;

extern void __fastcall fcn_0060f49e(void* self, int ignored, int a1, int a2, int a3, int a4, Ent60f354* e, int a6, int a7, int a8);

/* ADDRESS: GOLDTL 0x0060f354 */
int __fastcall fcn_0060f354(void* self, int ignored, Ent60f354* e, int arg2)
{
	unsigned short* map;
	int w10;
	int w14;
	int v1;
	int v2;
	int v3;
	int v4;
	int idx;
	int val;

	map = *(unsigned short**) ((char*) self + 0x88);
	w10 = e->f10;
	if (w10 == 0xffff) {
		v1 = 0xffff;
	} else {
		v1 = map[w10 * 3 + e->f12];
	}
	e->f38 = (unsigned short) v1;
	w14 = e->f14;
	if (w14 == 0xffff) {
		v2 = 0xffff;
	} else {
		v2 = map[w14 * 3 + (int) (e->f16 + 1) % 3];
	}
	e->f3a = (unsigned short) v2;
	if (e->f08 != 0xffff) {
		v3 = e->f18;
		if (v3 == 0xffff) {
			v3 = 0xffff;
		} else {
			v3 = map[v3 * 3 + (int) (e->f1a + 1) % 3];
		}
		e->f3c = (unsigned short) v3;
		v4 = e->f1c;
		if (v4 == 0xffff) {
			v4 = 0xffff;
		} else {
			v4 = map[v4 * 3 + e->f1e];
		}
		e->f3e = (unsigned short) v4;
	}
	idx = e->f10;
	if (idx != 0xffff) {
		val = v1;
	} else {
		idx = w14;
		if (idx != 0xffff) {
			val = v2;
		} else {
			if (e->f08 == 0xffff) {
				return 0;
			}
			idx = e->f18;
			if (idx != 0xffff) {
				val = e->f3c;
			} else {
				idx = e->f1c;
				if (idx == 0xffff) {
					return 0;
				}
				val = e->f3e;
			}
		}
	}
	if (idx == 0xffff) {
		return 0;
	}
	fcn_0060f49e(self, 0, idx, val, 0, w14, e, e->f1c, e->f3e, arg2);
	return 0;
}
