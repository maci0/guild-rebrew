#include <string.h>
#include "Develop/DieGildeAddOn/game/ch_motion.h"
#include "Develop/Units/d3/d3_animation.h"

char* __cdecl fcn_00401040(char* path);

/* ADDRESS: GOLDTL 0x0040ed40 */
int __cdecl fcn_0040ed40(char** character, char** animation, int* kind)
{
	D3_ANIMATION_OPTIONS options;
	char path[256];
	char name[256];
	char* object;
	char* draw;
	char** slot;
	int i;
	char copied;

	object = *character;
	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) fcn_0040ed40) {
		draw = *(char**) (object + 0x1ec);
		i = 0;
		slot = (char**) (draw + 0x484);
		for (; i < 3; i++, slot = (char**) ((char*) slot + 0x7c)) {
			if (*slot != 0) {
				*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040ed40;
				return 0;
			}
		}
		return 0;
	}
	strcpy(path, *animation);
	strcat(path, ".baf");
	i = 0;
	do {
		copied = path[i];
		name[i] = copied;
		i++;
	} while (copied != 0);
	fcn_00401040(name);
	if (path[0] != 0 && object != 0 && *(char**) (object + 0x1cc) != 0) {
		if (fcn_00433ba0(name) == 0) {
			d3_LoadAnimStream(path, name, 0);
		}
		memset(&options, 0, sizeof(options));
		*(int*) &options = 0;
		options.layer = (unsigned char) (0x10 | ((*kind == 0) ? 0x08 : 0));
		options.queue = 1;
		options.mode = 0;
		options.loop = 1;
		options.reverse = 0;
		fcn_00434970(*(char**) (object + 0x1cc), name, options);
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040ed40;
	}
	return 0;
}
