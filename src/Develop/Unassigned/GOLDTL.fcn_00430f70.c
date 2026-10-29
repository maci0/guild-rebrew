#include <string.h>

extern int g_6b7fdc;

int __cdecl fcn_0065f220(const char*, const char*);


/* Calls cb for every file of a VFS directory (and its subdirectories),
 * optionally only for one extension; stops when cb returns 0. */
/* ADDRESS: GOLDTL 0x00430f70 */
char __cdecl fcn_00430f70(char* start, char siblings, char* ext, char (__cdecl* cb)(char**, char*, void*), void* ctx)
{
	int i;
	char** f;
	char* dot;
	char* dir;

	dir = start;
	if (cb == 0) {
		return 0;
	}
	if (dir == 0) {
		dir = ((char*)g_6b7fdc);
		if (dir == 0) {
			return 1;
		}
	}
	do {
		if (dir[0x118] == 0) {
			break;
		}
		if (ext == 0) {
			for (i = 0, f = *(char***) (dir + 0x104); i < *(int*) (dir + 0x100); i++, f += 6) {
				if (!cb(f, dir, ctx)) {
					return 0;
				}
			}
		} else {
			for (i = 0, f = *(char***) (dir + 0x104); i < *(int*) (dir + 0x100); i++, f += 6) {
				dot = strrchr(*f, '.');
				if (dot != 0 && fcn_0065f220(dot + 1, ext) == 0) {
					if (!cb(f, dir, ctx)) {
						return 0;
					}
				}
			}
		}
		if (*(char**) (dir + 0x10c) != 0) {
			fcn_00430f70(*(char**) (dir + 0x10c), 1, ext, cb, ctx);
		}
		if (!siblings) {
			break;
		}
		dir = *(char**) (dir + 0x108);
	} while (dir != 0);
	return 1;
}
