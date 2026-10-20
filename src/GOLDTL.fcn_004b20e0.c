#include <string.h>

extern int g_1052de0;
extern char* g_14a5320[];
extern int g_67fca0;
extern char g_679060[]; /* %s */
extern char g_6808b0[]; /* hst_ParseText_Fake_1st_Pass() failed: Syntax Error in Label %i */
extern char g_6808f0[]; /* hst_ParseText_Fake_1st_Pass() failed: Label %i is too long */

int __cdecl sprintf(char*, const char*, ...);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004b20e0 */
int __cdecl fcn_004b20e0(char* out, int id)
{
	char buf[0x17d0];
	/* native frame is 0x18dc; the extra 8 bytes below msg stand in for the
	   dst/len spill slots the native generic memset keeps at ebp-8/ebp-0xc */
	char msg[0x108];
	char* open;
	char* hash;
	char* p;

	open = 0;
	hash = 0;
	if (g_1052de0 == 0) {
		return 0;
	}
	memset(buf, 0, sizeof(buf));
	if (id < 0x4800) {
		p = g_14a5320[id];
		if (p == 0) {
			return 0;
		}
		if (strlen(p) > 0x17c0) {
			sprintf(msg, g_6808f0, id);
			return 0;
		}
		strncpy(buf, p, 0x17c0);
	} else {
		strcpy(buf, (char*) id);
	}
	p = buf;
	while (*p != 0) {
		if (*p == '[') {
			if (open != 0) {
				sprintf(msg, g_6808b0, id - g_67fca0);
				return 0;
			}
			open = p;
			p++;
		} else if (*p == '#') {
			if (open == 0 || hash != 0) {
				sprintf(msg, g_6808b0, id - g_67fca0);
				return 0;
			}
			hash = p;
			p++;
		} else if (*p == ']') {
			if (open == 0 || hash == 0) {
				sprintf(msg, g_6808b0, id - g_67fca0);
				return 0;
			}
			fcn_0064d740(p, p + 1, strlen(p + 1) + 1);
			fcn_0064d740(open, hash + 1, strlen(hash + 1) + 1);
			p += (open - hash) - 1;
			hash = 0;
			open = 0;
		} else {
			p++;
		}
	}
	if (open != 0 || hash != 0) {
		sprintf(msg, g_6808b0, id - g_67fca0);
		return 0;
	}
	sprintf(out, g_679060, buf);
	return 1;
}

#pragma optimize("y", on)
