#include "Develop/DieGildeAddOn/game/spiel.h"


/* Same by-value request struct as fcn_004f5300: caller 0x4f56b0 copies 0x2d bytes. */
// SIZE 0x2d
typedef struct tag_req_2d_c {
	char raw[0x2d];
} req_2d_c;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_0051e070(void);

int __cdecl fcn_004f53a0(void* a1, req_2d_c s, int b)
{
	char* nm;
	char name[0x80] = "Geb\xe4ude";
	unsigned short w;
	unsigned char* p;
	int v = (b <= 1);

	gm_ResolveEntityById((void**) (&nm), 0, 0, *(int*) ((char*) &s + 0x21));
	if (nm != 0) {
		io_FormatTextBuffer(name, (int) "%1G", nm);
	}
	p = gm_LookupEntityRecordById(*(int*) ((char*) &s + 0x12));
	if (p != 0) {
		w = *(unsigned short*) p;
	} else {
		w = 0xfffe;
	}
	switch (*(int*) ((char*) &s + 0x1c) & 0xff) {
	case 0x11:
		io_FormatTextBuffer(a1, v + 0x1455, (char*) &s + 4);
		break;
	case 0x12:
		io_FormatTextBuffer(a1, v + 0x145a, (char*) &s + 4);
		break;
	case 0x13:
		io_FormatTextBuffer(a1, v + 0x145f, w, (char*) &s + 4);
		break;
	case 0x14:
		io_FormatTextBuffer(a1, v + 0x1464, (char*) &s + 4, w);
		break;
	case 0x15:
		io_FormatTextBuffer(a1, v + 0x1469, (char*) &s + 4, w);
		break;
	case 0x16:
		io_FormatTextBuffer(a1, v + 0x146e, w, (char*) &s + 4);
		break;
	case 0x17:
		io_FormatTextBuffer(a1, v + 0x1473, (char*) &s + 4, w);
		break;
	case 0x18:
		switch (fcn_0051e070()) {
		case 0:
		case 1:
			io_FormatTextBuffer(a1, v + 0x1478, (char*) &s + 4, w, name);
			break;
		case 2:
			io_FormatTextBuffer(a1, v + 0x1478, (char*) &s + 4, name, w);
			break;
		}
		break;
	case 0x19:
		io_FormatTextBuffer(a1, v + 0x147d, w, (char*) &s + 4);
		break;
	case 0x1a:
		io_FormatTextBuffer(a1, v + 0x1482, (char*) &s + 4, w);
		break;
	case 0x1b:
		io_FormatTextBuffer(a1, v + 0x1487, (char*) &s + 4);
		break;
	case 0x1c:
		io_FormatTextBuffer(a1, v + 0x148c, (char*) &s + 4, w);
		break;
	}
	return 0;
}
