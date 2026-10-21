#include <string.h>

typedef struct NODE042F010 {
	char pad0[0x108];
	struct NODE042F010* next;
	struct NODE042F010* child;
} NODE042F010;

int __cdecl fcn_0042e520(char*);
char* __cdecl fcn_0064e790(const char* s, int c);
int __cdecl fcn_0042e4d0(char* name, NODE042F010* p);

/* ADDRESS: GOLDTL 0x0042f010 */
char* __cdecl fcn_0042f010(char* name, NODE042F010* node)
{
	char buf[0x100];
	char path[0x100];
	NODE042F010* n;
	char* p;
	char c;

	n = node;
	if (name == 0) {
		return 0;
	}
	c = *name;
	if (c == 0) {
		return (char*) n;
	}
	strcpy(buf, name);
	fcn_0042e520(buf);
	if (buf[strlen(buf) - 1] != '/') {
		strcat(buf, "/");
	}
	strcpy(path, buf);
	p = fcn_0064e790(path, '/');
	while (p != 0 && n != 0) {
		strcpy(buf, p + 1);
		n = n->child;
		while (n != 0 && fcn_0042e4d0(path, n) != 0) {
			n = n->next;
		}
		strcpy(path, buf);
		p = fcn_0064e790(path, '/');
	}
	return (char*) n;
}
