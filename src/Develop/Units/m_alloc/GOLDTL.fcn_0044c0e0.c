#include <string.h>

extern char s_67ade8[];
extern char* g_1042efc;
extern char g_1042d00[];

char* __cdecl fcn_00449ac0(char* s, char* sub);
void __cdecl fcn_0044b340(char* name, int* a, int* b, int* c);
char* __cdecl fcn_0044b480(char* buf, char* name, int a, int b, int c);
void __cdecl m_FreeTracked(int p);
void __cdecl fcn_0044a120(void);
void __cdecl fcn_00455910(void);
void __cdecl fcn_0044c0c0(void);

/* ADDRESS: GOLDTL 0x0044c0e0 */
char* __cdecl fcn_0044c0e0(char* path, char* name)
{
	char* r;
	char* p;
	int x;
	int a;
	int c;
	int b;
	char buf[0x100];

	r = 0;
	p = fcn_00449ac0(path, s_67ade8);
	if (p != 0) {
		b = 0;
		c = 0;
		a = 0;
		strcpy(buf, p);
		fcn_0044b340(name, &a, &b, &c);
		if (a == 0) {
			fcn_0044b340(path, &a, &b, &c);
		}
		x = a;
		r = fcn_0044b480(buf, name, x, b, c);
		if (r != 0) {
			if (x != 0 && *(int*) (r + 0x200) != x) {
				m_FreeTracked(x);
			}
			*(void**) (r + 0x1ec) = (void*) fcn_0044a120;
			*(void**) (r + 0x1f0) = (void*) fcn_00455910;
			*(void**) (r + 0x1f4) = (void*) fcn_0044c0c0;
		} else if (x != 0) {
			m_FreeTracked(x);
		}
		if (r != 0) {
			*(char**) (r + 0x1fc) = g_1042efc;
			g_1042efc = r;
			*(char**) (r + 0x1f8) = g_1042d00;
			*(char**) (*(char**) (r + 0x1fc) + 0x1f8) = r;
		}
	}
	return r;
}
