char g_68deb8[] = "%s$A";
extern char g_68deb8[];



#include <string.h>

int __cdecl fcn_004e8d10(void*, int, void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_004ec660(void* a1)
{
	char items[0x48];
	char buf[0x800];
	int n;
	int i;

	if (*(unsigned char*) ((char*) a1 + 0xd) < 2) {
		return;
	}
	n = fcn_004e8d10(a1, 6, items);
	if (n == 0) {
		return;
	}
	memset(buf, 0, 0x800);
	io_FormatTextBuffer(buf, 0x13ac);
	if (n > 0) {
		for (i = 0; i < n; i++) {
			io_FormatTextBuffer(buf + strlen(buf), (int) g_68deb8,
			    *(int*) (items + i * 0xc) + 0x253);
		}
	}
	fcn_00545d40(*(int*) ((char*) a1 + 4), -1, buf, 1, 0x5ec, (void*) 0);
}
