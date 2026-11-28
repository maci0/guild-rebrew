

#include <string.h>

// SIZE 0xf8
#include "Develop/client_types.h"
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	char pad60[0x98];
};

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad[15];
} Req;

extern pos14_7f4c00 gm_GameTime;
extern __int64 gm_TargetPersonTypeMask;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestModifyHealth(int, int);
void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_OpenTargetPicker(Req*, char*, int, void*);
void __cdecl d2_ShowIntimidationDialog(void);

/* The message struct is local to the branch that sends it: with it at function
   scope the header stores before the e+4 load issue ahead of the push. */
/* ADDRESS: GOLDDE 0x005b7c40 */
int __cdecl gm_RunIntimidationAction(unsigned char* obj, char* request)
{
	Req req;
	char text[0x40];
	unsigned char* e;
	int result;

	result = 0;
	if (obj[2] != 6 && obj[2] != 7) {
		e = gm_LookupEntityRecordById(*(int*) (request + 0x214));
		if (e == 0) {
			return 0x60;
		}
		{
			struct msg m;

			cm_RequestModifyHealth(*(int*) (obj + 4), -2);
			memset(&m, 0, sizeof(m));
			m.b4 = 0x4b;
			m.f8 = *(int*) (obj + 4);
			m.fc = *(int*) (obj + 4);
			m.pos = gm_GameTime;
			m.b36 = 2;
			m.f5c = *(int*) (e + 4);
			m.f58 = *(int*) (obj + 4);
			cm_SendCopyEntityData(&m);
			return 0x10;
		}
	}
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	req.kind = 6;
	req.cd = gm_TargetPersonTypeMask;
	io_FormatTextBuffer(text, 0x1d61);
	if (d2_OpenTargetPicker(&req, text, 0, d2_ShowIntimidationDialog)) {
		result = 1;
	}
	return result;
}
