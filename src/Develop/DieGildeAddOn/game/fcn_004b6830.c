#include <string.h>

extern unsigned char g_773d75;
extern double g_662a48;
extern double g_6640e8;

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004e8ad0(unsigned char);
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
		goto fail;
	}
	r = fcn_004e8ad0(*(unsigned char*) ((char*) ent + 0x166));
	if (r == 0 || r >= 7) {
		goto fail;
	}
	n = fcn_004e8b80(r, 6, msg);
	if (n == 0) {
		goto fail;
	}
	hit = 0;
	for (i = 0; i < n && hit == 0; i++) {
		rec = msg + 0xc + i * 0x18;
		if (*(rec + 4) != 3 || *(int*) rec == 0) {
			continue;
		}
		for (j = 0; ; j++) {
			s = (unsigned char*) 0x7f4ca2 + j * 0x21c;
			if ((int) s >= 0x85a0a2) {
				break;
			}
			if (*(s + 0x166) != *(rec - 4)) {
				continue;
			}
			if (*s != 3 && *s != 4) {
				continue;
			}
			hit = (unsigned short*) (0x7f4ca0 + j * 0x21c);
			break;
		}
	}
	if (hit == 0) {
		goto fail;
	}
	v = fcn_0042e410(4) & 0xffff;
	d = (double) v + g_662a48;
	w = fcn_0050dac0(*(short*) hit);
	v = (int) (((double) w * d) * g_6640e8);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a0 + 4) + 0x12e7,
	    *(unsigned short*) hit, *(unsigned short*) ent,
	    *(unsigned char*) (msg + 8 + i * 0x18) + 0x253, v);
	fcn_004c51a0(*a0, *(int*) ((char*) hit + 4), g_773d75, v);
	fcn_00545d40(*((int*) ent + 1), *((int*) ent + 1), buf,
	    0x100 < strlen(buf + 4), 0x603, 0);
	return 0;

fail:
	return 0x400;
}
