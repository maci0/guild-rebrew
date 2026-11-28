#include <string.h>

#include "Develop/Units/d3/d3_animation.h"

char* __cdecl StripPathAndExt(char* path);
char* __cdecl d3_FindAnimByName(const char* name);
char* __cdecl d3_LoadAnimStream(char* path, char* name, char loop);
void __cdecl d3_RemoveObjectAnimation(char* a, char* b);

/* ADDRESS: GOLDTL 0x0040eed0 */
/* ADDRESS: GOLDDE 0x0040dcd0 */
int __cdecl PreloadAnim(char*** arg1, char** arg2)
{
	D3_ANIMATION_OPTIONS opt;
	char buf1[0x100];
	char buf2[0x100];
	char* anim;
	char* obj;

	obj = (char*) *arg1;
	strcpy(buf1, *arg2);
	strcat(buf1, ".baf");
	strcpy(buf2, buf1);
	anim = StripPathAndExt(buf2);
	if (buf1[0] != 0 && obj != 0 && *(char**) (obj + 0x1cc) != 0) {
		if (d3_FindAnimByName(buf2) == 0) {
			d3_LoadAnimStream(buf1, buf2, 0);
		}
		memset(&opt, 0, sizeof(opt));
		opt.layer = 0x10;
		opt.mode = 0;
		opt.queue = 1;
		opt.reverse = 0;
		opt.loop = 1;
		d3_AttachAnimationToContext(*(char**) (obj + 0x1cc), anim, opt);
		d3_RemoveObjectAnimation(*(char**) (obj + 0x1cc), anim);
	}
	return 0;
}
