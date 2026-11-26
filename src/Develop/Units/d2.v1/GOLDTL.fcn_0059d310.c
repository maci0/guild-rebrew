


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;
// SIZE 0x50

extern int g_14abad4;

void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_005bdc30(int, Req*, int, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl d2_RunTaschendiebstahlDialog(void);

void __cdecl d2_SelectPickpocketTarget(int building)
{
	Req req;

	memset(&req, 0, sizeof(req));
	req.d = 0;
	req.size = 0x400;
	req.kind = 7;
	req.c = 0x93810;
	fcn_0052a0c0(building, 0);
	fcn_005bdc30(1, &req, g_14abad4, (void*) d2_RunTaschendiebstahlDialog, 0);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
}
