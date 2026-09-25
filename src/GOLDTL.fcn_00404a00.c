#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// SIZE 0xc
struct animopt_404a00 {
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

int __cdecl fcn_0065f220(const char*, const char*);
void __cdecl fcn_0042e540(char*);
int __cdecl fcn_00433ba0(char*);
void __cdecl fcn_0044c620(char*, char*, char);
char* __cdecl fcn_00434970(char*, char*, struct animopt_404a00);
void __cdecl fcn_00435500(char*, char*);

// FUNCTION: GOLDTL 0x404a00
// SIZE: 342

/* Loads each named motion of a character that is not loaded yet; walking
 * and cart pulling are loaded looping. */
void __cdecl fcn_00404a00(char* obj, int n, ...)
{
	int i;
	va_list ap;
	char* name;
	char looped;
	struct animopt_404a00 opt;
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
