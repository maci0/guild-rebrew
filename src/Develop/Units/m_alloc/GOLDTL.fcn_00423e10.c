#include <string.h>

extern char* g_6b7d68;
extern int g_6b7d6c;

char* __cdecl fcn_00423ac0(char* s);
void* __cdecl fcn_004239b0(void);
char* __cdecl m_alloc(int size, char* tag);
char* __cdecl strncpy(char* dst, const char* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00423e10 */
int __cdecl fcn_00423e10(char* s)
{
	char* list;
	char* buf;

	if (g_6b7d68 == 0) {
		return -1;
	}
	if (fcn_00423ac0(s) != 0) {
		return -1;
	}
	list = (char*) fcn_004239b0();
	buf = m_alloc(0x40, (char*) 0x678fe0);
	if (list != 0) {
		*(char**) (list + 0x3c) = buf;
		if (buf == 0) {
			return -1;
		}
		memset(buf, 0, 0x40);
		strncpy(buf, s, 0x32);
		g_6b7d6c++;
		return 0;
	}
	if (buf == 0) {
		return -1;
	}
	memset(buf, 0, 0x40);
	strncpy(buf, s, 0x32);
	*(char**) (g_6b7d68 + 0x3c) = buf;
	g_6b7d6c++;
	return 0;
}
