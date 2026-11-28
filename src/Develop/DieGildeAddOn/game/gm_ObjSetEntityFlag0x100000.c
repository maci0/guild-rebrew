


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x50
typedef struct {
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;

extern __int64 gm_TargetPersonTypeMask;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl io_FormatTextBuffer(char*, int, ...);
char* __cdecl d2_OpenTargetPicker(Req*, char*, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

/* ADDRESS: GOLDDE 0x005bf4e0 */
int __cdecl gm_ObjSetEntityFlag0x100000(char* e, char* action)
{
	Req req;
	char text[0x100];
	char* r;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(&req.pad[2], -1, 0x20);
		io_FormatTextBuffer(text, 0x9c);
		req.c = (*(int*)&gm_TargetPersonTypeMask);
		req.a = 0;
		req.size = 0x400;
		req.kind = 6;
		req.d = g_66601c;
		r = d2_OpenTargetPicker(&req, text, 0, 0);
	}
	else {
		r = gm_LookupEntityRecordById(*(int*) (action + 4));
	}
	if (r == 0) {
		return 0;
	}
	cm_RequestChangeBits(*(int*) (r + 4), 0x1cc, 4, 0x100000, 0);
	return 1;
}
