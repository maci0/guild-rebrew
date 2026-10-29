#include <stdio.h>
#include <string.h>

#include "Develop/Units/d3/d3_animation.h"

extern char g_67553c[]; /* morph_%i */
extern char g_675584[]; /* character/%s/%s.baf */
extern char g_675548[]; /* could not attach CurrentAnimStream */
extern char g_675598[]; /* huston we got a problem */
extern float g_6628cc;
extern int g_675314;
extern int g_675318;

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00435500(char*, char*);
void __cdecl fcn_004311a0(char*, char*, int, int, int);
void __cdecl fcn_00434760(char*, char);
int __cdecl fcn_00413190(char*);
int __cdecl fcn_00433be0(char*, char*, int, int, int, int, char*, int);
int __cdecl fcn_004316c0(char*);
void __cdecl fcn_0041d9e0(const char*);

/* Completes a pending animation morph on the character. A finished morph is
 * reported and released, a pending morph stream is created against the
 * current animation, and a plain pending animation stream is attached after
 * its name is resolved. The entity's animation slot is cleared in each
 * completed path. */
/* ADDRESS: GOLDTL 0x004045c0 */
void __cdecl ch_CheckAniMorph(char* obj)
{
	int cleared;
	char* entity;
	D3_ANIMATION_OPTIONS opt;
	char* src;
	char buf[0x60];
	char path[0x1f0];
	char* anim;
	char* frames;
	char* name;
	int frame;
	int step;
	int d;
	int prev;
	int interp;

	cleared = 0;
	src = *(char**) (obj + 0x70);
	entity = *(char**) (obj + 0x34);
	if (src != 0 && (src[0x6d] & 0x20) != 0 && (src[0x74] & 8) == 0 &&
	    (obj[0x8c] & 2) == 0) {
		frames = *(char**) (src + 0x68);
		if (frames[0x169] == 0 && (src[0x70] & 3) != 0) {
			fcn_004311a0(entity, src, 0, *(int*) src, 3);
		}
		fcn_00435500(*(char**) (entity + 0x1ec) + 0xf4, frames);
		*(char**) (obj + 0x70) = 0;
	}
	if (*(char**) (obj + 0x7c) != 0) {
		if ((*(char**) (obj + 0x7c))[0x6d] & 0x20) {
			sprintf(buf, g_67553c, obj);
			fcn_00435500(*(char**) (entity + 0x1ec) + 0xf4, buf);
			fcn_00434760(fcn_00433ba0(buf), 1);
			*(char**) (obj + 0x7c) = 0;
			cleared = 1;
		} else {
			return;
		}
	}
	anim = *(char**) (obj + 0x80);
	if (anim != 0 && *(char**) (obj + 0x7c) == 0) {
		src = *(char**) (obj + 0x70);
		if (src != 0) {
			/* morph the running animation into the pending stream */
			frame = *(int*) (anim + 0x150);
			step = frame != -1 ? frame : 0;
			sprintf(buf, g_67553c, obj);
			frames = *(char**) (src + 0x68);
			d = *(int*) (*(char**) (anim + 0x15c) + step * 0xc0) -
			    *(int*) (*(char**) (frames + 0x15c) + *(int*) src * 0xc0);
			prev = *(int*) (*(char**) (frames + 0x15c) +
			                (*(int*) (frames + 0x148) - 1) * 0xc0);
			interp = (int) ((float) ((prev + d) / 2) + g_6628cc);
			entity = *(char**) (*(char**) (obj + 0x34) + 0x1cc);
			if (entity != 0) {
				if (fcn_00433be0(*(char**) (entity + 0x318), frames,
				                 *(int*) src * 0xc0 + *(int*) (frames + 0x15c),
				                 anim,
				                 *(int*) (anim + 0x15c) + step * 0xc0, 0,
				                 buf, interp)) {
					opt.mode = 0;
					opt.layer = 0x18;
					opt.loop = 0;
					opt.reverse = 0;
					opt.queue = 1;
					anim = fcn_00434970(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4,
					                    buf, opt);
					*(char**) (obj + 0x7c) = anim;
					if (anim != 0) {
						if (fcn_00413190(*(char**) (obj + 0x88)) != 0) {
							*(int*) (anim + 0x3c) = g_675314;
						} else {
							*(int*) (anim + 0x3c) = -1;
						}
					}
				} else {
					*(char**) (obj + 0x7c) = 0;
				}
			}
			frames = *(char**) (src + 0x68);
			if (frames[0x169] == 0 && (src[0x70] & 3) != 0) {
				fcn_004311a0(*(char**) (obj + 0x34), src, 0, *(int*) src, 3);
			}
			fcn_00435500(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, frames);
			entity = *(char**) (*(char**) (obj + 0x34) + 0x1cc);
			if (entity != 0 && *(int*) (entity + 0x390) != 0 &&
			    *(int*) (entity + 0x40c) != 0) {
				fcn_0041d9e0(g_675598);
			}
			*(char**) (obj + 0x70) = 0;
			return;
		}
		if (*(char**) (obj + 0x7c) == 0 && *(char**) (obj + 0x70) == 0) {
			/* attach the pending animation stream by name */
			name = *(char**) (obj + 0x80);
			*(int*) (anim + 0x14c) = *(int*) (anim + 0x14c) - 1;
			sprintf(path, g_675584, obj + 0x130, name);
			if (fcn_00433ba0(name) == 0) {
				d3_LoadAnimStream(path, name, 0);
			}
			opt.mode = (unsigned char) obj[0x84] >= 1 ? (unsigned char) obj[0x84] : 1;
			opt.layer = (unsigned char) obj[0x84] == 1 ? 0x18 : 0x08;
			opt.loop = 0;
			opt.reverse = 0;
			opt.queue = 1;
			anim = fcn_00434970(*(char**) (entity + 0x1ec) + 0xf4, name, opt);
			*(char**) (obj + 0x70) = anim;
			*(char*) (obj + 0x85) = -1;
			if (anim != 0) {
				if (fcn_00413190(*(char**) (obj + 0x88)) != 0) {
					*(int*) (anim + 0x3c) = g_675318;
				} else {
					*(int*) (anim + 0x3c) = -1;
				}
				frame = *(int*) (name + 0x150);
				if (frame != -1 && cleared != 0) {
					*(int*) anim = frame;
					*(int*) (anim + 4) = frame + 1;
					fcn_004316c0(entity);
				}
			} else {
				sprintf(path, g_675548, name);
			}
			*(char**) (obj + 0x80) = 0;
		}
	}
}
