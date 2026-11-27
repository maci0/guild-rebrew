


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

extern int g_14abd48;

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl d2_InitPlayerBar(char*, int);
void __cdecl d2_RunCityScrollMapDialog(int, Req*, int, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl d2_RunRaeuberlagerTargetDialog(int a0, char* a1);

void __cdecl d2_SelectSchutzgeldTarget(char* building)
{
	Req req;

	if (d2_CheckOwnerBlocked(building) != 0 || building == 0) {
		return;
	}
	memset(&req, 0, sizeof(req));
	req.a = 1;
	req.size = -1;
	req.kind = 6;
	req.c = 0xa07c43a0;
	req.d = 1;
	d2_InitPlayerBar(building, 0);
	d2_RunCityScrollMapDialog(1, &req, g_14abd48, (void*) d2_RunRaeuberlagerTargetDialog, 0);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
}
