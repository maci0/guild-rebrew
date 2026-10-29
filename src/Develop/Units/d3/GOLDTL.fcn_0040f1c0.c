#include <string.h>
#include <stdlib.h>
#include "Develop/Units/d3/d3_animation.h"

char* __cdecl fcn_00401040(char* path);

/* ADDRESS: GOLDTL 0x0040f1c0 */
char __cdecl fcn_0040f1c0(char* a0, char* a1)
{
	D3_ANIMATION_OPTIONS options;
	char path[256];
	char name[256];
	char resolved[256];
	char* short_name;
	char* anim;
	char* object;
	char* motion;
	int kind;
	int frame;
	int i;
	char copied;

	object = a0;
	motion = a1;
	if (strstr(object, motion) == 0) {
		return 1;
	}
	strcpy(path, motion + 0x40);
	strcat(path, ".baf");
	i = 0;
	do {
		copied = path[i];
		name[i] = copied;
		i++;
	} while (copied != 0);
	short_name = fcn_00401040(name);
	if (short_name != 0) {
		strcpy(resolved, short_name);
	}
	if (path[0] != 0 && object != 0 && *(char**) (object + 0x1cc) != 0) {
		if (fcn_00433ba0(name) == 0) {
			d3_LoadAnimStream(path, name, 0);
		}
		memset(&options, 0, sizeof(options));
		*(int*) &options = 0;
		kind = *(int*) (motion + 0xc0);
		options.queue = 1;
		options.layer = kind == 1 ? 0x10 : 0;
		options.mode = (unsigned char) kind;
		options.reverse = 0;
		options.loop = 1;
		anim = fcn_00434970(*(char**) (object + 0x1cc), name, options);
		if (anim != 0 && *(int*) (motion + 0xc4) != 0) {
			frame = rand() % (*(int*) (*(int*) (anim + 0x68) + 0x148) - 1);
			*(int*) anim = frame;
			*(int*) (anim + 4) = frame + 1;
		}
	}
	return 1;
}
