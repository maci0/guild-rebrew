#include <string.h>

extern char* g_6b7d68;
extern int g_6b7d6c;

char* __cdecl fcn_00423ac0(char* name);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00424130 */
int __cdecl fcn_00424130(char* set, char* name)
{
	char* scope;
	char* e;
	char* prev;
	char* next;
	int r;

	r = 0;
	prev = 0;
	scope = fcn_00423ac0(set);
	if (scope != 0) {
		if (name != 0) {
			for (e = *(char**) (scope + 0x38); e != 0; e = *(char**) (e + 0x104)) {
				if (strcmp(e, name) == 0) {
					if (prev != 0) {
						*(char**) (prev + 0x104) = *(char**) (e + 0x104);
					} else {
						*(char**) (scope + 0x38) = *(char**) (e + 0x104);
					}
					*(int*) (scope + 0x34) -= *(int*) (e + 0x100);
					*(int*) (g_6b7d68 + 0x34) -= *(int*) (e + 0x100);
					m_FreeTracked(e);
					g_6b7d6c++;
					break;
				}
				prev = e;
			}
		} else {
			e = *(char**) (scope + 0x38);
			while (e != 0) {
				next = *(char**) (e + 0x104);
				*(int*) (scope + 0x34) -= *(int*) (e + 0x100);
				*(int*) (g_6b7d68 + 0x34) -= *(int*) (e + 0x100);
				m_FreeTracked(e);
				g_6b7d6c++;
				e = next;
			}
			*(char**) (scope + 0x38) = 0;
		}
	} else {
		r = -1;
	}
	return r;
}
