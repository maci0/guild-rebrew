#include <stdio.h>
#include <string.h>

/* Inferred names; the native call passes all 12 bytes by value. */
typedef struct D3_ANIMATION_OPTIONS {
	unsigned char mode;
	unsigned char layer;
	unsigned char pad2[2];
	unsigned int loop : 1;
	unsigned int reverse : 1;
	unsigned int pad4 : 30;
	unsigned char blend : 1;
	unsigned char queue : 1;
	unsigned char pad8[3];
} D3_ANIMATION_OPTIONS;

extern int g_1041d08;

char* __cdecl fcn_00401040(char*);
char* __cdecl fcn_00433ba0(char*);
char* __cdecl d3_LoadAnimStream(char*, char*, char);
char* __cdecl fcn_00434970(char*, char*, D3_ANIMATION_OPTIONS);
char* __cdecl d3_LoadObjectAnim(char*, char*, char);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00412f10 */
/* Builds the animation stream name from the object name, loads the stream when
 * it is absent and attaches it, falling back to loading a whole object
 * animation named "<prefix><name>.oam" when no stream context is set. */
int __cdecl fcn_00412f10(char* obj, char* name, int flags)
{
	D3_ANIMATION_OPTIONS opt;
	char* stream;
	char* anim;
	char buf[0x100];
	char path[0x200];

	if (obj == 0 || name == 0) {
		return 0;
	}
	strcpy(buf, name);
	stream = fcn_00401040(buf);
	if (fcn_00433ba0(stream) == 0) {
		d3_LoadAnimStream(name, stream, 0);
	}
	memset(&opt, 0, sizeof(opt));
	if ((flags & 2) != 0) {
		opt.layer |= 0x10;
	}
	if ((flags & 1) != 0) {
		opt.layer &= 0xef;
	}
	if ((flags & 4) != 0) {
		opt.layer |= 2;
	}
	if ((flags & 0x10) != 0) {
		opt.layer |= 8;
	}
	if ((flags & 0x20) != 0) {
		opt.layer |= 4;
	}
	opt.queue |= 1;
	if (*(int*) (obj + 0x1ec) != 0) {
		anim = fcn_00434970(*(char**) (obj + 0x1ec) + 0xf4, stream, opt);
		if (anim != 0) {
			return 1;
		}
	}
	sprintf(path, "%s%s.oam", (char*) g_1041d08, name);
	anim = d3_LoadObjectAnim(path, obj, 1);
	if (anim == 0) {
		return 0;
	}
	if ((flags & 2) != 0) {
		*(unsigned char*) (anim + 0x2d) |= 0x10;
	}
	if ((flags & 1) != 0) {
		*(unsigned char*) (anim + 0x2d) &= 0xef;
	}
	if ((flags & 4) != 0) {
		*(unsigned char*) (anim + 0x2d) |= 2;
	}
	if ((flags & 0x10) != 0) {
		*(unsigned char*) (anim + 0x2d) |= 8;
	}
	if ((flags & 0x20) != 0) {
		*(unsigned char*) (anim + 0x2d) |= 4;
	}
	return 1;
}
