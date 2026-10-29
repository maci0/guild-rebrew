#include <stdio.h>

/* Character task fields used by this body. */
extern int g_6b5c24;    /* game tick counter */
extern char g_6b5c28;   /* scene debug switch */
extern int g_6b8010;    /* scripted-motion mode */

/* Shared float pool reached through raw .rdata addresses. */
extern float g_662910;
extern double g_6629c8;
extern float g_6629c0;
extern float g_6629bc;
extern float g_6629b8;
extern float g_6629b4;
extern float g_6629b0;
extern float g_675308;

extern char g_675504[]; /* "%s_%s" */
extern char g_6753fc[]; /* "bewegung/gehen" */

int __cdecl fcn_00402610(char*);
int __cdecl fcn_004050c0(char*);
int __cdecl fcn_00407610(char*);
int __cdecl fcn_004094c0(char*, int);
void __cdecl fcn_004098e0(char*, int);
int __cdecl fcn_00409ae0(char*, int);
int __cdecl fcn_00409c90(char*, int);
void __cdecl ch_FinishAni(char*);
void __cdecl fcn_00435500(char*, char*);
void __cdecl fcn_00433780(void*);
void __cdecl fcn_00438b40(char*, int*);
int __cdecl fcn_004053a0(char*, int);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_0042e540(char*);
void __cdecl ch_WalkOnPathRotation(char*);

/* ADDRESS: GOLDTL 0x0040a600 */
void __cdecl ch_WalkOnPath(char* obj)
{
	char buf[256];
	char* inst;
	char* anim;
	int res;
	int cell;
	float speed;

	res = fcn_00402610(*(char**) (obj + 0x14));
	inst = *(char**) (obj + 0x14);
	if (*(char*) (obj + 0x160) < 0) {
		anim = *(char**) (inst + 0x7c);
		if (anim != 0) {
			if ((anim[0x6d] & 0x20) == 0) {
				return;
			}
		}
		fcn_004050c0(obj);
		return;
	}
	if (*(char*) (obj + 0x190) != 0) {
		sprintf(buf, g_675504, g_6753fc, inst + 0x130);
		fcn_0042e540(buf);
		anim = *(char**) (inst + 0x70);
		if (anim != 0) {
			fcn_00435500(*(char**) (*(char**) (*(char**) (obj + 0x14) + 0x34) + 0x1ec) + 0xf4,
			             *(char**) (anim + 0x68));
		}
		*(char**) (inst + 0x70) = 0;
		fcn_00407610(obj);
cleanup:
		if (g_6b5c28 != 0) {
			*(char*) (*(char**) (obj + 0x14) + 0x8c) |= 8;
		}
		if (*(int*) (obj + 0xf4) != 0) {
			m_FreeTracked(*(void**) (obj + 0xf4));
			*(int*) (obj + 0xf4) = 0;
		}
		fcn_004050c0(obj);
		return;
	}
	if (*(int*) (obj + 0x154) != -1) {
		if (g_6b5c24 < *(int*) (obj + 0x154) + 225) {
			return;
		}
		anim = *(char**) (inst + 0x70);
		if (anim != 0) {
			*(float*) (anim + 0x60) = 1.0f;
		}
		*(int*) (obj + 0x154) = -1;
	}
	if (*(unsigned int*) (obj + 0x160) & 0x20) {
		*(int*) (obj + 0xc) = 0;
		*(unsigned int*) (obj + 0x160) &= ~0x20;
	}
	if (*(int*) (obj + 0xc) == 0) {
		if (*(char*) (*(char**) (inst + 0x88) + 0x3d5) != 0) {
			fcn_004050c0(obj);
			return;
		}
		if (!fcn_004094c0(obj, res)) {
			return;
		}
	}
	if (*(unsigned int*) (obj + 0x160) & 0x40) {
		anim = *(char**) (inst + 0x70);
		if (anim != 0 && (anim[0x6d] & 0x20) != 0) {
			fcn_00435500(*(char**) (*(char**) (inst + 0x34) + 0x1ec) + 0xf4,
			             *(char**) (anim + 0x68));
			fcn_00433780(*(char**) (inst + 0x34));
			*(int*) (inst + 0x78) = 0;
			*(unsigned int*) (obj + 0x160) &= ~0x40;
		} else {
			if (anim != 0) {
				return;
			}
			*(unsigned int*) (obj + 0x160) &= ~0x40;
		}
	}
	if (*(int*) (obj + 0x104) == 0) {
		anim = *(char**) (inst + 0x70);
		if (anim == 0 || (anim[0x6d] & 0x20) != 0) {
			if (!fcn_00409ae0(obj, res)) {
				return;
			}
		}
	}
	if (*(int*) (obj + 0x104) == 0) {
		if (*(char**) (inst + 0x70) == 0) {
			goto cleanup;
		}
		if (*(char**) (inst + 0x70) != 0) {
			return;
		}
	}
	cell = fcn_00407610(obj);
	fcn_004098e0(obj, cell);
	if (*(float*) (inst + 0x1a4) < g_6629c8) {
		*(float*) (inst + 0x1a4) += g_662910;
	}
	if (*(int*) (obj + 0xf4) != 0 && !fcn_00409c90(obj, res)) {
		return;
	}
	if (*(int*) (obj + 0xf4) == 0 &&
	    (*(unsigned int*) (obj + 0x160) & 0x10) != 0) {
		anim = *(char**) (inst + 0x70);
		if (anim != 0 && (anim[0x74] & 8) != 0) {
			ch_FinishAni(inst);
			if (g_6b5c28 != 0) {
				*(unsigned short*) (*(char**) (obj + 0x14) + 0x8c) |= 8;
			}
			*(unsigned int*) (obj + 0x160) |= 0x80;
			fcn_00438b40(*(char**) (inst + 0x34), (int*) (obj + 0x144));
			fcn_004053a0(inst, g_6b8010 != 0);
			return;
		}
	}
	ch_WalkOnPathRotation(obj);
	if (cell == 0 || cell == 0xd) {
		return;
	}
	anim = *(char**) (inst + 0x70);
	if (anim == 0) {
		return;
	}
	speed = g_6629c0;
	if (*(int*) (inst + 0x2c) == -1 &&
	    *(int*) (*(char**) (inst + 0x34) + 0x204) != 0) {
		speed = g_675308;
	}
	if (*(unsigned int*) (inst + 4) & 8) {
		if (cell != 0xb && cell != 6) {
			*(float*) (anim + 0x60) = *(float*) (inst + 0x1a0) *
			                          *(float*) (inst + 0x1a4) * speed *
			                          g_6629bc;
			return;
		}
		*(float*) (anim + 0x60) = *(float*) (inst + 0x1a0) *
		                          *(float*) (inst + 0x1a4) * speed *
		                          g_6629b8;
		return;
	}
	if (cell != 0xb && cell != 6) {
		*(float*) (anim + 0x60) = *(float*) (inst + 0x1a0) *
		                          *(float*) (inst + 0x1a4) * speed * g_6629b4;
		return;
	}
	*(float*) (anim + 0x60) = *(float*) (inst + 0x1a0) *
	                          *(float*) (inst + 0x1a4) * speed * g_6629b0;
}
char g_6b5c28 = 0;
unsigned char _dpad_6b5c28[148] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
