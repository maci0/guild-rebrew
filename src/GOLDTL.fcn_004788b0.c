// SIZE 0x20
typedef struct {
	int p0;
	int x4;
	char p8[0xc];
	unsigned char bpp;
	char p15[7];
	int x1c;
} Surf;

// SIZE 0xe
typedef struct {
	char p0[0xc];
	char kind;
	char mode;
} Img;

Img* __cdecl fcn_00477590(int, int, int, int, int, int, int);
Img* __cdecl fcn_00477e70(int, int, int, int, int, int, int);
Img* __cdecl fcn_00478400(int, int, int, int, int, int, int);
Img* __cdecl fcn_00477ae0(int, int, int, int, int, int, int);
Img* __cdecl fcn_004781e0(int, int, int, int, int, int, int);

// FUNCTION: GOLDTL 0x004788b0

Img* __cdecl fcn_004788b0(int a1, int a2, int a3, int a4, Surf* s, int mode, char alpha)
{
	Img* r;
	int kind;

	r = 0;
	if (alpha) {
		switch (s->bpp) {
		case 0x18:
			r = fcn_00477590(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 2;
			break;
		case 0x10:
			r = fcn_00477e70(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 1;
			break;
		case 8:
			r = fcn_00478400(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 0;
			break;
		default:
			break;
		}
	} else {
		switch (s->bpp) {
		case 0x18:
			r = fcn_00477ae0(a1, a2, a3, a4, s->x1c, mode, s->x4);
			kind = 2;
			break;
		case 0x10:
			r = fcn_004781e0(a1, a2, a3, a4, s->x1c, mode, s->x4);
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
