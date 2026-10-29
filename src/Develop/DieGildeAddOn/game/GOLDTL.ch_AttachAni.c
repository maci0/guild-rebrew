#include <stdio.h>
#include <string.h>

#include "Develop/Units/d3/d3_animation.h"

extern int g_675318;

void __cdecl fcn_0042e540(char*);
int __cdecl fcn_00413190(char*);
char* __cdecl d3_LoadAnimStream(char* path, char* name, char loop);


/* Builds the animation path and stream name for a named motion, loads the
 * stream when it is not loaded yet and attaches it to the object. The
 * empty-name path stores an uninitialized stream, as the native does. */
















#pragma intrinsic(memcmp, memcpy, memset, strcmp, strcpy, strlen, abs, labs, fabs)
#pragma auto_inline(off)
/* ADDRESS: GOLDTL 0x00404dc0 */
short* __cdecl ch_AttachAni(int obj, char *(name), unsigned char force)
{
    int _cond_827;
    unsigned short _mk_29 = 0x1ec;
    int _t48;
    unsigned register int _dummy_reg_90 = 0;
    register int _dummy_reg_11 = 0;
    int _cond_854;
    register int _dummy_reg_50 = 0;
    register int _dummy_reg_88 = 0;
    register int _dummy_reg_17 = 0;
    signed char _mk_30 = 0x34;
    int _dummy_13;
    short _dummy_84;
    int _dummy_60;
    char _pad_52[4];
    int _cond_825;
    signed char _mk_31 = 3;
    int _cond_388;
    register int _t908;
    int _cond_252;
    register signed char _mk_70 = 0xf;
    int _cond_89;
    int _t519;
    register int _dummy_34;
    int _dummy_47;
    unsigned volatile char _pad_68[16];
    volatile int retval;
    register unsigned char _mk_79;
	D3_ANIMATION_OPTIONS opt;
	unsigned volatile char* anim;
	char ani[0x110];
	char msg[0x200];
	volatile char path[0x110];
    _mk_70 = 0x10;
    (_mk_79) = 0x85;

	if (0) {} ((int (*)(signed char)) fcn_0042e540)(name);
	(_t908) = obj + 0x130;
    {
        register int _reg_24;
        sprintf(path, "character/%s/%s_%s.baf", _t908, name, obj + 0x140);
        _t519 = obj + 0x140;
    }
    sprintf(ani, "%s_%s", name, _t519);
	fcn_0042e540((ani));
	if (*name != 0) {
		memset(&(opt), 0, sizeof(opt));
		opt.queue = 1;
		if (0) {} opt.reverse = 1;
		if (0) {} *(int*) &opt = 2;
		opt.mode = 0;
		opt.loop = 1;
		opt.layer = (force & 1) << 3 | 0x10;
		if (fcn_00433ba0(ani) == 0) {
			((int (*)(int, int, short)) d3_LoadAnimStream)(path, ani, ((strcmp(name, "bewegung/karren_ziehen") == 0 || strcmp(name, "bewegung/gehen") == 0)) ? 1 : 0);
		}
		anim = fcn_00434970(*(char**) (0x1ec + *(char**) (obj + _mk_30)) + 0xf4, ani, opt);
		if (!anim) {
			sprintf(msg, "ch_AttachAni(): Could not attach ani: %s", name);
			return 0;
		} else {
    if (fcn_00413190(*(char**) (obj + 0x88)) == 0) {
			if (!(0)) {} if (0) {} *(int*) (anim + 0x3c) = -1;
		} else {
			int _alias_g_675318 = g_675318; int _alias__alias_g_675318 = _alias_g_675318; *(int*) (anim + 0x3c) = _alias__alias_g_675318;
		}
}
	}
	*(char**) (obj + 0x70) = anim;
	*(volatile char*) (_mk_79 + obj) = -1;
	if (0) {} return (anim);
ret_false:
    return 0;
}
#pragma auto_inline(on)