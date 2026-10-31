#include <string.h>

void __cdecl io_FormatTextBuffer(void* out, int id, ...);
void* __cdecl gm_LookupEntityRecordById(int id);
void* __cdecl fcn_005cd440(void* desc, void* buf, int a, int b);
void __cdecl fcn_004c5420(int a, int b, int c, int d, int e);
void __cdecl fcn_005dbe90(void* buf);

/* ADDRESS: GOLDTL 0x005de9a0 */
int __cdecl fcn_005de9a0(char* a0, char* a1)
{
	char desc[0x50];
	char bufA[0x200];
	char bufB[0x400];
	void* p;

	if (a0[2] == 6) {
		memset(desc, 0, 0x50);
		memset(desc + 0x1c, 0xff, 0x20);
		io_FormatTextBuffer(bufA, 0x9c);
		*(int*) (desc + 0x08) = *(int*) 0x666018;
		*(int*) (desc + 0x0c) = *(int*) 0x66601c;
		*(int*) (desc + 0x00) = 0;
		*(int*) (desc + 0x04) = 0x400;
		*(int*) (desc + 0x10) = 6;
		p = fcn_005cd440(desc, bufA, 0, 0);
	} else {
		p = gm_LookupEntityRecordById(*(int*) (a1 + 4));
	}
	if (p == 0) {
		return 0;
	}
	fcn_004c5420(*(int*) ((char*) p + 4), 0x1cc, 4, 0x200000, 0);
	*(int*) (a1 + 0x10) = 1;
	if (a0[2] == 6) {
		io_FormatTextBuffer(bufA, 0x10a7, *(unsigned short*) p);
		io_FormatTextBuffer(bufB, 0xfe8, bufA);
		fcn_005dbe90(bufB);
	}
	return 1;
}
