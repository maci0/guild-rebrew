// FUNCTION: GOLD 0x00551590
// SIZE: 251
// FUNCTION: GOLDTL 0x559660
// SIZE: 251

// SIZE 0xc
struct slot {
	int id;
	int item;
	unsigned char f8;
	unsigned char f9;
	unsigned char fa;
	unsigned char fb;
};

// SIZE 0x188
struct obj {
	char pad0[4];
	int handle;
	char pad8[0x17c];
	int shown;
};

extern unsigned short g_7f4c04;

struct obj* __cdecl fcn_00508e40(int);
void __cdecl fcn_005015e0(int*, int, int, int);
int __cdecl fcn_00529670(struct obj*, int);
void __cdecl fcn_004c6a40(int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_00559660(struct slot* s)
{
	struct obj* o;
	int r;

	if (s->id != -1) {
		o = fcn_00508e40(s->id);
		if (o == 0) {
			goto clear;
		}
		fcn_005015e0(&r, 0, 0, s->item);
		if (r == 0) {
			if (o->shown != 0) {
				fcn_004c6a40(s->id);
				fcn_004c5420(o->handle, 0x1c8, 4, 0, 0x40000000);
			}
		clear:
			s->id = -1;
			s->item = -1;
			s->f8 = 0;
			s->f9 = 0;
			s->fa = 0;
			s->fb = 0;
			return 0;
		}
		if (fcn_00529670(o, r) == 0 && g_7f4c04 < 0x16) {
			return 2;
		}
		if (o->shown != 0) {
			fcn_004c5c80(o->handle);
			fcn_004c6a40(s->id);
		}
		s->id = -1;
		s->item = -1;
		s->f8 = 0;
		s->f9 = 0;
		s->fa = 0;
		s->fb = 0;
		fcn_004c5420(o->handle, 0x1c8, 4, 0, 0x40000000);
	}
	return 0;
}
