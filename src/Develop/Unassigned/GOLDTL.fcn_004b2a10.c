#include <string.h>

typedef struct Slot {
	int x0;
	char pad4[0x40];
} Slot;
// SIZE 0x44

extern int g_67fca0;
extern char g_680ae0[]; /* hst_ParseText_Fake_2nd_Pass() failed: Syntax Error in Label %i < %s > */

int __cdecl sprintf(char*, const char*, ...);
int __cdecl _isctype(int c, int mask);
Slot* __cdecl hst_ParseCommandline_1st_Pass(int id);
int __cdecl hst_ParseContext(char* label, char* out, Slot* slot);

#pragma optimize("y", off)


/* Second pass over a fake text line: every "_name--<n>" label is closed by
 * expanding its context through fcn_004b2300, everything else is copied. */
/* ADDRESS: GOLDTL 0x004b2a10 */
int __cdecl hst_ParseText_Fake_2nd_Pass(char* out, int id)
{
	char buf[0x17d0];
	char msg[0x400];
	char slotname[0x100];
	char label[0x100];
	Slot* slot;
	int in_label;
	int dashes;
	char* p;
	char* s;
	char* q;
	int c;
	int n;

	memset(buf, 0, sizeof(buf));
	in_label = 0;
	dashes = 0;
	strcpy(buf, out);
	slot = hst_ParseCommandline_1st_Pass(id);
	s = buf;
	if (*s != 0) {
		do {
			c = *s;
			if (in_label == 0) {
				if (c != '_') {
					*out++ = (char) c;
				} else {
					memset(label, 0, sizeof(label));
					label[0] = (char) c;
					p = label + 1;
					in_label = 1;
					dashes = 0;
				}
				s++;
				continue;
			}
			if (c == ' ') {
				goto syntax_error;
			}
			if (c == '-') {
				*p++ = (char) c;
				s++;
				dashes++;
				if (dashes > 2) {
					sprintf(msg, g_680ae0, id - g_67fca0 - 1, label);
					return 0;
				}
				continue;
			}
			if (dashes < 2) {
				*p++ = (char) c;
				s++;
				continue;
			}
			if (*(int*) 0x6b25b0 > 1) {
				n = _isctype(c, 4);
			} else {
				n = *(unsigned char*) (*(unsigned char**) 0x6b23a4 + c * 2) & 4;
			}
			if (n == 0) {
				sprintf(msg, g_680ae0, id - g_67fca0 - 1, label);
				return 0;
			}
			while ((*(int*) 0x6b25b0 > 1 ? _isctype(*s, 4)
			    : *(unsigned char*) (*(unsigned char**) 0x6b23a4 + *s * 2) & 4) != 0
			    && *s != 0) {
				*p++ = *s++;
			}
			memset(slotname, 0, sizeof(slotname));
			*p = 0;
			if (hst_ParseContext(label, slotname, slot) == 0) {
				goto parse_fail;
			}
			q = slotname;
			while (*q != 0) {
				*out++ = *q++;
			}
			*out++ = *s;
			in_label = 0;
			dashes = 0;
			s++;
		} while (*s != 0);
	}
	if (in_label != 0 && dashes < 2) {
syntax_error:
		sprintf(msg, g_680ae0, id - g_67fca0 - 1, label);
		return 0;
	}
	if (in_label == 1 && dashes == 2) {
		memset(slotname, 0, sizeof(slotname));
		*p = 0;
		if (hst_ParseContext(label, slotname, slot) == 0) {
			goto parse_fail;
		}
		q = slotname;
		while (*q != 0) {
			*out++ = *q++;
		}
	}
	*out = 0;
	return 1;
parse_fail:
	if (slot != 0) {
		slot->x0 = 0;
	}
	return 0;
}

#pragma optimize("y", on)
