#include <string.h>

extern char* g_6b7d68;
extern int g_6b7d6c;

void __cdecl fcn_0041ddd0(void* p);

// FUNCTION: GOLDTL 0x4245b0
int __cdecl fcn_004245b0(char* name)
{
	char* e;
	char* prev;
	char* next;
	int r;

	r = 0;
	prev = 0;
	if (g_6b7d68 != 0) {
		if (name != 0) {
			for (e = *(char**) (g_6b7d68 + 0x38); e != 0; e = *(char**) (e + 0x104)) {
				if (strcmp(e, name) == 0) {
					if (prev != 0) {
						*(char**) (prev + 0x104) = *(char**) (e + 0x104);
					} else {
						*(char**) (g_6b7d68 + 0x38) = *(char**) (e + 0x104);
					}
					*(int*) (g_6b7d68 + 0x34) -= *(int*) (e + 0x100);
					fcn_0041ddd0(e);
					g_6b7d6c++;
					break;
				}
				prev = e;
			}
		} else {
			e = *(char**) (g_6b7d68 + 0x38);
			while (e != 0) {
				next = *(char**) (e + 0x104);
				*(int*) (g_6b7d68 + 0x34) -= *(int*) (e + 0x100);
				fcn_0041ddd0(e);
				g_6b7d6c++;
				e = next;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
