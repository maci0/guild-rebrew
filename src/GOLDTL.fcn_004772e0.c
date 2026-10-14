void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x40
typedef struct {
	char p0[0x10];
	int pitch;
	unsigned char bpp;
	char p15[7];
	char* bits;
	char p20[0x1c];
	int locked;
} Surf;

int __cdecl fcn_00475fd0(Surf*);
void __cdecl fcn_00476060(Surf*);

/* ADDRESS: GOLDTL 0x004772e0 */

void __cdecl fcn_004772e0(int x, int y, int w, int h, Surf* s)
{
	int locked;
	int i;

	if (s == 0) {
		return;
	}
	locked = s->locked;
	if (fcn_00475fd0(s) == 0) {
		return;
	}
	if (s->bpp == 0x10) {
		for (i = 0; i < h; i++) {
			memset(s->bits + ((y + i) * s->pitch + x) * 2, 0, w * 2);
		}
	} else if (s->bpp == 0x20) {
		for (i = 0; i < h; i++) {
			memset(s->bits + ((y + i) * s->pitch + x) * 4, 0, w * 4);
		}
	} else if (s->bpp == 0x18) {
		for (i = 0; i < h; i++) {
			memset(s->bits + ((y + i) * s->pitch + x) * 3, 0, w * 3);
		}
	}
	if (locked) {
		fcn_00475fd0(s);
	} else {
		fcn_00476060(s);
	}
}
