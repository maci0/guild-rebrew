#include "Develop/DieGildeAddOn/game/spiel.h"


/* Same by-value request struct as fcn_004f5300: caller 0x4f56b0 copies 0x2d bytes. */
// SIZE 0x2d
typedef struct tag_req_2d_c {
	char raw[0x2d];
} req_2d_c;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_0051e070(void);

int __cdecl fcn_004f53a0(void* output, req_2d_c request, int b)
{
	char* nm;
	char name[0x80] = "Geb\xe4ude";
	unsigned short entityId;
	unsigned char* p;
	int formatOffset = (b <= 1);

	gm_ResolveEntityById((void**) (&nm), 0, 0, *(int*) ((char*) &request + 0x21));
	if (nm != 0) {
		io_FormatTextBuffer(name, (int) "%1G", nm);
	}
	p = gm_LookupEntityRecordById(*(int*) ((char*) &request + 0x12));
	if (p != 0) {
		entityId = *(unsigned short*) p;
	} else {
		entityId = 0xfffe;
	}
	switch (*(int*) ((char*) &request + 0x1c) & 0xff) {
	case 0x11:
		io_FormatTextBuffer(output, formatOffset + 0x1455, (char*) &request + 4);
		break;
	case 0x12:
		io_FormatTextBuffer(output, formatOffset + 0x145a, (char*) &request + 4);
		break;
	case 0x13:
		io_FormatTextBuffer(output, formatOffset + 0x145f, entityId, (char*) &request + 4);
		break;
	case 0x14:
		io_FormatTextBuffer(output, formatOffset + 0x1464, (char*) &request + 4, entityId);
		break;
	case 0x15:
		io_FormatTextBuffer(output, formatOffset + 0x1469, (char*) &request + 4, entityId);
		break;
	case 0x16:
		io_FormatTextBuffer(output, formatOffset + 0x146e, entityId, (char*) &request + 4);
		break;
	case 0x17:
		io_FormatTextBuffer(output, formatOffset + 0x1473, (char*) &request + 4, entityId);
		break;
	case 0x18:
		switch (fcn_0051e070()) {
		case 0:
		case 1:
			io_FormatTextBuffer(output, formatOffset + 0x1478, (char*) &request + 4, entityId, name);
			break;
		case 2:
			io_FormatTextBuffer(output, formatOffset + 0x1478, (char*) &request + 4, name, entityId);
			break;
		}
		break;
	case 0x19:
		io_FormatTextBuffer(output, formatOffset + 0x147d, entityId, (char*) &request + 4);
		break;
	case 0x1a:
		io_FormatTextBuffer(output, formatOffset + 0x1482, (char*) &request + 4, entityId);
		break;
	case 0x1b:
		io_FormatTextBuffer(output, formatOffset + 0x1487, (char*) &request + 4);
		break;
	case 0x1c:
		io_FormatTextBuffer(output, formatOffset + 0x148c, (char*) &request + 4, entityId);
		break;
	}
	return 0;
}
