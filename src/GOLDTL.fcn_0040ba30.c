// FUNCTION: GOLDTL 0x0040ba30
// SIZE: 833

#include <string.h>

typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Col;
// SIZE 0x4

typedef struct {
	char* ent;
	char pad4[0x7c];
} Hit;
// SIZE 0x80

typedef struct {
	char pad0[0xc];
	int started;
	char pad10[4];
	char* ent;
	char pad18[0x30 - 0x18];
	int fade_in;
	char pad34[0x50 - 0x34];
	float start;
} Fade;
// SIZE 0x54

extern int g_6b5c24;
extern int g_67530c;
extern int g_675310;
extern int g_67a370;

void __cdecl fcn_00402a00(char*, int);
void __cdecl fcn_0043a3f0(char*, int, Col);
int __cdecl fcn_00405d70(char* self, char** out, float range);
char* __cdecl fcn_004051d0(char*, Fade*, int, ...);
void __cdecl fcn_004050c0(Fade*);

void __cdecl fcn_0040ba30(Fade* f)
{
	char* e;
	Col col;
	float alpha;
	Hit hit;

	e = f->ent;
	if (f->started == 0) {
		if (*(int*) (*(char**) (e + 0x34) + 0x1cc) == 0) {
			fcn_004050c0(f);
			return;
		}
		if (g_67530c != *(int*) (e + 0x2c) || g_675310 != *(int*) (e + 0x30)) {
			if (*(int*) (e + 0x2c) != -1) {
				fcn_00402a00(e, 0);
			} else {
				fcn_00402a00(e, f->fade_in);
			}
			fcn_004050c0(f);
			return;
		}
		fcn_00402a00(e, 1);
		memset(&col, 0, sizeof(col));
		col.c &= 0xfe;
		col.a = 0xff;
		fcn_0043a3f0(*(char**) (e + 0x34), *(int*) (*(char**) (e + 0x34) + 0x1cc), col);
		if (*(char***) (e + 0x124) != 0) {
			fcn_0043a3f0(**(char***) (e + 0x124), *(int*) (**(char***) (e + 0x124) + 0x1cc), col);
		}
		if (*(char**) (e + 0x22c) != 0) {
			fcn_0043a3f0(*(char**) (e + 0x22c), *(int*) (*(char**) (e + 0x22c) + 0x1cc), col);
		}
		f->start = (float) (g_6b5c24 - 1);
		*(unsigned short*) (e + 0x8c) = (*(unsigned short*) (e + 0x8c) & 0xbfff) | 0x40;
	}
	alpha = (g_6b5c24 - f->start) * 0.02f;
	if (f->fade_in == 0) {
		alpha = 1.0f - alpha;
	}
	if (!(alpha > 0.0f)) {
		alpha = 0.0f;
	} else if (!(alpha < 1.0f)) {
		alpha = 1.0f;
	}
	if (*(int*) (e + 0x88) == g_67a370 && f->fade_in != 0 && (*(unsigned short*) (e + 0x8c) & 0x4000) == 0 &&
	    alpha < 0.1 && fcn_00405d70(e, &hit.ent, 30.0f) != 0) {
		f->start = (float) (g_6b5c24 - 1);
		*(unsigned short*) (hit.ent + 0x8c) |= 0x4000;
		fcn_004051d0(e, f, 0x3b, 0x4b);
		return;
	}
	alpha *= 255.0f;
	memset(&col, 0, sizeof(col));
	col.c &= 0xfe;
	col.a = (unsigned char) alpha;
	if (alpha != 255.0f && alpha != 0.0f) {
		fcn_0043a3f0(*(char**) (e + 0x34), *(int*) (*(char**) (e + 0x34) + 0x1cc), col);
		if (*(char***) (e + 0x124) != 0) {
			fcn_0043a3f0(**(char***) (e + 0x124), *(int*) (**(char***) (e + 0x124) + 0x1cc), col);
		}
		if (*(char**) (e + 0x22c) != 0) {
			fcn_0043a3f0(*(char**) (e + 0x22c), *(int*) (*(char**) (e + 0x22c) + 0x1cc), col);
		}
	}
	if (alpha == 0.0f || alpha == 255.0f) {
		e[0x8c] &= 0xbf;
		col.c &= 0xfe;
		col.a = 0xff;
		fcn_0043a3f0(*(char**) (e + 0x34), *(int*) (*(char**) (e + 0x34) + 0x1cc), col);
		if (*(char***) (e + 0x124) != 0) {
			fcn_0043a3f0(**(char***) (e + 0x124), *(int*) (**(char***) (e + 0x124) + 0x1cc), col);
		}
		if (*(char**) (e + 0x22c) != 0) {
			fcn_0043a3f0(*(char**) (e + 0x22c), *(int*) (*(char**) (e + 0x22c) + 0x1cc), col);
		}
		if (alpha == 0.0f) {
			fcn_00402a00(e, 0);
		} else if (alpha == 255.0f) {
			fcn_00402a00(e, 1);
		}
		fcn_004050c0(f);
	}
}
