#include <stdio.h>
#include <string.h>

// SIZE 0x4c
struct kind_404150 {
	char pad[5];
	char name[0x47];
};

// SIZE 0xc
struct animopt_404150 {
	unsigned char mode;
	unsigned char layer;
	unsigned char pad2[2];
	unsigned int loop : 1;
	unsigned int reverse : 1;
	unsigned int pad4 : 30;
	unsigned char blend : 1;
	unsigned char queue : 1;
	unsigned char pad8[3];
};

#include "../../../client_types.h"
extern Entry_14d0c40 g_14d0c40[];
extern int g_675318;

void __cdecl fcn_0042e540(char*);
int __cdecl fcn_00433ba0(char*);
void __cdecl fcn_0044c620(char*, char*, int);
char* __cdecl fcn_00434970(char*, char*, struct animopt_404150);
int __cdecl fcn_00413190(int);

// FUNCTION: GOLD 0x00403950
// FUNCTION: GOLDTL 0x404150

/* Attaches the named motion of a character kind to an object. */
char* __cdecl ch_AttachMotion(char* obj, int kind)
{
	struct animopt_404150 opt;
	char* anim;
	char ani[0x110];
	char path[0x110];
	char msg[0x200];

	sprintf(path, "character/%s/%s_%s.baf", obj + 0x130, ((struct kind_404150*)g_14d0c40)[kind].name, obj + 0x130);
	sprintf(ani, "%s_%s", ((struct kind_404150*)g_14d0c40)[kind].name, obj + 0x130);
	fcn_0042e540(ani);
	if (path[0] != 0) {
		memset(&opt, 0, sizeof(opt));
		opt.queue = 1;
		opt.reverse = 0;
		opt.loop = 1;
		*(int*) &opt = 0;
		opt.layer = 0x18;
		opt.mode = 0;
		if (fcn_00433ba0(ani) == 0) {
			fcn_0044c620(path, ani, 1);
		}
		anim = fcn_00434970(*(char**) (*(char**) (obj + 0x34) + 0x1ec) + 0xf4, ani, opt);
		if (anim == 0) {
			sprintf(msg, "ch_AttachMotion(): Could not attach ani: %s", path);
			return 0;
		}
	}
	if (fcn_00413190(*(int*) (obj + 0x88)) == 0) {
		*(int*) (anim + 0x3c) = -1;
	} else {
		*(int*) (anim + 0x3c) = g_675318;
	}
	return anim;
}
