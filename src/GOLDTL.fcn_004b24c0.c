#include <string.h>

typedef struct Slot {
	int x0;
	char pad4[0x40];
} Slot;
// SIZE 0x44

extern int g_1052de0;
extern char* g_14a5320[];
extern char g_1007bc0[];
extern int g_67fca0;

int __cdecl sprintf(char* buf, const char* fmt, ...);
int __cdecl atoi(const char* s);
void __cdecl fcn_004b2020(int n);

/* ADDRESS: GOLD 0x004b2380 */
/* ADDRESS: GOLDTL 0x004b24c0 */
Slot* __cdecl hst_ParseCommandline_1st_Pass(int id)
{
	char buf[0x17d0];
	char msg[0x100];
	char* s;
	int set;
	int n;
	Slot* slot;

	set = 0;
	if (g_1052de0 == 0) {
		return 0;
	}
	{
		char* p;
		int len;

		len = sizeof(buf);
		p = buf;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
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
	{
		char* p;
		int len;

		len = sizeof(msg);
		p = msg;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
	}
	if (id < 0x4800) {
		s = g_14a5320[id];
		if (s == 0) {
			return 0;
		}
		if (strlen(s) > 0x17c0) {
			sprintf(msg, "hst_ParseCommandline_1st_Pass() failed: Label %i is too long", id);
			return 0;
		}
		strncpy(buf, s, 0x17c0);
	} else {
		strcpy(buf, (char*) id);
	}
	if (*(int*) (buf + 1) == *(int*) "_SET") {
		msg[0] = buf[6];
		n = atoi(msg);
		set = 1;
	} else if (*(int*) (buf + 1) == *(int*) "_USE") {
		msg[0] = buf[6];
		n = atoi(msg);
	} else {
		return 0;
	}
	if (n > -1 && n < 4) {
		slot = &((Slot*)g_1007bc0)[n];
		if (set) {
			fcn_004b2020(n);
		}
		return slot;
	}
	if (n >= 4) {
		sprintf(msg, "hst_ParseCommandline_1st_Pass() failed: Wrong group index in Label %i", id - g_67fca0);
	}
	return 0;
}
