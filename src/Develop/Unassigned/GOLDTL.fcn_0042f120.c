#include <string.h>

void __cdecl fcn_0042e520(char*);
void __cdecl fcn_0042e540(char*);
void* __cdecl fcn_0042f010(char*, void*);
int __cdecl fcn_0042e690(char*, void*, void**, int);


/* Looks a VFS path up: resolves its directory part, then the file name,
 * which may start with '*' for a wildcard match; returns whether found. */
/* ADDRESS: GOLDTL 0x0042f120 */
int __cdecl fcn_0042f120(char* path, void* root, void** found)
{
	void* dir;
	char* p;
	char* s;
	int ok;
	char buf[0x100];
	char name[0x100];

	dir = root;
	strcpy(buf, path);
	fcn_0042e520(buf);
	fcn_0042e540(buf);
	p = buf;
	while (*p != 0 && *p == '/') {
		p++;
	}
	strcpy(name, p);
	if (p != buf) {
		strcpy(buf, name);
	}
	s = strrchr(buf, '/');
	if (s != 0) {
		s++;
		strcpy(name, s);
		*s = 0;
		dir = fcn_0042f010(buf, dir);
		if (dir == 0) {
			return 0;
		}
	}
	if (name[0] == '*') {
		ok = fcn_0042e690(name + 1, dir, &dir, 1);
	} else {
		ok = fcn_0042e690(name, dir, &dir, 0);
	}
	if (ok) {
		*found = dir;
	}
	return ok;
}
