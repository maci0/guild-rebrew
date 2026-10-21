#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "Develop/Units/d3/d3_animation.h"

void __cdecl fcn_0042e540(char*);

/* ADDRESS: GOLDTL 0x00404b60 */
void __cdecl fcn_00404b60(char* obj, int n, ...)
{
	D3_ANIMATION_OPTIONS opt;
	int i;
	va_list ap;
	char low[0x100];
	char path[0x100];

	va_start(ap, n);
	for (i = n; i > 0; i--) {
		char* name;
		name = va_arg(ap, char*);
		if (*name == 0) {
			continue;
		}
		sprintf(path, "lowpolycharacter/%s/%s_%s_LOW.baf", obj + 0x230, name, obj + 0x230);
		sprintf(low, "%s_%s_LOW.baf", name, obj + 0x230);
		fcn_0042e540(low);
		if (fcn_00433ba0(low) == 0 && d3_LoadAnimStream(path, low, 1) == 0) {
			continue;
		}
		memset(&opt, 0, sizeof(opt));
		opt.queue = 1;
		opt.reverse = 0;
		opt.loop = 0;
		*(int*) &opt = 0;
		opt.layer = 8;
		opt.mode = 0;
		fcn_00434970(*(char**) (*(char**) (obj + 0x22c) + 0x1ec) + 0xf4, low, opt);
		fcn_00435500(*(char**) (*(char**) (obj + 0x22c) + 0x1ec) + 0xf4, low);
	}
	va_end(ap);
}
