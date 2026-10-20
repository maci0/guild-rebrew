#include <stdio.h>
#include <string.h>

#include "Develop/Units/d3/d3_animation.h"

extern int g_675318;

void __cdecl fcn_0042e540(char*);
int __cdecl fcn_00413190(char*);

/* ADDRESS: GOLDTL 0x00404dc0 */

/* Builds the animation path and stream name for a named motion, loads the
 * stream when it is not loaded yet and attaches it to the object. The
 * empty-name path stores an uninitialized stream, as the native does. */
char* __cdecl ch_AttachAni(char* obj, char* name, unsigned char force)
{
	D3_ANIMATION_OPTIONS opt;
	char* anim;
	char ani[0x110];
	char path[0x110];
	char msg[0x200];

	fcn_0042e540(name);
	sprintf(path, "character/%s/%s_%s.baf", obj + 0x130, name, obj + 0x130);
	sprintf(ani, "%s_%s", name, obj + 0x130);
	fcn_0042e540(ani);
	if (*name != 0) {
		memset(&opt, 0, sizeof(opt));
		opt.queue = 1;
		opt.reverse = 1;
		opt.loop = 1;
		*(int*) &opt = 0;
		opt.layer = (force & 1) << 3 | 0x10;
		opt.mode = 0;
		if (fcn_00433ba0(ani) == 0) {
			if (strcmp(name, "bewegung/gehen") == 0 ||
				strcmp(name, "bewegung/karren_ziehen") == 0) {
				d3_LoadAnimStream(path, ani, 1);
			} else {
				d3_LoadAnimStream(path, ani, 0);
			}
		}
		anim = fcn_00434970(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, ani, opt);
		if (anim == 0) {
			sprintf(msg, "ch_AttachAni(): Could not attach ani: %s", name);
			return 0;
		}
		if (fcn_00413190(*(char**) (obj + 0x88)) == 0) {
			*(int*) (anim + 0x3c) = -1;
		} else {
			*(int*) (anim + 0x3c) = g_675318;
		}
	}
	*(char**) (obj + 0x70) = anim;
	*(char*) (obj + 0x85) = -1;
	return anim;
}
