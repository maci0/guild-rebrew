#include <string.h>

extern int g_1052de0;
extern char* g_14a5320[];
extern int g_67fca0;
extern unsigned char g_773d75;
extern char g_868080[];
extern char g_1007ba0[];

int __cdecl sprintf(char*, const char*, ...);
int __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl fcn_0064eeec(void*);

typedef struct Parts {
	char a;
	char b;
} Parts;

/*
 * Native frame is 0x17f8, but bytes -0x24..-0x1d are never read, written or
 * addressed by any instruction and no spill, fill or copy window lands there.
 * With evidenced locals only the frame is 0x17f4, so the 8-byte gap is
 * unreachable from C without inventing dead members; it is left unreproduced.
 */

/* block-fill prelude, see docs/codegen-walls.md section 6b */
static __inline void fill0(char* d, int n)
{
	char* dd;
	int nn;

	nn = n;
	dd = d;
	__asm {
		mov edi, dd
		mov ebx, nn
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

/* block-copy prelude, see docs/codegen-walls.md section 6b */
static __inline void copy0(char* d, char* s, int n)
{
	char* dd;
	char* sp_;
	int nn;

	nn = n;
	sp_ = s;
	dd = d;
	__asm {
		mov edi, dd
		mov esi, sp_
		mov ebx, nn
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L2
		rep movsb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep movsd
	L2:
		add ecx, ebx
		rep movsb
	}
}


/* ADDRESS: GOLDTL 0x004b3010 */
int __cdecl hst_ParseDate(int key, int flags, int* out, char* text)
{
	char buf[0x17d0];
	Parts parts;
	int c;
	int mode;
	unsigned char tmp[0x10];
	char* src;
	int val;

#define a parts.a
#define b parts.b

	mode = 0;
	do {
		if (g_1052de0 == 0) {
			break;
		}
		if (g_67fca0 == -1) {
			break;
		}
		fill0(buf, 0x17d0);
		fill0((char*) tmp, 0x10);
		if (key < 0x4800) {
			src = g_14a5320[key];
			if (src == 0) {
				break;
			}
			if (strlen(src) > 0x17c0) {
				break;
			}
			strncpy(buf, src, 0x17c0);
		} else {
			strcpy(buf, (char*) key);
		}
		if (strlen(buf) != 0xa) {
			sprintf(buf, (char*) 0x680b84, key - g_67fca0);
			break;
		}
		copy0((char*) tmp, buf, 2);
		a = (char) fcn_0064eeec(tmp);
		copy0((char*) tmp, buf + 3, 2);
		b = (char) fcn_0064eeec(tmp);
		copy0((char*) tmp, buf + 6, 4);
		c = (short) fcn_0064eeec(tmp);
		val = fcn_0064eeec(tmp);
		if (a == 0) {
			a = 1;
			mode = 1;
		}
		if (b == 0) {
			b = 1;
			mode = 2;
		}
		*out = val - 0x578;
		if ((flags & 4) != 0) {
			copy0(text, buf, strlen(buf));
		} else if ((flags & 2) != 0) {
			switch (mode) {
			case 2:
				io_FormatTextBuffer(text, (char*) 0x680b7c, g_868080 + g_773d75 * 0x2f4, c);
				break;
			case 1:
				io_FormatTextBuffer(text, (char*) 0x680b70, g_868080 + g_773d75 * 0x2f4, b + 0x4f, c);
				break;
			case 0:
				io_FormatTextBuffer(text, (char*) 0x680b60, g_868080 + g_773d75 * 0x2f4, a, b + 0x4f, c);
				break;
			}
		}
		if ((flags & 1) != 0) {
			fill0(g_1007ba0, 0x10);
			copy0(g_1007ba0, buf, 0xa);
		}
		return 1;
	} while (0);
	return 0;
}
unsigned char _dpad_868080[5120];
