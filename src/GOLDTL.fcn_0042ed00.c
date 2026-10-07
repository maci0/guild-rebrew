// FUNCTION: GOLD 0x0042f4d0
// FUNCTION: GOLDTL 0x42ed00

#include <string.h>

void* __cdecl fcn_0042e5a0(char*, void*);
int __cdecl fcn_0042e740(char*, void*, int, int, int, int, int);

void __cdecl fcn_0042ed00(char* path, void* parent, int a3, int a4, int a5, int a6, int a7)
{
	char buf[0x100];
	char part[0x100];
	char* s;
	char* p;
	void* node;

	if (path[strlen(path) - 1] != '/') {
		node = parent;
		strcpy(buf, path);
		s = buf;
		p = strchr(buf, '/');
		while (p != 0) {
			strcpy(part, s);
			strchr(part, '/')[1] = 0;
			node = fcn_0042e5a0(part, node);
			s = p + 1;
			p = strchr(s, '/');
		}
		fcn_0042e740(s, node, a3, a4, a5, a6, a7);
	}
}
