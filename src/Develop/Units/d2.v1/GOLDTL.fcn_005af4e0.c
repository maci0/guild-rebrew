


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

extern int g_14abcc0;

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl fcn_005bdc30(int, Req*, int, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl ConfirmProductionSelection(int, char*);

void __cdecl d2_ShowProductionSelection(char* a)
{
	Req req;

	if (d2_CheckOwnerBlocked(a) != 0) {
		return;
	}
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	req.kind = 2;
	req.c = 0;
	if (a == 0) {
		return;
	}
	fcn_0052a0c0(a, 0);
	fcn_005bdc30(1, &req, g_14abcc0, (void*) ConfirmProductionSelection, 0);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
}
