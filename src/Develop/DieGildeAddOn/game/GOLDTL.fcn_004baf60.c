extern double g_664e78;
extern double g_664e78;
extern float g_662cf8;
extern float g_662cf8;
/* Owned (both targets) by src/GOLDTL.fcn_004b6f00.c. */
extern double g_6640e8;

#include <string.h>

int __cdecl gm_RandomMod(int);
void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(void*, int);
int __cdecl fcn_004bac00(void*, int*, float);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, void*);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);


/* ADDRESS: GOLD 0x004bab90 */
/* ADDRESS: GOLDTL 0x004baf60 */
int __cdecl fcn_004baf60(void* a1)
{
	float f;
	int v;
	char buf[0x200];
	int n;
	unsigned char* p;
	void* e;
	int r;
	unsigned int len;

	n = gm_RandomMod(0x14) & 0xffff;
	f = (float) (((double) n + g_664e78) * g_6640e8);
	p = gm_LookupEntityRecordById(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	if (fcn_005c6270(p, 0x290) == 0) {
		if (fcn_004bac00(p, &v, f) != 0) {
			e = gm_StartFilteredEntitySearch(1, 1, v);
			if (e != 0) {
				float t;

				t = f;
				r = (int) (t * g_662cf8);
				io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, r, e);
				len = strlen(buf);
				he_MessageBoxQuickjump(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4),
				    buf, 0x100 < len, 0x603, *(int*) ((char*) e + 1), -1, 0, 0);
				return 0;
			}
		}
	}
	return 0x400;
}
