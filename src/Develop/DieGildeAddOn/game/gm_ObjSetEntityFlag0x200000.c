#include <string.h>
extern __int64 g_666018;
void __cdecl io_FormatTextBuffer(void* out, int id, ...);
void* __cdecl gm_LookupEntityRecordById(int id);
void* __cdecl d2_OpenTargetPicker(void* desc, void* buf, int a, int b);
void __cdecl cm_RequestChangeBits(int a, int b, int c, int d, int e);
void __cdecl fcn_005dbe90(void* buf);

/* ADDRESS: GOLDTL 0x005de9a0 */
int __cdecl gm_ObjSetEntityFlag0x200000(char* actor, char* action)
{
	char desc[0x50];
	char bufA[0x200];
	char bufB[0x400];
	void* p;

	if (actor[2] == 6) {
		memset(desc, 0, 0x50);
		memset(desc + 0x1c, 0xff, 0x20);
		io_FormatTextBuffer(bufA, 0x9c);

		*(int*) (desc + 0x00) = 0;
		*(int*) (desc + 0x04) = 0x400;
		*(int*) (desc + 0x10) = 6;
		*(__int64*) (desc + 0x08) = g_666018;
		p = d2_OpenTargetPicker(desc, bufA, 0, 0);
	} else {
		p = gm_LookupEntityRecordById(*(int*) (action + 4));
	}
	if (p == 0) {
		return 0;
	}
	cm_RequestChangeBits(*(int*) ((char*) p + 4), 0x1cc, 4, 0x200000, 0);
	*(int*) (action + 0x10) = 1;
	if (actor[2] == 6) {
		io_FormatTextBuffer(bufA, 0x10a7, *(unsigned short*) p);
		io_FormatTextBuffer(bufB, 0xfe8, bufA);
		fcn_005dbe90(bufB);
	}
	return 1;
}
