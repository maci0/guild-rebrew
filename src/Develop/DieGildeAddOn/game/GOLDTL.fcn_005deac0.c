


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

extern __int64 g_666018;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl io_FormatTextBuffer(char*, int, ...);
char* __cdecl d2_OpenTargetPicker(Req*, char*, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(char*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl cm_SendBlockCharacter(int, int, int);
void __cdecl fcn_005dbe90(char*);

int __cdecl gm_ObjApplyAction0x5b(char* e, char* action)
{
	Req req;
	char text[0x200];
	char msg[0x400];
	char* r;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(&req.pad[2], -1, 0x20);
		io_FormatTextBuffer(text, 0x9c);
		req.c = (*(int*)&g_666018);
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
	if (gm_HasActiveSpecialObject(r, 0x2c4) == 0 || gm_RandomFloat01() > g_662a6c) {
		cm_SendBlockCharacter(*(int*) (r + 4), 1, 0);
	}
	*(int*) (action + 0x10) = 1;
	if (e[2] == 6) {
		io_FormatTextBuffer(text, 0x10a9, *(unsigned short*) r);
		io_FormatTextBuffer(msg, 0xfe8, text);
		fcn_005dbe90(msg);
	}
	return 1;
}
