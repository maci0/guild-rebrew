#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Stamp_54f0c0;
#pragma pack(pop)

// SIZE 0x8
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
} Entity_54f0c0;

// SIZE 0xb8
typedef struct {
	char pad0[0x52];
	Stamp_54f0c0 stamp;
	char pad60[0x10];
	int state;
	char pad74[4];
	unsigned char flags;
	char pad79[0xb];
	int event;
	char pad88[0x24];
	int actor;
	int target;
	int mode;
} Order_54f0c0;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

Entity_54f0c0* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_0051af00(char*, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_00500bb0(Stamp_54f0c0*, int, int, int);
int __cdecl fcn_004c5620(int, Order_54f0c0*);
void __cdecl fcn_00546190(Order_54f0c0*);


/* ADDRESS: GOLDTL 0x0054f0c0 */
void __cdecl fcn_0054f0c0(Order_54f0c0* o)
{
	char buf[0x100];
	Entity_54f0c0* a;
	Entity_54f0c0* b;

	switch (o->state) {
	case -2:
	case -1:
		if (o->flags & 2) {
			a = fcn_00508e40(o->actor);
			if (a != 0) {
				fcn_004c5420(a->id, 0x1c8, 4, 0, 0x100);
			}
			b = fcn_00508e40(o->target);
			if (b != 0) {
				fcn_004c5420(b->id, 0x1c8, 4, 0, 0x200);
			}
		}
		fcn_00546190(o);
		break;
	case 2:
		if (o->flags & 2) {
			a = fcn_00508e40(o->actor);
			if (a != 0) {
				fcn_004c5420(a->id, 0x1c8, 4, 0, 0x100);
			}
			b = fcn_00508e40(o->target);
			if (b != 0) {
				fcn_004c5420(b->id, 0x1c8, 4, 0, 0x200);
			}
			if (a != 0 && b != 0) {
				if (o->mode == 1) {
					if (b->type == 6 || b->type == 7) {
						fcn_0051af00(buf, 0x1e19, a->slot);
						fcn_00545d40(b->id, -1, buf, 0, 0x5fb, 0);
					}
				} else if (o->mode == 2) {
					if (b->type == 6 || b->type == 7) {
						fcn_0051af00(buf, 0x1e20, a->slot);
						fcn_00545d40(b->id, -1, buf, 0, 0x5fb, 0);
					}
				} else {
					fcn_004c54c0(a->id, b->id, -0x68, 1);
					if (b->type == 6 || b->type == 7) {
						fcn_0051af00(buf, 0x1d5d, a->slot);
						fcn_00545d40(b->id, b->id, buf, 0, 0x5fb, 0);
					}
					if (a->type == 6 || a->type == 7) {
						fcn_0051af00(buf, 0x1d5c, b->slot);
						fcn_00545d40(b->id, b->id, buf, 0, 0x5fb, 0);
					}
				}
			}
			o->stamp = (*(Stamp_54f0c0*)&g_7f4c00);
			fcn_00500bb0(&o->stamp, 0, 2, 0);
			o->event = fcn_004c5620(-1, o);
		}
		break;
	}
}
