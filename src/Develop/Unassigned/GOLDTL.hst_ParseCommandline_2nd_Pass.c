#include <string.h>
#include <stdlib.h>

extern int g_1052de0;
extern int* g_14a5320[];
extern int g_680748;
extern int g_68074d;
extern int g_67fca0;

/* Inferred helper name; the operand-homed fill is the reviewed original
 * inline assembly (see .scratch/sol/RULES.md, inline fill/copy block). */
static __inline void fill0(char* dst, int size)
{
	char* d;
	int n;

	n = size;
	d = dst;
	__asm {
		mov edi, d
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
}

/* ADDRESS: GOLDTL 0x004b2670 */
int __cdecl hst_ParseCommandline_2nd_Pass(int a0)
{
	char label[0x17d0];
	char buf[0x100];
	int rec;
	int len;
	char* p;
	char* start;
	char* wp;
	char* end;
	char c;
	int inToken;
	int i;

	rec = 0;
	len = 0;
	inToken = 0;
	wp = buf;

	if (g_1052de0 == 0) {
		return 0;
	}
	fill0(label, 0x17d0);
	fill0(buf, 0x100);

	if (a0 < 0x4800) {
		if (g_14a5320[a0] == 0) {
			return 0;
		}
		len = strlen((char*) g_14a5320[a0]);
		if ((unsigned int) len > 0x17c0) {
			sprintf(buf, (char*) 0x680a9c, a0);
			return 0;
		}
		strncpy(label, (char*) g_14a5320[a0], 0x17c0);
	} else {
		strcpy(label, (char*) a0);
	}

	if (*(int*) (label + 1) != g_680748 && *(int*) (label + 1) != g_68074d) {
		p = label;
	} else {
		buf[0] = label[6];
		i = atoi(buf);
		if (i < 0 || i >= 4) {
			sprintf(buf, (char*) 0x680a50, a0 - g_67fca0);
			return 0;
		}
		rec = i * 0x44 + 0x1007bc0;
		if (*(int*) rec == 0) {
			return 0;
		}
		p = label + 7;
	}

	fill0(buf, 0x100);
	wp = buf;

	while (*p != 0) {
		c = *p;
		if (c == ' ') {
			if (inToken) {
				len = 8;
				start = buf + 2;
				if (*(int*) (buf + 1) == g_68074d) {
					len = atoi(buf);
					start = buf + 8;
				}
				for (i = 0; i < 27; i++) {
					if (strcmp(start, (char*) (0x67fcb8 + i * 0x40)) == 0) {
						break;
					}
				}
				if (i < 27 && i < 0x1b) {
					end = start + strlen((char*) (0x67fcb8 + i * 0x40));
					(*(void (__cdecl**)(int, int, char*)) (0x680798 + i * 4))(rec, len, end);
				}
				fill0(buf, 0x100);
				wp = buf;
				inToken = 0;
			}
		} else {
			if (!inToken) {
				inToken = 1;
			}
			*wp = c;
			wp++;
		}
		p++;
	}

	if (!inToken) {
		return 1;
	}
	a0 = 8; start = buf + 2;
	if (*(int*) (buf + 1) == g_68074d) {
		a0 = atoi(buf); start = buf + 8;
	}
	for (i = 0; i < 27; i++) {
		if (strcmp(start, (char*) (0x67fcb8 + i * 0x40)) == 0) {
			break;
		}
	}
	if (i < 27 && i < 0x1b) {
		end = start + strlen((char*) (0x67fcb8 + i * 0x40));
		(*(void (__cdecl**)(int, int, char*)) (0x680798 + i * 4))(rec, a0, end);
	}
	return 1;
}
