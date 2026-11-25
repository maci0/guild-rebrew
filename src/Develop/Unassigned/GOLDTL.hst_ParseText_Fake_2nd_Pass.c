#include <string.h>
#include <ctype.h>

typedef struct Slot {
	int x0;
	char pad4[0x40];
} Slot;
// SIZE 0x44

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_680ae0[]; /* hst_ParseText_Fake_2nd_Pass() failed: Syntax Error in Label %i < %s > */

int __cdecl sprintf(char*, const char*, ...);
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
	char* d;
	char* p;
	char* s;
	char* q;
	char c;

	in_label = 0;
	dashes = 0;
	{
		int n = sizeof(buf);
		char* fp = buf;
		__asm {
			mov edi, fp
			mov ebx, n
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short fill_end1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		fill_end1:
			add ecx, ebx
			rep stosb
		}
	}
	{
		int n = strlen(out);
		char* fp = buf;
		__asm {
			mov edi, fp
			mov esi, out
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short fill_end2
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		fill_end2:
			add ecx, ebx
			rep movsb
		}
	}
	slot = hst_ParseCommandline_1st_Pass(id);
	s = buf;
	d = out;
	if (*s != 0) {
		do {
			if (in_label == 0) {
				c = *s;
				if (c == '_') {
					{
						int n = sizeof(label);
						char* fp = label;
						__asm {
							mov edi, fp
							mov ebx, n
							xor eax, eax
							lea ecx, [edi+edi*2]
							and ecx, 3
							sub ebx, ecx
							jle short fill_end3
							rep stosb
							mov ecx, ebx
							and ebx, 3
							shr ecx, 2
							rep stosd
						fill_end3:
							add ecx, ebx
							rep stosb
						}
					}
					p = label;
					*p++ = *s;
					in_label = 1;
					dashes = 0;
				} else {
					*d++ = (char) c;
				}
				s++;
				continue;
			}
			c = *s;
			if (c == ' ') {
				goto syntax_error;
			}
			if (c == '-') {
				dashes++;
				*p++ = (char) c;
				s++;
				if (dashes > 2) {
					sprintf(msg, g_680ae0, id - hst_HistoryTextBase - 1, label);
					return 0;
				}
				continue;
			}
			if (dashes < 2) {
				*p++ = (char) c;
				s++;
				continue;
			}
			if (dashes == 2) {
				if (isdigit(c) == 0) {
					sprintf(msg, g_680ae0, id - hst_HistoryTextBase - 1, label);
					return 0;
				}
				while (isdigit(*s) && *s != 0) {
					*p++ = *s++;
				}
				{
					int n = sizeof(slotname);
					char* fq = slotname;
					__asm {
						mov edi, fq
						mov ebx, n
						xor eax, eax
						lea ecx, [edi+edi*2]
						and ecx, 3
						sub ebx, ecx
						jle short fill_end4
						rep stosb
						mov ecx, ebx
						and ebx, 3
						shr ecx, 2
						rep stosd
					fill_end4:
						add ecx, ebx
						rep stosb
					}
				}
				*p = 0;
				if (hst_ParseContext(label, slotname, slot) == 0) {
					goto parse_fail;
				}
				q = slotname;
				while (*q != 0) {
					*d++ = *q++;
				}
				*d++ = *s;
				in_label = 0;
				dashes = 0;
				s++;
			}
		} while (*s != 0);
	}
	if (in_label != 0 && dashes < 2) {
syntax_error:
		sprintf(msg, g_680ae0, id - hst_HistoryTextBase - 1, label);
		return 0;
	}
	if (in_label == 1 && dashes == 2) {
		{
			int n = sizeof(slotname);
			char* fq = slotname;
			__asm {
				mov edi, fq
				mov ebx, n
				xor eax, eax
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short fill_end5
				rep stosb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep stosd
			fill_end5:
				add ecx, ebx
				rep stosb
			}
		}
		*p = 0;
		if (hst_ParseContext(label, slotname, slot) == 0) {
			goto parse_fail;
		}
		q = slotname;
		while (*q != 0) {
			*d++ = *q++;
		}
	}
	*d = 0;
	return 1;
parse_fail:
	if (slot != 0) {
		slot->x0 = 0;
	}
	return 0;
}

#pragma optimize("y", on)
