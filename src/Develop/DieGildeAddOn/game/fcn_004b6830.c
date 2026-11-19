#include <string.h>

extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004e8ad0(int);
int __cdecl fcn_004e8b80(int, int, void*);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_0050dac0(short);
void __cdecl io_FormatTextBuffer(char*, int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b6830 */
int __cdecl fcn_004b6830(int* a0)
{
	unsigned char msg[0xa8];
	char buf[0xe8];
	unsigned short* ent;
	unsigned char* rec;
	unsigned char* s;
	unsigned short* hit;
	int i;
	int j;
	int n;
	int r;
	int w;
	int v;
	double d;

	ent = (unsigned short*) gm_LookupEntityRecordById(*a0);
	if (ent == 0) {
		return 1;
	}
	if (*(unsigned char*) ((char*) ent + 0x166) == 0) {
		return 0x400;
	}
	r = fcn_004e8ad0(*(unsigned char*) ((char*) ent + 0x166));
	if (r == 0 || r >= 7) {
		return 0x400;
	}
	n = fcn_004e8b80(r, 6, msg);
	if (n == 0) {
		return 0x400;
	}
	hit = 0;
	for (i = 0; i < n && hit == 0; i++) {
		rec = msg + 0xc + i * 0x18;
		if (*(rec + 4) != 3 || *(int*) rec == 0) {
			continue;
		}
		for (s = (unsigned char*) 0x7f4ca2; (int) s < 0x85a0a2; s += 0x21c) {
			if (*(s + 0x166) != *(rec - 4)) {
				continue;
			}
			if (*s != 3 && *s != 4) {
				continue;
			}
			hit = (unsigned short*) (s - 2);
			break;
		}
		if (hit != 0) {
			goto found;
		}
	}
	return 0x400;
found:
	v = fcn_0042e410(4) & 0xffff;
	d = (double) v + 2.0;
	w = fcn_0050dac0(*(short*) hit);
	v = (int) (((double) w * d) * 0.01);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a0 + 4) + 0x12e7,
	    *(unsigned short*) hit, *(unsigned short*) ent,
	    *(unsigned char*) (msg + 8 + i * 0x18) + 0x253, v);
	fcn_004c51a0(*a0, *(int*) ((char*) hit + 4), g_773d75, v);
	fcn_00545d40(*((int*) ent + 1), *((int*) ent + 1), buf,
	    0x100 < strlen(buf + 4), 0x603, 0);
	return 0;

}
