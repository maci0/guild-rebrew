


#include <string.h>

/* The caller (0x4f56b0) copies 0x2d bytes onto the stack: 11 dwords + 1 byte. */
// SIZE 0x2d
typedef struct tag_req_2d {
	char raw[0x2d];
} req_2d;

extern char g_69037c[];
unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f5300(void* a1, req_2d s, int b)
{
	unsigned short w;
	unsigned char* p;
	int r = 1;
	int v = (b <= r);

	p = gm_LookupEntityRecordById(*(int*) ((char*) &s + 0x12));
	if (p != 0) {
		w = *(unsigned short*) p;
	} else {
		w = 0xfffe;
	}
	switch (*(int*) ((char*) &s + 0x1c) & 0xff) {
	case 0xe:
		io_FormatTextBuffer(a1, v + 0x1446, (char*) &s + 4, w);
		break;
	case 0x10:
		io_FormatTextBuffer(a1, v + 0x1450, w, (char*) &s + 4);
		break;
	default:
		memcpy(a1, g_69037c, 0x20);
		r = 0;
		break;
	}
	return r;
}
