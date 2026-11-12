#include <stdio.h>
#include <string.h>

extern int g_1052de0;
extern int g_67fca0;

void __cdecl io_FormatTextBuffer(int, int, ...);

/* ADDRESS: GOLDTL 0x004b2e20 */
void __cdecl hst_ParseText_Real(int out, int src)
{
	char buf[0x17d0];
	char msg[0x100];
	char* open;
	char* hash;
	char* scan;
	char* p;
	char c;
	void* fill_dst;
	int fill_size;

	open = 0;
	hash = 0;
	if (g_1052de0 == 0) {
		return;
	}
	fill_dst = buf;
	fill_size = sizeof(buf);
	__asm {
		mov edi, fill_dst
		mov ebx, fill_size
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L4b2e20fill
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L4b2e20fill:
		add ecx, ebx
		rep stosb
	}
	if (src < 0x4800) {
		p = *(char**) (src * 4 + 0x14a5320);
		if (p == 0) {
			return;
		}
		if (strlen(p) > 0x17c0) {
			return;
		}
		strncpy(buf, p, 0x17c0);
	} else {
		strcpy(buf, (char*) src);
	}
	scan = buf;
	while (*scan) {
		c = *scan;
		if (c == '[') {
			if (open != 0) {
				sprintf(msg, (char*) 0x680b28, src - g_67fca0);
				return;
			}
			open = scan;
			scan++;
		} else if (c == '#') {
			if (open == 0 || hash != 0) {
				sprintf(msg, (char*) 0x680b28, src - g_67fca0);
				return;
			}
			hash = scan;
			scan++;
		} else if (c == ']') {
			if (open == 0 || hash == 0) {
				sprintf(msg, (char*) 0x680b28, src - g_67fca0);
				return;
			}
			memmove(hash, scan + 1, strlen(scan + 1) + 1);
			memmove(open, open + 1, strlen(open + 1) + 1);
			scan = hash - 1;
			hash = 0;
			open = 0;
		} else {
			scan++;
		}
	}
	if (open != 0) {
		return;
	}
	if (hash != 0) {
		return;
	}
	io_FormatTextBuffer(out, 0x679060, buf);
}
