typedef struct {
	int p0;
	short x4;
	char p6[2];
	char p8[0xc];
	unsigned char bpp;
	char p15[7];
	int x1c;
} Surf0047b210;
// SIZE 0x20

typedef struct {
	char p0[0xc];
	char kind;
	char mode;
} Img0047b210;
// SIZE 0xe

Img0047b210* __cdecl fcn_00479f30(int, int, int, int, int, int, short);
Img0047b210* __cdecl fcn_0047a7c0(int, int, int, int, int, int, short);
Img0047b210* __cdecl fcn_0047ad30(int, int, int, int, int, int, short);
Img0047b210* __cdecl fcn_0047a450(int, int, int, int, int, int, short);
Img0047b210* __cdecl fcn_0047ab20(int, int, int, int, int, int, short);

/* ADDRESS: GOLD 0x0047b210 */

Img0047b210* __cdecl fcn_0047b210(int a1, int a2, int a3, int a4, Surf0047b210* s, int mode, char alpha)
{
	Img0047b210* r;
	int kind;

	r = 0;
	if (alpha) {
		switch (s->bpp) {
		case 0x18:
			r = fcn_00479f30(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 2;
			break;
		case 0x10:
			r = fcn_0047a7c0(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 1;
			break;
		case 8:
			r = fcn_0047ad30(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 0;
			break;
		default:
			break;
		}
	} else {
		switch (s->bpp) {
		case 0x18:
			r = fcn_0047a450(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 2;
			break;
		case 0x10:
			r = fcn_0047ab20(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 1;
			break;
		default:
			break;
		}
	}
	if (r != 0) {
		r->kind = (char) kind;
		r->mode = (char) mode;
	}
	return r;
}
