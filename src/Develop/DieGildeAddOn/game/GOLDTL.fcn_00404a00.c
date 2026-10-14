#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "../../Units/d3/d3_animation.h"

int __cdecl fcn_0065f220(const char*, const char*);
void __cdecl fcn_0042e540(char*);
int __cdecl fcn_00433ba0(char*);
void __cdecl fcn_0044c620(char*, char*, char);
char* __cdecl fcn_00434970(char*, char*, D3_ANIMATION_OPTIONS);
void __cdecl fcn_00435500(char*, char*);



#include "ch_motion.h"

char* __cdecl fcn_00433be0(char*, char*, char*, int, int, char*, char*, int);
void __cdecl fcn_004311a0(char*, char*, int, int, int);
#ifdef REBREW_GOLD
int __cdecl fcn_00411be0(char*);
#else
int __cdecl fcn_00413190(char*);
#endif


/* The option padding is left as in the native partially initialized view. */
void __cdecl ch_FinishAni(char* obj)
{
    char* node;
    char* ani;
    char* stream;
    D3_ANIMATION_OPTIONS opt;
    char name[0x60];

    node = *(char**) (obj + 0x34);
    if (*(char**) (obj + 0x70) == 0) {
        return;
    }
    sprintf(name, "morph_%i", (int) obj);
    if (fcn_00433ba0(name) != 0) {
        return;
    }
    if (*(char**) (node + 0x1cc) != 0) {
#ifdef REBREW_GOLD
        stream = *(char**) (*(char**) (node + 0x1cc) + 0x10);
#else
        stream = *(char**) (*(char**) (node + 0x1cc) + 0x318);
#endif
        ani = *(char**) (obj + 0x70);
        if (fcn_00433be0(stream, *(char**) (ani + 0x68),
            *(char**) (*(char**) (ani + 0x68) + 0x15c) + 0xc0 * *(int*) ani,
            0, 0, stream, name, 4) != 0) {
            *(int*) &opt = 0;
            opt.queue = 1;
            opt.reverse = 0;
            opt.loop = 0;
            opt.layer = 0x18;
            *(char**) (obj + 0x7c) = fcn_00434970(
                *(char**) (node + 0x1ec) + 0xf4, name, opt);
            if (*(char**) (obj + 0x7c) != 0) {
#ifdef REBREW_GOLD
                if (fcn_00411be0(*(char**) (obj + 0x88)) == 0) {
#else
                if (fcn_00413190(*(char**) (obj + 0x88)) == 0) {
#endif
                    *(int*) (*(char**) (obj + 0x7c) + 0x3c) = -1;
                } else {
                    *(int*) (*(char**) (obj + 0x7c) + 0x3c) = ch_MorphFrameValue;
                }
            }
        }
    }
    ani = *(char**) (obj + 0x70);
    if ((*(char**) (ani + 0x68))[0x169] == 0 && (ani[0x70] & 3) != 0) {
        fcn_004311a0(node, ani, 0, *(int*) ani, 3);
    }
    fcn_00435500(*(char**) (node + 0x1ec) + 0xf4, *(char**) (ani + 0x68));
    *(char**) (obj + 0x70) = 0;
}

/* Loads each named motion of a character that is not loaded yet; walking
 * and cart pulling are loaded looping. */
void __cdecl fcn_00404a00(char* obj, int n, ...)
{
	int i;
	va_list ap;
	char* name;
	char looped;
	D3_ANIMATION_OPTIONS opt;
	char ani[0x100];
	char path[0x100];

	va_start(ap, n);
	for (i = n; i > 0; i--) {
		name = va_arg(ap, char*);
		if (*name == 0) {
			continue;
		}
		looped = 0;
		if (fcn_0065f220(name, "bewegung/gehen") == 0 || fcn_0065f220(name, "bewegung/karren_ziehen") == 0) {
			looped = 1;
		}
		sprintf(path, "character/%s/%s_%s.baf", obj + 0x130, name, obj + 0x130);
		sprintf(ani, "%s_%s", name, obj + 0x130);
		fcn_0042e540(ani);
		if (fcn_00433ba0(ani) != 0) {
			continue;
		}
		fcn_0044c620(path, ani, looped);
		memset(&opt, 0, sizeof(opt));
		opt.queue = 1;
		opt.reverse = 0;
		opt.loop = 1;
		*(int*) &opt = 0;
		opt.layer = 0x18;
		opt.mode = 0;
		fcn_00434970(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, ani, opt);
		fcn_00435500(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, ani);
	}
	va_end(ap);
}

/* Inferred name. The unused native helper reads address 0x34 literally. */
void __cdecl ch_PreloadModelMotions(char* model, int n, ...)
{
    int i;
    va_list ap;
    char* name;
    D3_ANIMATION_OPTIONS opt;
    char ani[0x100];
    char path[0x100];

    va_start(ap, n);
    for (i = n; i > 0; i--) {
        name = va_arg(ap, char*);
        if (*name == 0) {
            continue;
        }
        sprintf(path, "character/%s/%s_%s.baf", model, name, model);
        sprintf(ani, "%s_%s", name, model);
        fcn_0042e540(ani);
        if (fcn_00433ba0(ani) != 0) {
            continue;
        }
        fcn_0044c620(path, ani, 0);
        memset(&opt, 0, sizeof(opt));
        opt.queue = 1;
        opt.reverse = 0;
        opt.loop = 1;
        *(int*) &opt = 0;
        opt.layer = 0x18;
        opt.mode = 0;
        fcn_00434970(*(char**) (*(char**) 0x34 + 0x1ec) + 0xf4, ani, opt);
        fcn_00435500(*(char**) (*(char**) 0x34 + 0x1ec) + 0xf4, ani);
    }
    va_end(ap);
}
